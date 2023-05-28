/*
	Write a command line program in C++ with this syntax:
	write_int11 <filein.txt> <fileout.bin>
	The first parameter is the name of a text file that contains base 10 integers from - 1000 to 1000 separated
	by whitespace.The program must create a new file, with the name passed as the second parameter, with
	the same numbers saved as 11 - bit binary in 2’s complement.The bits are inserted in the file from the
	most significant to the least significant.The last byte of the file, if incomplete, is filled with bits equal to
	0. Since the incomplete byte will have at most 7 padding bits, there’s no risk of interpreting padding as
	another value.
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main(int argc, const char* argv[]) {

	if (argc != 3) {
		cout << "Wrong syntax, expected: main <inputfile> <outputfile>";
		return 1;
	}

	ifstream is(argv[1]);
	if (!is) {
		cout << "Error on opening input file " << argv[1];
		return 2;
	}

	ofstream os(argv[2], ios::binary);
	if (!os) {
		cout << "Error on opening output file " << argv[2];
		return 3;
	}

	vector<int32_t> v{ istream_iterator<int32_t>(is), istream_iterator<int32_t>() };


	char buffer[100];

	for (auto i = 0; i < v.size(); i++) {
		cout << v.at(i) << '\n';

		int32_t num = v.at(i);
	
		reinterpret_cast<char*>(&num);

	}

}