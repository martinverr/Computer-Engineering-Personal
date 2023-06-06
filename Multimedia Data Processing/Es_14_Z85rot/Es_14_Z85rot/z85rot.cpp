#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>
#include <intrin.h>

using namespace std;


template <typename T>
istream& raw_read(istream& is, T& val, size_t size = sizeof(T)) {
	return is.read(reinterpret_cast<char*>(&val), size);
}


template <typename T>
ostream& raw_write(ostream& os, const T& val, size_t size = sizeof(T)) {
	return os.write(reinterpret_cast<const char*>(&val), size);
}


void error(const string& msg) {
	cout << msg;
	exit(EXIT_FAILURE);
}


template <typename T>
struct mat {
	int rows_, cols_;
	std::vector<T> data_;
	mat(int rows = 0, int cols = 0) : rows_(rows), cols_(cols), data_(rows* cols) {}

	void resize(int rows, int cols) {
		rows_ = rows;
		cols_ = cols;
		data_.resize(rows * cols);
	}

	const T& at(int r, int c) const {
		return data_[r * cols_ + c];
	}
	T& at(int r, int c) {
		return const_cast<T&>(static_cast<const mat*>(this)->at(r, c));
	}

	const T& operator()(int r, int c) const {
		return data_[r * cols_ + c];
	}
	T& operator()(int r, int c) {
		return data_[r * cols_ + c];
	}
	int rows() const { return rows_; }
	int cols() const { return cols_; }
	int size() const { return rows_ * cols_; }

	size_t raw_size() const {
		return rows_ * cols_ * sizeof(T);
	}
	const char* raw_data() const {
		return reinterpret_cast<const char*>(&data_[0]);
	}
};


struct Ppm {
private:
	typedef vector<uint8_t> rgb;
	mat<rgb> img_;

	void commentcheck_ppm(ifstream& is) {
		while (is.peek() == '#') {
			while (is.get() != '\n') {}
		}
	}
public:
	Ppm() : img_() {	}


	ostream& save_ppm(ofstream& os) {
		os << "P6" << ' ';
		os << img_.cols() << ' ' << img_.rows() << ' ';
		os << 255 << endl;

		auto cols = img_.cols();
		auto rows = img_.rows();

		for (auto r = 0; r < rows; r++) {
			for (auto c = 0; c < cols; c++) {
				for (auto ch = 0; ch < 3; ch++) {
					raw_write(os, img_(r, c)[ch]);
				}
			}
		}
		return os;
	}

	istream& load_ppm(ifstream& is) {
		char magicnum[3]; magicnum[2] = 0;
		int cols, rows, maxval;
		

		raw_read(is, magicnum, 2);
		if (string(magicnum) != "P6") error("error parsing .ppm");
		commentcheck_ppm(is);
		is.get();
		commentcheck_ppm(is);

		is >> cols;
		commentcheck_ppm(is);
		is.get();
		commentcheck_ppm(is);
		
		is >> rows;
		commentcheck_ppm(is);
		is.get();
		commentcheck_ppm(is);
		
		is >> maxval;
		commentcheck_ppm(is);
		is.get();
		
		if(cols < 0 or rows < 0 or maxval < 0)  error("error parsing .ppm");
		img_ = mat<rgb>(rows, cols);

		for (auto r = 0; r < rows; r++) {
			for (auto c = 0; c < cols; c++) {
				img_(r, c) = rgb(3);
				for (auto ch = 0; ch < 3; ch++) {
					raw_read(is, img_(r, c)[ch]);
				}
			}
		}
		return is;
	}


	auto getMat() { return img_; }

	auto getData() { return img_.data_; }

	auto getRawData() { 
		vector<uint8_t> rawData;
		auto rows = img_.rows();
		auto cols = img_.cols();

		for (auto r = 0; r < rows; r++) {
			for (auto c = 0; c < cols; c++) {
				for (auto ch = 0; ch < 3; ch++) {
					rawData.push_back(img_(r, c)[ch]);
				}
			}
		}

		return rawData;
	}

};

class Ascii85 {
private:
	stringstream ascii85_decoded;
	int rotateN;
	char mapping[86] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ.-:+=^!/*?&<>()[]{}@%$#";


	void _print_to85(uint32_t val, stringstream& convertingval) {
		if (val / 85)
			_print_to85(val / 85, convertingval);
		convertingval << val % 85;
	}
	void print_to85(const uint32_t& val) {
		stringstream convertedval = stringstream();

		_print_to85(uint32_t(val), convertedval);
		cout << convertedval.str();
	}

	vector<uint8_t> to85(uint32_t val) {
		vector<uint8_t> convertedval(5);
		fill(convertedval.begin(), convertedval.end(), val);

		for (auto i = 0; i < 5; i++) {
			convertedval[i] = val % 85;
			val /= 85;
		}
		reverse(convertedval.begin(), convertedval.end());
		return convertedval;
	}

public:
	vector<uint8_t> data;
	vector<uint32_t> data32;

	Ascii85(const vector<uint8_t> & data, int rotateN=0) : ascii85_decoded() {
		this->data = data;
		this->rotateN = rotateN;
		auto size = data.size();
		for (size_t i = 0; i < size; i+=4) {
			uint32_t tmp = *(uint32_t*)&(data[i]);
			data32.push_back(_byteswap_ulong(tmp));
		}
	}

	Ascii85(const vector<uint32_t>& data, int rotateN = 0) : ascii85_decoded() {
		this->data32 = data;
		this->rotateN = rotateN;
	}

	auto convert() {

		vector<uint8_t> converted;

		auto r = 0;
		for (const auto& val : data32) {
			auto tmp = to85(val);
			for (size_t i = 0; i < 5; i++) {
				auto rotatedindex = tmp[i] - r%85;
				if (rotatedindex < 0)
					rotatedindex += 85;
				r += rotateN;
				tmp[i] = mapping[rotatedindex];
			}
			converted.insert(converted.end(), tmp.begin(), tmp.end());
		}

		for (const auto& singlechar : converted)
			ascii85_decoded << singlechar;

		return converted;
	}

	string getDecodedTxt() {
		return ascii85_decoded.str();
	}
};


void compression(const int & rot, const string & ifilename, const string& ofilename) {
	ifstream is(ifilename);
	ofstream os(ofilename);
	if (!is)
		error("Error opening <input file>");
	if (!os)
		error("Error opening <output file>");

	Ppm ppm;
	ppm.load_ppm(is);
	auto data = ppm.getRawData();

	Ascii85 ascii85(data, rot);
	auto data_ascii85 = ascii85.convert();
	
	os << ppm.getMat().rows() << "," << ppm.getMat().cols() << ",";
	os << ascii85.getDecodedTxt();
}


int main(int argc, char** argv) {
	if (argc != 5)
		error("Wrong syntax, should be: Z85rot {c | d} <N> <input file> <output file>\n");
	
	int N;
	char choice;
	string ifilename, ofilename;

	try
	{
		choice = argv[1][0];
		stringstream(argv[2]) >> N;
	}
	catch (const std::exception&)
	{
		error("error parsing argument {c|d} <N> wrong\n");
	}

	ifilename = string(argv[3]);
	ofilename = string(argv[4]);

	compression(N, ifilename, ofilename);

	return EXIT_SUCCESS;
}