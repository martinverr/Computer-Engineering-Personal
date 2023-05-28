#include <iostream>
#include <fstream>	
#include <vector>
#include <iterator>
#include <cstdint>
#include <iomanip>
#include <unordered_map>


template<typename T>
std::ostream& raw_write(std::ostream& os, const T& val, size_t size = sizeof(T)) {
	return os.write(reinterpret_cast<const char*>(&val), size);
}

int main(int argc, char * argv[]) {
	if (argc != 3) {
		std::cout << "Wrong syntax, should be 'frequencies <input file> <output file>'";
	}

	std::ifstream is(argv[1]);
	if (!is) {
		std::cout << "Error opening input file.\n";
		return 1;
	}

	std::ofstream os(argv[2], std::ios::binary);
	if (!os) {
		std::cout << "Error opening output file.\n";
		return 1;
	}

	using namespace std;


	std::vector<int32_t> v{ istream_iterator<int32_t>(is) , istream_iterator<int32_t>() };

	for (const auto &x : v) {
		raw_write<int32_t>(os, x);
	}
	/*
	//266 -> 0000.0001.0000.1010 -> 10A -> 0A 01 00 00 in little endian 32 bit
	int32_t num = 266;
	os.write((const char *)&num, 4);
	// ma evitare i cast quando possibile in C++, esempio in C:
	int a = 7;
	double b = (double)a / 10;
	// in C++:
	double c = static_cast<double>(a) / 10;
	
	const char s[] = "Prova";
	const char *p = s;
	char *q = const_cast<char*> s;

	int32_t x = 266;
	int32_t *px = &x;
	char *qx = reinterpret_cast<char*>(px);
	*/
}