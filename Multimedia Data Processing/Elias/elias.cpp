#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <assert.h>

#include "raw_read_write.h"

using namespace std;


class bitwriter {
	uint8_t buffer_;
	int n_ = 0;
	std::ostream& os_;

	std::ostream& write_bit(uint32_t bit) {
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

	std::ostream& write(uint32_t u, uint8_t n) {
		//while (n --> 0) {
		//  write_bit(u >> n);
		//}
		for (int i = n - 1; i >= 0; --i) {
			write_bit(u >> i);
		}
		return os_;
	}

	std::ostream& operator()(uint32_t u, uint8_t n) {
		return write(u, n);
	}

	std::ostream& flush(uint32_t bit = 0) {
		while (n_ > 0) {
			write_bit(bit);
		}
		return os_;
	}

	~bitwriter() {
		flush();
	}
};

class bitreader {
	uint8_t buffer_;
	uint8_t n_ = 0;
	std::istream& is_;

public:
	bitreader(std::istream& is) : is_(is) {}

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
		while (n-- > 0) {
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

int compression(char* ifilename, char* ofilename) {

	ifstream is(ifilename);
	if (!is) {
		cout << "Error opening file " << ifilename;
		return -3;
	}

	vector<int32_t> v{
	istream_iterator<int32_t>(is),
	istream_iterator<int32_t>()
	};


	for (size_t i = 0; i < v.size(); i++) {
		auto num = v[i];
		v[i] = num >= 0 ? num * 2 + 1 : -num * 2;
	} 
	/*for (auto num : v) {
		cout << num << '\n';
	}*/

	ofstream os(ofilename, ios::binary);
	if (!os) {
		cout << "Error opening file " << ofilename;
		return -3;
	}

	bitwriter bw(os);
	for (const auto& num : v) {
		uint8_t nbits = ((uint8_t) log2(num)) * 2 + 1; //todo?: cast
		bw(num, nbits);
	}

	return 0;
}

int decompression(char* ifilename, char* ofilename) {
	ifstream is(ifilename, ios::binary);
	if (!is) {
		cout << "Error opening file " << ifilename;
		return -3;
	}
	
	bitreader br(is);
	int32_t num = 0;
	uint8_t zeros = 0;
	std::vector<int32_t> v;

	while (1) {
		num = br(1);
		if (!br) {
			break;
		}

		if (num == 0) {
			zeros++;
			continue;
		}


		// we are here if we found a bit 1

		num = br(zeros);
		if (!br) {
			break;
		}

		//add first significant bit '1'
		num += 1 << zeros;
		//mapping
		num = num % 2? num / 2 : -num / 2;


		v.push_back(num);
		zeros = 0;
	}


	ofstream os(ofilename);
	if (!os) {
		cout << "Error opening file " << ofilename;
		return -3;
	}

	if (!os) {
		return 1;
	}

	copy(v.begin(), v.end(),
		std::ostream_iterator<int32_t>(os, "\n"));

	return 0;
}



int main(int argc, char* argv[]) {
	if (argc != 4) {
		cout << "Wrong syntax, correct usage should be 'elias [c|d] <filein> <fileout>";
		return -1;
	}

	char choice = 0;

	if (strcmp(argv[1], "c") == 0) choice = 'c';
	if (strcmp(argv[1], "d") == 0) choice = 'd';
	
	switch (choice) {
	case 'c':
		cout << "proceeding with compression\n";
		return compression(argv[2], argv[3]);
	case 'd':
		cout << "proceeding with decompression\n";
		return decompression(argv[2], argv[3]);
	default:
		cout << "choice not valid\n";
		return -2;
	}

	return 0;
}