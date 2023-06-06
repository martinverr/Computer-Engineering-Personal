#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>


using namespace std;

template <typename T>
istream & raw_read(ifstream &is, T& val, size_t size = sizeof(T)) {
	return is.read(reinterpret_cast<char*>(&val), size);
}

template <typename T>
ostream& raw_write(ofstream& os, const T& val, size_t size = sizeof(T)) {
	return os.write(reinterpret_cast<char*>(&val), size);
}


void error(const string & msg) {
	cout << msg << endl;
	exit(EXIT_FAILURE);
}

struct inputfile {
	string filename;
	int x = 0;
	int y = 0;

	inputfile(const string& filename, int x = 0, int y = 0) {
		this->filename = filename;
		this->x = x;
		this->y = y;
	}
};

vector<inputfile> parseCommandArgs(int argc, char ** argv) {
	vector<inputfile> inputfiles;

	for (int i = 3; i < argc; i++) {
		stringstream ss;
		ss << argv[i];

		if (ss.peek() == '-') {
			int current = ss.get();
			int next = ss.get();

			if (next != 'p') error("error parsing arguments, wrong sintax");

			int x = stoi(argv[++i]);
			int y = stoi(argv[++i]);

			stringstream filename;
			filename << argv[++i] << ".pam";
			inputfiles.emplace_back(filename.str(), x, y);
		}
		else {
			ss << ".pam";
			inputfiles.emplace_back(ss.str());
		}
	}

	return inputfiles;
}


template <typename T>
struct mat {
	int rows_, cols_;
	vector<T> data;
	
	mat(int rows = 0, int cols = 0) : rows_(rows), cols_(cols) {}

	void resize(int rows, int cols) {
		rows_ = rows;
		cols_ = cols;
		data.resize(rows * cols);
	}

	const T& at(int r, int c) const{
		return data.at(r * cols_ + c);
	}
	T& at(int r, int c) {
		return const_cast<T&>( at(r * cols_ + c) );
	}

	const T& operator()(int r, int c) const {
		return data[r * cols_ + c];
	}
	T& operator()(int r, int c) {
		return data[r * cols_ + c];
	}

	auto rows() { return rows_; }
	auto cols() { return cols_; }
	auto size() { return rows_ * cols_; }
	size_t rawsize() { return rows_* cols_ * sizeof(T); }
	const char* raw_data() const {
		return reinterpret_cast<const char*>(&data[0]);
	}
};

struct argb{
	float alpha = 0;
	uint8_t R=0, G=0, B = 0;
};



struct PAM {
	mat<argb> img;
	int offset_x, offset_y;

	PAM() : img(), offset_x(0), offset_y(0) {}
	PAM(const mat<argb>& data) : img(data), offset_x(0), offset_y(0) {}

	void load_from_file(const string& filename) {
		ifstream is(filename, ios::binary);
		if (!is)
			error("Error opening/reading" + filename);

		string magicnumber;
		getline(is, magicnumber);
		if (magicnumber != "P7") error("Error header file pam " + filename);

		int rows = 0;
		int cols = 0;
		int depth = 4;
		int maxval = 255;
		string tultype;

		string line;
		while (true) {
			getline(is, line);
			if (line == "ENDHDR")
				break;

			stringstream ss(line);
			string s;
			ss >> s;

			if (s.at(0) == '#') {
				continue;
			}
			else if (s == "HEIGHT") {
				ss >> rows;
				if (rows < 0)
					error(".pam HEIGHT reading error (negative)");
			}
			else if (s == "WIDTH") {
				ss >> cols;
				if (cols < 0)
					error(".pam WIDTH reading error (negative)");
			}
			else if (s == "DEPTH") {
				ss >> depth;
				if (depth != 3 and depth != 4)
					error(".pam DEPTH not supported");
			}
			else if (s == "MAXVAL") {
				ss >> maxval;
				if (maxval > 255)
					error(".pam MAXVAL not supported");
			}
			else if (s == "TUPLTYPE") {
				ss >> tultype;
				if (tultype != "RGB" and tultype != "RGB_ALPHA")
					error(".pam TULTYPE not supported");
			}
			else
				error(".pam header parsing error, header line not recognized");
		}

		rows += offset_y;
		cols += offset_x;

		img.resize(rows, cols);

		for (auto r = offset_y; r < rows; r++) {
			for (auto c = offset_x; c < cols; c++) {
				raw_read(is, img(r, c).R);
				raw_read(is, img(r, c).G);
				raw_read(is, img(r, c).B);
				if (depth == 3)
					img(r, c).alpha = 1;
				else if (depth == 4) {
					uint8_t alpha_int = 0;
					raw_read(is, alpha_int);
					img(r, c).alpha = static_cast<float>(alpha_int) / maxval;
				}
			}
		}

	}
	
	float combine_alpha(float alpha_b, float alpha_a) {
		return alpha_a + alpha_b * (1 - alpha_a);
	}

	uint8_t combine_color(uint8_t color_b, uint8_t color_a, float alpha_b, float alpha_a) {
		float color = color_a * alpha_a + color_b * alpha_b * (1 - alpha_a);
		color /= combine_alpha(alpha_a, alpha_b);

		return static_cast<uint8_t>(color);
	}


	void combine(const PAM& other) {
		if (img.size() == 0) {
			*this = other;
			return;
		}
		auto oldrows = img.rows();
		auto oldcols = img.cols();

		auto newrows = max(oldrows, other.img.rows_);
		auto newcols = max(oldcols, other.img.cols_);

		if (newrows > img.rows() or newcols > img.cols()) {
			mat<argb> tmp;
			tmp = img;
			img.data.clear();
			img.resize(newrows, newcols);

			for (auto r = 0; r < oldrows; r++) {
				for (auto c = 0; c < oldcols; c++) {
					img(r, c) = tmp(r, c);
				}
			}
		}



		for (auto r = 0; r < newrows; r++) {
			for (auto c = 0; c < newcols; c++) {
				bool old_OutOfIndex = r >= oldrows or c >= oldcols;
				bool new_OutOfIndex = r >= other.img.rows_ or c >= other.img.cols_;

				auto oldAlpha = old_OutOfIndex ?  0: img(r, c).alpha;
				auto oldB = old_OutOfIndex ? 0 : img(r, c).B;
				auto oldG = old_OutOfIndex ? 0 : img(r, c).G;
				auto oldR = old_OutOfIndex ? 0 : img(r, c).R;

				auto newAlpha = new_OutOfIndex ? 0 : other.img(r, c).alpha;
				auto newB = new_OutOfIndex ? 0 : other.img(r, c).B;
				auto newG = new_OutOfIndex ? 0 : other.img(r, c).G;
				auto newR = new_OutOfIndex ? 0 : other.img(r, c).R;

				if(newAlpha != 0)
					img(r, c).alpha = combine_alpha(oldAlpha, newAlpha);
				img(r, c).B = combine_color(oldB, newB, oldAlpha, newAlpha);
				img(r, c).G = combine_color(oldG, newG, oldAlpha, newAlpha);
				img(r, c).R = combine_color(oldR, newR, oldAlpha, newAlpha);
			}
		}

	}

	void save_to_file(ostream& os) {
		auto cols = img.cols();
		auto rows = img.rows();

		os << "P7" << endl;
		os << "WIDTH " << cols << endl;
		os << "HEIGHT " << rows << endl;
		os << "DEPTH 4" << endl;
		os << "MAXVAL 255" << endl;
		os << "TUPLTYPE RGB_ALPHA" << endl;
		os << "ENDHDR" << endl;

		for (auto r = 0; r < rows; r++) {
			for (auto c = 0; c < cols; c++) {
				os.put(img(r, c).R);
				os.put(img(r, c).G);
				os.put(img(r, c).B);
				os.put(static_cast<uint8_t>(img(r, c).alpha * 255));
			}
		}
	}

};


int main(int argc, char** argv) {
	string ofilename = string(argv[2]) + ".pam";
	ofstream os(ofilename, ios::binary);
	if (!os)
		error("Error opening file output");

	vector<inputfile> inputfiles = parseCommandArgs(argc, argv);

	cout << "Inputfiles parsed:" << endl;
	for (const auto& inputfile : inputfiles) {
		cout << '\t' << inputfile.filename
			<< ", x=" << inputfile.x 
			<< ", y=" << inputfile.y 
			<< endl;
	}
	cout << endl;

	vector<PAM> pams;
	
	for (const auto& inputfile : inputfiles) {
		cout << "Loading " << inputfile.filename << "...";
		
		PAM pam;
		pam.offset_x = inputfile.x;
		pam.offset_y = inputfile.y;
		mat<argb> matrix;
		pam.load_from_file(inputfile.filename);
		pams.push_back(pam);

		cout << " Done" << endl;
	}
	cout << endl;

	PAM combiningPam;
	//int i = 1;
	for (auto& pam : pams) {
		cout << "Combining " << pam.img.cols_ << "x" << pam.img.rows_ << "...";
		combiningPam.combine(pam);
		cout << " Done" << endl;
		
	
		//ofstream debugos("debug" + to_string(i) + ".pam", ios::binary);
		//if (!debugos)
		//	error("Error opening file output of debug");

		//combiningPam.save_to_file(debugos);
		//i++;
	}

	combiningPam.save_to_file(os);

	return EXIT_SUCCESS;
}