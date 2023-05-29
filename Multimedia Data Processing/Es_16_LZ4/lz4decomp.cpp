#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

template <typename T>
istream& raw_read(istream& is, T& val, size_t size = sizeof(T)) {
	return is.read(reinterpret_cast<char*>(&val), size);
}

class Lz4 {
private:
	vector<char> sequence;
	istream &_is;
	ostream& _os;


	void run(uint16_t offset, size_t match, bool verbose = false) {
		auto currpos = sequence.size();
		for (auto i = currpos - offset; match > 0; i++) {
			if (i == currpos)
				i = currpos - offset;
			if (verbose)
				cout << sequence[i];
			sequence.push_back(sequence[i]);
			--match;
		}
	}
public:
	Lz4(istream& is, ostream& os) : _is(is), _os(os) {}

	void read_lz4_block(uint32_t block_size, bool verbose = false) {
		uint8_t token, literal_buff;
		uint16_t offset;
		size_t L;
		size_t match_len;

		while (block_size > 0) {
			//token
			raw_read(_is, token);
			L = token >> 4;
			match_len = token & 0x0f;
			block_size--;


			// literals
			if (L == 15) {
				uint8_t addingsize = 255;
				while (addingsize == 255) {
					raw_read(_is, addingsize);
					L += addingsize;
					block_size--;
				}
			}

			while(L-->0){
				raw_read(_is, literal_buff);
				block_size--;
				sequence.push_back(literal_buff);

				if(verbose)
				cout << literal_buff;
			}
			if (block_size <= 0)
				return;

			//offset
			raw_read(_is, offset);
			block_size -= 2;

			// match
			if (match_len == 15) {
				uint8_t addingsize = 255;
				while (addingsize == 255) {
					raw_read(_is, addingsize);
					match_len += addingsize;
					block_size--;
				}
			}

			match_len += 4;
			run(offset, match_len, verbose);
		}
	}

	void write(){
		_os << string(sequence.begin(), sequence.end());
	}

	string get_decoded_block() const{
		return string(sequence.begin(), sequence.end());
	}
};



void decompress(istream& is, ostream& os, bool verbose = false) {
	char byteread;
	char valueread[4];
	uint32_t unc_file_lenght;
	uint32_t block_size;

	is >> byteread;
	if(byteread != 0x03) exit(EXIT_FAILURE);
	
	is >> byteread;
	if (byteread != 0x21) exit(EXIT_FAILURE); 

	is >> byteread;
	if (byteread != 0x4c) exit(EXIT_FAILURE);
	
	is >> byteread;
	if (byteread != 0x18) exit(EXIT_FAILURE);

	raw_read(is, unc_file_lenght);
	raw_read(is, valueread);
	if (valueread[0] != 0 or valueread[1] != 0 or valueread[2] != 0 or valueread[3] != 0x4D)
		exit(EXIT_FAILURE);
	
	cout << "file lenght: " << unc_file_lenght << endl;

	Lz4 lz4(is, os);

	while (raw_read(is, block_size)) {
		lz4.read_lz4_block(block_size, verbose);
	}
	lz4.write();
}


int main(int argc, char** argv) {
	if (argc != 3) {
		cout << "Wrong syntax, should be: lz4decomp <input file> <output file>";
	}

	ifstream is(argv[1], ios::binary);
	if (!is) {
		cout << "Error opening file input: " << argv[1];
	}

	ofstream os(argv[2], ios::binary);
	if (!os) {
		cout << "Error opening file output: " << argv[2];
	}

	cout << "Decompressing " << argv [1] << endl;
	decompress(is, os, false);


	return EXIT_SUCCESS;
}