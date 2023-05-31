#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <cstdint>
#include <cassert>
#include <string>
#include <unordered_map>
#include <iomanip>


using namespace std;

void error(const string& msg, int returncode = EXIT_FAILURE) {
	cout << msg << endl;
	exit(returncode);
}

template <typename T>
istream& raw_read(istream& is, T& val, size_t size = sizeof(T)) {
	return is.read(reinterpret_cast<char*>(&val), size);
}

struct FieldDefinition {
	uint8_t number, size, base_type;

	FieldDefinition(istream& _is) {
		raw_read(_is, number);
		raw_read(_is, size);
		raw_read(_is, base_type);
	}
};

class definition_message {
private:
	istream& _is;
	int bytes_read = 0;
	vector<FieldDefinition> fields;
public:
	uint8_t Reserved, Architecture, NumFields;
	uint16_t GlobalMessageNumber;

	definition_message(istream& is) : _is(is) {
		GlobalMessageNumber = Reserved = Architecture = NumFields = 0;
		// just not to have warning, but it's necessary for the caller
		// to call a read_definition_mess() in order to have vars make sense
	}

	int read_definition_mess() {
		bytes_read = 0;
		fields.clear();

		raw_read(_is, Reserved);
		bytes_read++;
		raw_read(_is, Architecture);
		bytes_read++;
		raw_read(_is, GlobalMessageNumber);
		bytes_read += 2;
		raw_read(_is, NumFields);
		bytes_read++;

		for (auto i = 0; i < NumFields; i++) {
			fields.push_back(FieldDefinition(_is));
			bytes_read += 3;
		}

		return bytes_read;
	}

	auto get_last_bytes_read() { return bytes_read; }
	auto get_all_fields() { return fields; }
	auto get_field(int index) { return fields[index]; }
	auto get_datasize() {
		size_t size = 0;
		for (const auto& f : fields) {
			size += f.size;
		}
		return size;
	}
};

class FitFile {
private:
	ifstream is;
	ofstream os;

	uint8_t HeaderSize = 0;
	uint32_t DataSize = 0;
	uint16_t header_CRC = 0, header_CRCread = 0;
	uint16_t data_CRC = 0, data_CRCread = 0;

	struct global_def {
		vector<FieldDefinition> fields;
		uint16_t GlobalMessageNumber;
	};

	bool dumpHeader() {
		uint8_t ProtocolVersion;
		uint16_t ProfileVersion;
		char DataType[5];
		DataType[4] = 0;

		raw_read(is, HeaderSize);
		raw_read(is, ProtocolVersion);
		raw_read(is, ProfileVersion);
		raw_read(is, DataSize);
		raw_read(is, DataType, 4);

		/*if (HeaderSize < 1 || HeaderSize > 14)
			error("HeaderSize corrupted");
		if (string(DataType) != ".FIT") 
			error("DataType not \".FIT\"");*/

		is.seekg(0, ios_base::beg);
		for (size_t i = 0; i < HeaderSize - 2; i++) {
			uint8_t buff;
			raw_read(is, buff);
			FitCRC_Get16(header_CRC, buff);
		}
		raw_read(is, header_CRCread);
		if (header_CRC != header_CRCread)
			return false;
		return true;
	}

	void FitCRC_Get16(uint16_t& crc, uint8_t byte)
	{
		static const uint16_t crc_table[16] =
		{
			0x0000, 0xCC01, 0xD801, 0x1400, 0xF001, 0x3C00, 0x2800, 0xE401,
			0xA001, 0x6C00, 0x7800, 0xB401, 0x5000, 0x9C01, 0x8801, 0x4400
		};
		uint16_t tmp;
		// compute checksum of lower four bits of byte
		tmp = crc_table[crc & 0xF];
		crc = (crc >> 4) & 0x0FFF;
		crc = crc ^ tmp ^ crc_table[byte & 0xF];
		// now compute checksum of upper four bits of byte
		tmp = crc_table[crc & 0xF];
		crc = (crc >> 4) & 0x0FFF;
		crc = crc ^ tmp ^ crc_table[(byte >> 4) & 0xF];
	}

public:

	FitFile(const string& filename) : is(filename, ios::binary), os("debug_dump.txt") {

		if (!is)
			error("Error opening file input");

		if (!os)
			error("Error opening file debug_dump.txt");
	}

	void dump() {
		//cout << "Header reading" << endl;
		if (!dumpHeader())
			exit(EXIT_FAILURE);
		else
			cout << "Header CRC ok" << endl;

		auto remainingdata = DataSize;
		uint8_t read_8;
		uint8_t is_definition_mess = 0;
		definition_message curr_def_mess(is);
		uint8_t local_message_type;
		bool first_record = true;
		//map local_message_type to global
		unordered_map<uint8_t, global_def> global_def_map;

		while (remainingdata --> 0) {
			if (!raw_read(is, read_8)) 
				error("eof before reading all bytes");
			
			is_definition_mess = read_8 >> 4;
			local_message_type = read_8 & 0x0f;

			if (is_definition_mess) {
				curr_def_mess.read_definition_mess();
				remainingdata -= curr_def_mess.get_last_bytes_read();
				global_def tostore = global_def();
				tostore.fields = curr_def_mess.get_all_fields();
				tostore.GlobalMessageNumber = curr_def_mess.GlobalMessageNumber;
				global_def_map[local_message_type] = tostore;
			}
			else {
				/*os << "def message(" 
					<< curr_def_mess.GlobalMessageNumber 
					<< ", type: " << int(local_message_type) 
					<< ", lenght: " << 1 + curr_def_mess.get_datasize() << " bytes):" 
					<< endl;*/


				char buffer[32];
				auto curr_global_def = global_def_map[local_message_type];
				
				for (auto field : curr_global_def.fields) {
					if (!is.read(buffer, field.size)) error("eof before reading all bytes");
					remainingdata -= field.size;

					if (first_record and field.number == 4) {
						cout << "time_created = " << ((uint32_t*)buffer)[0] << endl;
						first_record = false;
					}

					if (curr_global_def.GlobalMessageNumber == 19 and field.number == 13) {
						uint16_t speedmms = ((uint16_t*)buffer)[0];
						double speedkmh = (double)speedmms * 3600 / 1'000'000;
						cout << "avg_speed = " << fixed << setprecision(3) << speedkmh << " km/h" << endl;
					}
				}
			}
		}

		is.seekg(- (int32_t) DataSize, ios_base::cur);
		for (size_t i = 0; i < DataSize; i++) {
			raw_read(is, read_8);
			FitCRC_Get16(data_CRC, read_8);
		}
		raw_read(is, data_CRCread);
		if (data_CRC != data_CRCread) {
			//cout << data_CRC << " but read " << data_CRCread << endl;
			exit(EXIT_FAILURE);
		}
		else
			cout << "File CRC ok" << endl;
	}
};

int main(int argc, char** argv)
{
	if (argc != 2)
		error("Wrong Syntax, should be: fitdump <input file .FIT>");

	FitFile fitfile = FitFile(string(argv[1]));
	fitfile.dump();
}