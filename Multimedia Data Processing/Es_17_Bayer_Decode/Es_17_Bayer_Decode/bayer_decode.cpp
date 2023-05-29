#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

template <typename T>
istream& raw_read(istream& is, T& val, size_t size = sizeof(T)) {
	return is.read(reinterpret_cast<char*>(&val), size);
}


template <typename T>
ostream& raw_write(ostream& os, const T& val, size_t size = sizeof(T)) {
	return os.write(reinterpret_cast<const char*>(&val), size);
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


class Pgm {
private:
	ifstream& is_;
	mat<uint8_t> img_;

	bool load_pgm() {
		string strbuffer;
		size_t width;
		size_t height;
		int maxval = 265;

		is_ >> strbuffer;
		if (strbuffer != "P5") return false;
		is_ >> width;
		is_ >> height;
		if (width < 0 || height < 0) return false;
		is_ >> maxval;
		if (maxval < 0 || maxval > 65535) return false;
		is_.get();
		//cout << "prima della tabella letto:" << is_.get()  << endl;

		/*
		vector<uint16_t> buffvec(size_t(height * width));
		is.read(reinterpret_cast<char*>(buffvec.data()), height*width*2);
		*/

		img_ = mat<uint8_t>(height, width);

		if (maxval > 255) { // for 2 byte per pixel
			for (auto r = 0; r < height; r++) {
				for (auto c = 0; c < width; c++) {

					uint16_t buffer = 0;
					raw_read(is_, buffer);

					uint16_t val = (buffer >> 8) | (buffer << 8);
					img_(r, c) = static_cast<uint8_t> (static_cast<double>(val) / 256);
				}
			}
		}
		else { // for 1 byte pixel
			vector<uint8_t> buffvec(height * width);
			is_.read(reinterpret_cast<char*>(buffvec.data()), height * width);
			img_.data_ = buffvec;
		}

		return true;
	}

public:
	Pgm(ifstream& is) : is_(is) {
		load_pgm();
	}

	ostream& save_pgm(ofstream& os) {
		os << "P5";
		os << ' ';
		os << img_.cols();
		os << ' ';
		os << img_.rows();
		os << ' ';
		os << 255;
		os << endl;
		os.write(img_.raw_data(), img_.raw_size());

		return os;
	}

	auto data() { return img_; }
};


class Ppm {
private:
	typedef vector<uint8_t> rgb;
	mat<uint8_t> gray_img_;
	mat<rgb> img_;

	char pixel_type(int r, int c) {
		// blue row
		if (r & 1)
			if (c & 1)
				return 2;
			else
				return 1;
		// red row
		else
			if (c & 1)
				return 1;
			else
				return 0;
	}

	void bayer_ppm() {
		auto cols = gray_img_.cols();
		auto rows = gray_img_.rows();

		img_ = mat<rgb>(rows, cols);

		for (auto r = 0; r < rows; r++) {
			for (auto c = 0; c < cols; c++) {
				img_(r, c) = rgb(3, 0);
				img_(r, c)[pixel_type(r, c)] = gray_img_(r, c);
			}
		}
	}
public:
	Ppm(mat<uint8_t> data) : gray_img_(data) {

		auto cols = gray_img_.cols();
		auto rows = gray_img_.rows();

		img_ = mat<rgb>(rows, cols);

		bayer_ppm();

	}

	ostream& save_ppm(ofstream& os) {
		os << "P6";
		os << ' ';
		os << img_.cols();
		os << ' ';
		os << img_.rows();
		os << ' ';
		os << 255;
		os << endl;

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

	void interpolateFirstPass() {
		auto cols = img_.cols();
		auto rows = img_.rows();

		double greenval;
		double X1, X3, X5, X7, X9;
		double G2, G4, G6, G8;
		double H, V;
		char px_type;

		for (auto r = 0; r < rows; r++) {
			for (auto c = 0; c < cols; c++) {
				px_type = pixel_type(r, c);

				if (px_type == 1) continue;

				X5 = img_(r, c)[px_type];

				X1 = r - 2 >= 0 ? img_(r - 2, c)[px_type] : 0;
				X3 = c - 2 >= 0 ? img_(r, c - 2)[px_type] : 0;
				X7 = c + 2 < cols ? img_(r, c + 2)[px_type] : 0;
				X9 = r + 2 < rows ? img_(r + 2, c)[px_type] : 0;

				G2 = r - 1 >= 0 ? img_(r - 1, c)[1] : 0;
				G4 = c - 1 >= 0 ? img_(r, c - 1)[1] : 0;
				G6 = c + 1 < cols ? img_(r, c + 1)[1] : 0;
				G8 = r + 1 < rows ? img_(r + 1, c)[1] : 0;

				H = abs(G4 - G6) + abs(X5 - X3 + X5 - X7);
				V = abs(G2 - G8) + abs(X5 - X1 + X5 - X9);

				if (H < V)
					greenval = (G4 + G6) / 2 + (X5 - X3 + X5 - X7) / 4;
				else if (H > V)
					greenval = (G2 + G8) / 2 + (X5 - X1 + X5 - X9) / 4;
				else
					greenval = (G2 + G4 + G6 + G8) / 4 + (X5 - X1 + X5 - X3 + X5 - X7 + X5 - X9) / 8;
				
				uint8_t greenval_8;

				if (greenval < 0) greenval_8 = 0;
				else if (greenval > 255) greenval_8 = 255;
				else greenval_8 = static_cast<uint8_t>(greenval);

				img_(r, c)[1] = greenval_8;
			}
		}
	}

	void interpolateSecondPass() {
		auto cols = img_.cols();
		auto rows = img_.rows();

		double N, P;
		double X1, X3, X5, X7, X9;
		double G1, G3, G5, G7, G9;
		double val;
		char px_type;

		for (auto r = 0; r < rows; r++) {
			for (auto c = 0; c < cols; c++) {
				px_type = pixel_type(r, c);

				if (px_type == 1) {
					double b1, b2, r1, r2;
					double bg1, bg2, rg1, rg2;
					double g = img_(r, c)[1];

					if (r & 1) {
						b1 = c - 1 >= 0 ? img_(r, c - 1)[2] : 0;
						b2 = c + 1 < cols ? img_(r, c + 1)[2] : 0;
						r1 = r - 1 >= 0 ? img_(r - 1, c)[0] : 0;
						r2 = r + 1 < rows ? img_(r + 1, c)[0] : 0;

						bg1 = c - 1 >= 0 ? img_(r, c - 1)[1] : 0;
						bg2 = c + 1 < cols ? img_(r, c + 1)[1] : 0;
						rg1 = r - 1 >= 0 ? img_(r - 1, c)[1] : 0;
						rg2 = r + 1 < rows ? img_(r + 1, c)[1] : 0;
					}
					else {
						r1 = c - 1 >= 0 ? img_(r, c - 1)[0] : 0;
						r2 = c + 1 < cols ? img_(r, c + 1)[0] : 0;
						b1 = r - 1 >= 0 ? img_(r - 1, c)[2] : 0;
						b2 = r + 1 < rows ? img_(r + 1, c)[2] : 0;

						rg1 = c - 1 >= 0 ? img_(r, c - 1)[1] : 0;
						rg2 = c + 1 < cols ? img_(r, c + 1)[1] : 0;
						bg1 = r - 1 >= 0 ? img_(r - 1, c)[1] : 0;
						bg2 = r + 1 < rows ? img_(r + 1, c)[1] : 0;
					}
					double b = (b1 + b2) / 2 + (g - bg1 + g - bg2) / 4;
					double red = (r1 + r2) / 2 + (g - rg1 + g - rg2) / 4;
					uint8_t b_8 = 0;
					uint8_t r_8 = 0;

					if (b < 0) b_8 = 0;
					else if (b > 255) b_8 = 255;
					else b_8 = static_cast<uint8_t>(b);

					if (red < 0) r_8 = 0;
					else if (red > 255) r_8 = 255;
					else r_8 = static_cast<uint8_t>(red);

					img_(r, c)[0] = r_8;
					img_(r, c)[2] = b_8;
					continue;
				}


				if (px_type == 0) px_type = 2;
				else if (px_type == 2) px_type = 0;

				X5 = img_(r, c)[pixel_type(r, c)];
				G5 = img_(r, c)[1];

				X1 = r - 1 >= 0 and c - 1 >= 0 ? img_(r - 1, c - 1)[px_type] : 0;
				G1 = r - 1 >= 0 and c - 1 >= 0 ? img_(r - 1, c - 1)[1] : 0;
				X3 = r - 1 >= 0 and c + 1 < cols ? img_(r - 1, c + 1)[px_type] : 0;
				G3 = r - 1 >= 0 and c + 1 < cols ? img_(r - 1, c + 1)[1] : 0;
				X7 = r + 1 < rows and c - 1 >= 0 ? img_(r + 1, c - 1)[px_type] : 0;
				G7 = r + 1 < rows and c - 1 >= 0 ? img_(r + 1, c - 1)[1] : 0;
				X9 = r + 1 < rows and c + 1 < cols ? img_(r + 1, c + 1)[px_type] : 0;
				G9 = r + 1 < rows and c + 1 < cols ? img_(r + 1, c + 1)[1] : 0;


				N = abs(X1 - X9) + abs(G5 - G1 + G5 - G9);
				P = abs(X3 - X7) + abs(G5 - G3 + G5 - G7);

				if (N < P)
					val = (X1 + X9) / 2 + (G5 - G1 + G5 - G9) / 4;
				else if (N > P)
					val = (X3 + X7) / 2 + (G5 - G3 + G5 - G7) / 4;
				else
					val = (X1 + X3 + X7 + X9) / 4 +
					(G5 - G1 + G5 - G3 + G5 - G7 + G5 - G9) / 8;

				uint8_t val_8;
				if (val < 0) val_8 = 0;
				else if (val > 255) val_8 = 255;
				else val_8 = static_cast<uint8_t>(val);

				img_(r, c)[px_type] = val_8;
			}
		}
	}

};


int main(int argc, char** argv) {
	if (argc != 3) {
		cout << "Wrong syntax, should be bayer_decode <input file.PGM> <output prefix>";
		return EXIT_FAILURE;
	}

	ifstream is(argv[1], ios::binary);
	if (!is) {
		cout << "Error opening file input\n";
		return EXIT_FAILURE;
	}

	Pgm pgm(is);

	ofstream os(string(argv[2]) + "_gray.pgm", ios::binary);
	if (!os) {
		cout << "Error opening file output pgm\n";
		return EXIT_FAILURE;
	}

	pgm.save_pgm(os);



	ofstream os2(string(argv[2]) + "_bayer.ppm", ios::binary);
	if (!os2) {
		cout << "Error opening file output _bayer.ppm\n";
		return EXIT_FAILURE;
	}

	ofstream os3(string(argv[2]) + "_green.ppm", ios::binary);
	if (!os3) {
		cout << "Error opening file output _green.ppm\n";
		return EXIT_FAILURE;
	}

	ofstream os4(string(argv[2]) + "_interp.ppm", ios::binary);
	if (!os4) {
		cout << "Error opening file output _interp.ppm\n";
		return EXIT_FAILURE;
	}

	Ppm ppm(pgm.data());
	ppm.save_ppm(os2);
	ppm.interpolateFirstPass();
	ppm.save_ppm(os3);
	ppm.interpolateSecondPass();
	ppm.save_ppm(os4);
	return EXIT_SUCCESS;
}