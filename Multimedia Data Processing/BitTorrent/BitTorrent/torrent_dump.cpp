#include <iostream>
#include <fstream>
#include <vector>

#define SYNTAX_ERROR_EXIT_CODE -1
#define NOT_A_TORRENT_EXIT_CODE -2
#define FILE_ERROR_EXIT_CODE -3


using namespace std;

class TorrentElement {
private:
	vector<TorrentElement> elements;
public:
	enum Type {
		stringEl = 1,
		intEl = 2,
		listEl = 3,
		dictEl = 4,
		rootEl = 0
	};
	Type _type = rootEl;

	int intEl;
	string stringEl;

	TorrentElement() {
		_type = rootEl;
	}

	TorrentElement(Type type) {
		_type = type;
	}

	Type getType() {return _type;}
};

void read_torrent(ifstream& is, TorrentElement& torrent_root) {
	char read_char = is.peek();
	TorrentElement torrent_el = TorrentElement();

	if (read_char >= '0', read_char <= '9')
		torrent_el._type;

	switch (read_char) {
	break; case 'i':
	break; case 'l':
	break; case 'f':
	break; case 'd':
	}
}

int main(int argc, char** argv) {
	if (argc != 2) {
		cout << "Wrong syntax, correct use: torrent_dump <file.torrent>";
		return SYNTAX_ERROR_EXIT_CODE;
	}

	string filename(argv[1]);

	if (filename.substr(filename.find_last_of('.'), string::npos) == ".torrent") {
		cout << "File" << filename << "is not a.torrent";
		return NOT_A_TORRENT_EXIT_CODE;
	}

	ifstream is(filename);

	if (!is) {
		cout << "Error opening" << filename;
		return FILE_ERROR_EXIT_CODE;
	}
	
	TorrentElement torrent_data;

	read_torrent(is, torrent_data);
}