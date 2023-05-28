#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cassert>
#include <cstdint>
#include <array>

template <typename T>
struct mat {
	int rows_, cols_;
	std::vector<T> data_;

	mat(int rows = 0, int cols = 0) : rows_(rows), cols_(cols), data_(rows*cols) {}

	void resize(int rows, int cols) {
		rows_ = rows;
		cols_ = cols;
		data_.resize(rows * cols);
	}

	const T& at(int r, int c) const {
		assert(r >= 0 && r < rows_ && c>=0 && c < cols_);
		return data_[r * cols_ + c];
	}
	T& at(int r, int c) {
		return const_cast<T&>(static_cast<const mat*>(this)->at(r, c));
	}

	const T &operator()(int r, int c) const {
		assert(r >= 0 && r < rows_ && c>=0 && c < cols_);
		return data_[r * cols_ + c];
	}
	T &operator()(int r, int c) {
		assert(r >= 0 && r < rows_ && c>=0 && c < cols_);
		return data_[r * cols_ + c];
	}

	int rows() const { return rows_; }
	int cols() const { return cols_; }
	int size() const { return rows_ * cols_; }

	size_t raw_size() const {
		return rows_ * cols_ * sizeof(T);
	}
	const char *raw_data() const {
		return reinterpret_cast<const char *>(&data_[0]);
	}
};

bool save_pam(const mat<uint8_t> &img, const std::string& filename)
{
	std::ofstream os(filename, std::ios::binary);
	if (!os) {
		return false;
	}
	os << "P7\n";
	os << "WIDTH " << img.cols() << "\n";
	os << "HEIGHT " << img.rows() << "\n";
	os << "DEPTH 1\n";
	os << "MAXVAL 255\n";
	os << "TUPLTYPE GRAYSCALE\n";
	os << "ENDHDR\n";

	for (int r = 0; r < img.rows(); ++r) {
		for (int c = 0; c < img.cols(); ++c) {
			os.put(img(r, c));
		}
	}

	//os.write(img.raw_data(), img.raw_size());

	return true;
}

bool load_pam(mat<uint8_t> &img, const std::string &filename)
{
	std::ifstream is(filename, std::ios::binary);
	if (!is) {
		return false;
	}

	std::string magic_number;
	std::getline(is, magic_number);
	if (magic_number != "P7") {
		return false;
	}

	int w, h;
	while (1) {
		std::string line;
		std::getline(is, line);
		if (line == "ENDHDR") {
			break;
		}
		std::stringstream ss(line);
		std::string token;
		ss >> token;
		if (token == "WIDTH") {
			ss >> w;
		}
		else if (token == "HEIGHT") {
			ss >> h;
		}
		else if (token == "DEPTH") {
			int depth;
			ss >> depth;
			if (depth != 1) {
				return false;
			}
		}
		else if (token == "MAXVAL") {
			int maxval;
			ss >> maxval;
			if (maxval != 255) {
				return false;
			}
		}
		else if (token == "TUPLTYPE") {
			std::string tupltype;
			ss >> tupltype;
			if (tupltype != "GRAYSCALE") {
				return false;
			}
		}
		else {
			return false;
		}
	}

	img.resize(h, w);

	for (int r = 0; r < img.rows(); ++r) {
		for (int c = 0; c < img.cols(); ++c) {
			img(r, c) = is.get();
		}
	}

	return true;
}

using rgb = std::array<uint8_t, 3>;

bool save_pam(const mat<rgb> &img, const std::string &filename)
{
	std::ofstream os(filename, std::ios::binary);
	if (!os) {
		return false;
	}
	os << "P7\n";
	os << "WIDTH " << img.cols() << "\n";
	os << "HEIGHT " << img.rows() << "\n";
	os << "DEPTH 3\n";
	os << "MAXVAL 255\n";
	os << "TUPLTYPE RGB\n";
	os << "ENDHDR\n";

	for (int r = 0; r < img.rows(); ++r) {
		for (int c = 0; c < img.cols(); ++c) {
			os.put(img(r, c)[0]);
			os.put(img(r, c)[1]);
			os.put(img(r, c)[2]);
		}
	}

	//os.write(img.raw_data(), img.raw_size());

	return true;
}

bool load_pam(mat<rgb> &img, const std::string &filename)
{
	std::ifstream is(filename, std::ios::binary);
	if (!is) {
		return false;
	}

	std::string magic_number;
	std::getline(is, magic_number);
	if (magic_number != "P7") {
		return false;
	}

	int w, h;
	while (1) {
		std::string line;
		std::getline(is, line);
		if (line == "ENDHDR") {
			break;
		}
		std::stringstream ss(line);
		std::string token;
		ss >> token;
		if (token == "WIDTH") {
			ss >> w;
		}
		else if (token == "HEIGHT") {
			ss >> h;
		}
		else if (token == "DEPTH") {
			int depth;
			ss >> depth;
			if (depth != 3) {
				return false;
			}
		}
		else if (token == "MAXVAL") {
			int maxval;
			ss >> maxval;
			if (maxval != 255) {
				return false;
			}
		}
		else if (token == "TUPLTYPE") {
			std::string tupltype;
			ss >> tupltype;
			if (tupltype != "RGB") {
				return false;
			}
		}
		else {
			return false;
		}
	}

	img.resize(h, w);

	for (int r = 0; r < img.rows(); ++r) {
		for (int c = 0; c < img.cols(); ++c) {
			img(r, c)[0] = is.get();
			img(r, c)[1] = is.get();
			img(r, c)[2] = is.get();
		}
	}

	return true;
}


mat<uint8_t> split_dim(const mat<rgb> & img, const int & dim){
	auto rows = img.rows();
	auto cols = img.cols();
	
	mat<uint8_t> result(rows, cols);
	for(int r = 0; r<rows; r++){
		for(int c = 0; c<cols; c++){
			result(r, c) = img(r,c)[dim];
		}	
	}

	return result;
}

bool split(const std::string & filename){
	mat<rgb> img;
    if(!load_pam(img, filename))
		return false;
    
	mat<uint8_t> R(split_dim(img, 0));
	mat<uint8_t> G(split_dim(img, 1));
	mat<uint8_t> B(split_dim(img, 2));
	std::string partial_filename = filename.substr(0, filename.find(".pam"));
	
	save_pam(R, partial_filename + "_R.pam");
	save_pam(G, partial_filename + "_G.pam");
	save_pam(B, partial_filename + "_B.pam");

	return true;
}


int main(int argc, char* argv[]) {
	if (argc != 2) {
		std::cout << "Wrong syntax, correct usage should be 'split <filename>";
		return EXIT_FAILURE;
	}

    if(!split(argv[1]))
        return EXIT_FAILURE;

	return EXIT_SUCCESS;
}