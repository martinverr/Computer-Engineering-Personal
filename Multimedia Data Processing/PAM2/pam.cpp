#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cassert>
#include <cstdint>
#include <array>
#include <assert.h>
#include <algorithm>
#include <unordered_map>
#include <numeric>
#include <iterator>



template<typename T>
std::istream& raw_read(std::istream& is, T& num, size_t size = sizeof(T))
{
	return is.read(reinterpret_cast<char*>(&num), size);
}
template<typename T>
std::ostream& raw_write(std::ostream& os, const T& num, size_t size = sizeof(T))
{
	return os.write(reinterpret_cast<const char*>(&num), size);
}


class bitwriter {
	std::ostream& os_;
	uint8_t buffer_;
	size_t nbits_;

	std::ostream& write_bit(uint32_t u) {
		// buffer_ = buffer_ * 2 + u % 2;
		buffer_ = (buffer_ << 1) | (u & 1);
		++nbits_;
		if (nbits_ == 8) {
			raw_write(os_, buffer_);
			nbits_ = 0;
		}
		return os_;
	}

public:
	bitwriter(std::ostream& os) : os_(os), nbits_(0) {}

	~bitwriter() {
		flush();
	}

	std::ostream& write(uint32_t u, size_t n) {
		while (n-- > 0) {
			write_bit(u >> n);
		}
		return os_;
	}

	std::ostream& operator()(uint32_t u, size_t n) {
		return write(u, n);
	}

	void flush(uint32_t u = 0) {
		while (nbits_ > 0) {
			write_bit(u);
		}
	}
};

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

template<typename T>
void flip_inplace(mat<T> &img)
{
	using std::swap;
	auto rows = img.rows();
	for (int r = 0; r < rows / 2; ++r) {
		for (int c = 0; c < img.cols(); ++c) {
			swap(img(r, c), img(rows - 1 - r, c));
		}
	}
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


using namespace std;


struct frequency_counter {
	std::array<size_t, 256> occurrencies;

	frequency_counter() : occurrencies{ 0 } {}

	void operator()(uint8_t val) {
		++occurrencies[val];
	}

	const size_t& operator[](size_t pos) const {
		return occurrencies[pos];
	}
	size_t& operator[](size_t pos) {
		return occurrencies[pos];
	}

	double entropy() {
		double tot = 0.0;
		for (const auto& x : occurrencies) {
			tot += x;
		}

		double H = 0.0;
		for (const auto& x : occurrencies) {
			if (x > 0) {
				double px = x / tot;
				H += px * log2(px);
			}
		}

		return -H;
	}
};


bool compression(string ifilename, string ofilename){
	cout << "Loading " << ifilename << "...\n";
	mat<uint8_t> img;
	
	if (!load_pam(img, ifilename)) {
		cout << "Error loading input file " << ifilename;
		return false;
	}
	std::cout << " done.\n";

	ofstream os(ofilename, ios::binary);
	if(!os){
		cout << "Error opening output filename";
		return false;
	}

	os << "HUFFDIFF";
	auto rows = img.rows();
	auto cols = img.cols();

	os << static_cast<int32_t>(img.cols());
	os << static_cast<int32_t>(img.rows());

	mat<uint16_t> diff(rows, cols);
	frequency_counter freqs;

	for(size_t r = 0; r<rows; r++){
		for(size_t c = 0; c<cols; c++){
			if(r==0 && c == 0)
				diff(r,c) = img(r,c);
			else if(c==0)
				diff(r, c) = img(r,c) - img(r-1,c);
			else if(c!=0)
				diff(r, c) = img(r,c) - img(r,c-1);
			else
				assert(false);
			
			freqs(diff(r,c));
		}
	}

	if(false){ // set true to save the diff_matrix.pam
		mat<uint8_t> formatteddiff(rows, cols);
		for(size_t r = 0; r<rows; r++){
				for(size_t c = 0; c<cols; c++){
					formatteddiff(r,c) = diff(r,c) / 2 + 128;
				}
			}
		save_pam(formatteddiff, "diff_matrix.pam");	
	}

	cout << "diff matrix calculated with entropy" << freqs.entropy() << "\n";

	struct node {
		uint8_t sym_;
		size_t prob_;
		node* left_ = nullptr;
		node* right_ = nullptr;

		node(uint8_t sym, size_t prob) : 
			sym_(sym), prob_(prob) {}
		node(node* a, node *b) :
			prob_(a->prob_ + b->prob_),
			left_(a), right_(b) {}
	};

	std::vector<node*> vec;
	for (size_t i = 0; i < 256; ++i) {
		if (freqs[i] > 0) {
			node* n = new node(static_cast<uint8_t>(i), freqs[i]);
			vec.push_back(n);
		}
	}

	//una lamda function in C++: [](){}
	std::sort(begin(vec), end(vec), 
		[](const node* a, const node* b) {
			return a->prob_ > b->prob_;
		}
	);

	while (vec.size() > 1) {
		node* n1 = vec.back();
		vec.pop_back();
		node* n2 = vec.back();
		vec.pop_back();
		node* n = new node(n1, n2);
		auto it = vec.begin();
		for (; it != vec.end(); ++it) {
			node* x = *it;
			if (x->prob_ <= n->prob_) {
				break;
			}
		}
		vec.insert(it, n);

		node * root = vec.back();
	
		struct huffman {
			struct code {
				uint32_t len_, val_;
			};
			unordered_map<uint8_t, code> codes_table_;

			huffman(const node* root){
				compute_codes(root,0,0);
			}
			void compute_codes(const node* p, uint32_t len, uint32_t val){
				if(p->left_ == nullptr){
					codes_table_[p->sym_] = {len, val};
				}
				else {
					compute_codes(p->left_, len+1, val<<1);
					compute_codes(p->right_, len + 1, val << 1 | 1);
				}
			}
		};

		huffman h(root);
		os.put(static_cast<char>(h.codes_table_.size()));
		bitwriter bw(os);
		for (const auto& x : h.codes_table_) {
			bw(x.first, 8);
			bw(x.second.len_, 5);
			bw(x.second.val_, x.second.len_);
		}
		uint32_t num_symbols = accumulate(begin(f.occurrencies),
			end(f.occurrencies), 0);
		bw(num_symbols, 32);

		is.clear();
		is.seekg(0);

		while (true) {
			int c = is.get();
			if (c == EOF) {
				break;
			}
			auto hc = h.codes_table_[c];
			bw(hc.val_, hc.len_);
		}
	}
	return true;
}

bool decompression(){
	return true;
}

int main(int argc, char ** argv)
{
	if (argc != 4){
		cout << "Wrong syntax, should be: huffdiff [c|d] <input file> <output file>";
		return EXIT_FAILURE;
	}

	string choice = argv[1];
	
	if (choice == "c"){
		cout << "proceeding with compression";
		if (!compression(argv[2], argv[3]))
			return EXIT_FAILURE;
	}
	else if (choice == "d"){
		cout << "proceeding with decompression";
		if (!decompression())
			return EXIT_FAILURE;
	}
	else
		return EXIT_FAILURE;

	
	return EXIT_SUCCESS;
}