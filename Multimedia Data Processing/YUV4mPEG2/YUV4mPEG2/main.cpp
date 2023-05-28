#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cassert>
#include <cstdint>
#include <iomanip>
#include "mat.h"
#include "pgm.h"

int load_yuv4m(std::vector<mat<uint8_t>>& frames, const std::string& filename)
{
	std::ifstream is(filename, std::ios::binary);
	if (!is) {
		return -1;
	}

	std::string readstr;
	std::getline(is, readstr, ' ');
	if (readstr != "YUV4MPEG2") {
		return -2;
	}

	int w, h;
	std::string line;

	mat<uint8_t> matrix;

	std::getline(is, line);

	std::stringstream ss(line);
	std::string token;
	
	while (ss >> token) { // Extract word from the stream.
		switch (token[0]) {
		break; case 'W':
			w = stoi(token.substr(1, token.size()));
		break; case 'H':
			h = stoi(token.substr(1, token.size()));
		break; case 'C':
			if (token != "C420jpeg")
				return -5;
		break; case 'I':
			if (token != "Ip")
				return -6;
		break; case 'F':
		break; case 'A':
		break; case 'X':
		break; default: return -4;
		}
	}


	matrix.resize(h, w);
	while (1) {
		std::getline(is, readstr, char(0x0a));
		if (readstr.substr(0, 5)  != "FRAME")
			break;
		
		//frames.push_back
	}
	//img.resize(h, w);

	//for (int r = 0; r < img.rows(); ++r) {
	//	for (int c = 0; c < img.cols(); ++c) {
	//		img(r, c) = is.get();
	//	}
	//}

	return 0;
}


int main()
{
	std::vector<mat<uint8_t>> frames;

	std::cout << "Loading test.y4m file...";

	int returnfunct = load_yuv4m(frames, "test1.y4m");
	if (returnfunct !=0) {
		return returnfunct;
	}
	for (size_t i = 0; i < frames.size(); i++) {
		std::stringstream ss;
		ss << std::setw(3) << std::setfill('0');
		ss << "frame" << i << ".pgm";
		save_pgm(ss.str(), frames[i]);
	}
	std::cout << " done.\n";
	
	
	return 0;
}