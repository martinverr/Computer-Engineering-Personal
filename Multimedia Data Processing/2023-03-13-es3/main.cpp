#include <iostream>
#include <fstream>	
#include <vector>
#include <iterator>
#include <cstdint>
#include <iomanip>
#include <unordered_map>


template<typename T>
std::istream& raw_read(std::istream& is, T& val, size_t size = sizeof(T)) {
	return is.read(reinterpret_cast<char *>(&val), size);
}

int main(int argc, char * argv[]) {
	if (argc != 3) {
		std::cout << "Wrong syntax, should be 'frequencies <input file> <output file>'";
	}

	std::ifstream is(argv[1], std::ios::binary);
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


	std::vector<int32_t> v{ istream_iterator<int32_t>(is) , istream_iterator<int32_t>() };

	while(1){
		int32_t valread;
		if (!raw_read(is, valread)) {
			break;
		}
		v.push_back(valread);
	}

	for (const auto &x : v) {
		os << x << '/n';
	}
}