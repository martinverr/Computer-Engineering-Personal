#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <cstdint>
#include <iomanip>
#include <unordered_map>


int main(int argc, char * argv[]) {
	if (argc != 3) {
		std::cout << "Wrong syntax, should be 'frequencies <input file> <output file>'";
	}

	std::ifstream is(argv[1], std::ios::binary/*apertura in modalita' binaria'*/);
	if (!is) {
		std::cout << "Error opening input file.\n";
		return 1;
	}

	std::ofstream os(argv[2]);
	if (!os) {
		std::cout << "Error opening output file.\n";
		return 1;
	}

	using namespace std;
	std::unordered_map<int, uint32_t> count;
	while (1) {
		int num;
		num = is.get(); //get() puo' ritornare -1 per questo si ritorna un int e non un char
		if (num == EOF) break;
		count[num]++;
	}
	for (const auto &x : count) {
		os << setbase(16) << setw(2) << setfill('0') << uppercase << x.first;
		os << '\t' << setbase(10) << count[x.first] << '\n';
	}

	/* 
	uint32_t count[256];
	for (auto i = 0; i < 256; i++) count[i] = 0;
	while (1) {
		int num;
		num = is.get(); //get() puo' ritornare -1 per questo si ritorna un int e non un char
	if (num == EOF) break;
		count[num]++;
	}
	
	
	
	
	for (size_t i = 0; i < 256; i++) {
		if (count[i] > 0) {
			os << setbase(16) << setw(2) << setfill('0') << uppercase << i; 
			os << '\t' << setbase(10) << count[i] << '\n';
		}
	}
	*/

	/*
	std::istream_iterator<unsigned char> start(is);
	std::istream_iterator<unsigned char> stop;
	std::vector<unsigned char> v(start, stop);
	*/

	/*
	for (auto it = start; it != stop; ++it) {
		v.push_back(*it);
	}*/

}