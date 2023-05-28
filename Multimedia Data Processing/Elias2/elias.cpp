#include <fstream>
#include <iostream>
#include <vector>


#define SYNTAX_ERROR_CODE 1
#define OPENING_INPUTFILE_ERROR_CODE 2
#define OPENING_OUTPUTFILE_ERROR_CODE 3
 
using namespace std;

template<typename T>
std::istream &raw_read(std::istream &is, T &val, size_t size = sizeof(T)) {
	return is.read(reinterpret_cast<char *>(&val), size);
}

class bitreader {
	uint8_t buffer_;
	uint8_t n_ = 0;
	std::istream& is_;

public:
	bitreader(std::istream &is) : is_(is) {}

	uint32_t read_bit() {
		if (n_ == 0) {
			raw_read(is_, buffer_);
			n_ = 8;
		}
		--n_;
		return (buffer_ >> n_) & 1;
	}

	uint32_t read(uint8_t n) {
		uint32_t u = 0;
		while (n --> 0) {
			u = (u << 1) | read_bit();
		}
		return u;
	}

	uint32_t operator()(uint8_t n) {
		return read(n);
	}

	bool fail() const {
		return is_.fail();
	}

	explicit operator bool() const {
		return !fail();
	}
};

template<typename T>
std::ostream &raw_write(std::ostream &os, const T &val, size_t size = sizeof(T)) {
	return os.write(reinterpret_cast<const char *>(&val), size);
}

class bitwriter {
	uint8_t buffer_;
	int n_ = 0;
	std::ostream& os_;

	std::ostream &write_bit(uint32_t bit) {
		buffer_ = (buffer_ << 1) | (bit & 1);
		++n_;
		if (n_ == 8) {
			raw_write(os_, buffer_);
			n_ = 0;
		}
		return os_;
	}

public:
	bitwriter(std::ostream& os) : os_(os) {}

	std::ostream &write(uint32_t u, uint8_t n) {
		//while (n --> 0) {
		//  write_bit(u >> n);
		//}
		for (int i = n - 1; i >= 0; --i) {
			write_bit(u >> i);
		}
		return os_;
	}

	std::ostream &operator()(uint32_t u, uint8_t n) {
		return write(u, n);
	}

	std::ostream &flush(uint32_t bit = 0) {
		while (n_ > 0) {
			write_bit(bit);
		}
		return os_;
	}

	~bitwriter() {
		flush();
	}
};


void _mapping(vector<int32_t> & numbers){
    for(size_t i = 0; i<numbers.size(); i++){
        if (numbers[i] >=0)
            numbers[i] = numbers[i] * 2 + 1;
        else
            numbers[i] = -numbers[i]*2; 
    }
}

int32_t _unmap(uint32_t num){    
    if (num % 2)
        return (int32_t)num/2;
    else
        return -(int32_t)num/2; 
}

int _class(uint32_t num){
    int zeros = 0;

    while(num /= 2) zeros++;

    return zeros;
}

int compression(const string & ifilename, const string & ofilename){
    ifstream is{ifilename};
    if(!is){
        cout << "Error opening inputfile '" << ifilename << "'\n";
        return OPENING_INPUTFILE_ERROR_CODE;
    }

    vector<int32_t> numbers{
	istream_iterator<int32_t>(is),
	istream_iterator<int32_t>()
	};

    _mapping(numbers);

    ofstream os{ofilename, ios::binary};
    if(!os){
        cout << "Error opening outputfile '" << ofilename << "'\n";
        return OPENING_OUTPUTFILE_ERROR_CODE;
    }
    bitwriter bw(os);

    for(auto number : numbers){
        bw.write(0, _class(number));
        bw.write(number, _class(number)+1);
    }

    return 0;
}

int decompression(const string & ifilename, const string & ofilename){
    ifstream is{ifilename, ios::binary};
    if(!is){
        cout << "Error opening inputfile '" << ifilename << "'\n";
        return OPENING_INPUTFILE_ERROR_CODE;
    }
    ofstream os{ofilename};
    if(!os){
        cout << "Error opening outputfile '" << ofilename << "'\n";
        return OPENING_OUTPUTFILE_ERROR_CODE;
    }

    bitreader br(is);
    size_t nbits = 0;
    vector<int32_t> numbers;
    while(br){
        while(br.read_bit() == 0) nbits++;
        if(br)
            numbers.push_back(br(nbits) + (1 << nbits));
        nbits = 0;
    }

    for (auto number : numbers){
        os << _unmap(number) << '\n';
    }

    return 0;
}

int main(int argc, char ** argv){
    if(argc!=4){
        cout << "Wrong syntax, should be 'elias c|d <inputfile> <outputfile>'";
        return SYNTAX_ERROR_CODE;
    }

    string choice = argv[1];
    if(choice == "c")
        return compression(argv[2], argv[3]);
    else if(choice == "d")
        return decompression(argv[2], argv[3]);
    else{
        cout << "Wrong syntax, should be 'elias c|d <inputfile> <outputfile>'";
        return SYNTAX_ERROR_CODE;
    }
    

    return 0;
}