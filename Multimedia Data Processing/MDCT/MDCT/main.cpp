#include <fstream>
#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <map>

#define _USE_MATH_DEFINES
#include <cmath>

using namespace std;

template <typename T>
istream & raw_read(istream& is, T& val, size_t size = sizeof(T)) {
	return is.read(reinterpret_cast<char *> (&val), size);
}

template<typename T>
ostream& raw_write(ostream& os, const T& val, size_t size = sizeof(T)) {
	return os.write(reinterpret_cast<const char*>(&val), size);
}

template<typename T>
struct frequency_counter {
	vector<T> samples;
	map<T, size_t> occurrencies;

	frequency_counter() : samples{ 0 } {}

	frequency_counter(const vector<T> &v){
		samples = v;
	}

	void calc_occurrencies() {
		occurrencies.clear();
		for (const auto &x : samples) {
			++occurrencies[x];
		}
	}


	void save(string filename) {
		ofstream os(filename, ios::binary);
		//vector<int16_t> v = vector<int16_t>(samples.begin(), samples.end());
		for (auto& x : samples) {
			raw_write(os, x);
		}
	}

	bool quantize(const int &factor) {
		if (factor == 0)
			return false;
		for (auto &x : samples) {
			x /= factor;
		}
		return true;
	}

	bool dequantize(const int &factor) {
		for (size_t i = 0; i < samples.size(); i++) {
			samples[i] *= factor;
		}
		return true;
	}

	double entropy() {
		calc_occurrencies();
		double tot = 0.0;
		for (const auto& x : occurrencies) {
			tot += x.second;
		}

		double H = 0.0;
		for (const auto& x : occurrencies) {
			if (x.second > 0) {
				double px = x.second / tot;
				H += px * log2(px);
			}
		}

		return -H;
	}

	void diffs(vector<int16_t>& dst, const vector<int16_t>& src) {
		for (size_t i = 0; i < src.size(); i++) {
			dst[i] = samples[i] - src[i];
		}
	}
};


class Mdct {
private:
	frequency_counter<int16_t> audio_;
	frequency_counter<int32_t> audio_t;
	
	vector<int16_t> audio_extended;
	size_t N;
	vector<vector<double>> X;
	vector <double> coeffs;

public:
	Mdct(const vector<int16_t> & audio, size_t window_size) {
		this->audio_ = frequency_counter<int16_t>(audio);
		this->N = window_size;

		mdct_transform();
		
		
		for (auto& vec : X) {
			coeffs.insert(cend(coeffs), std::cbegin(vec), std::cend(vec));
		}
		frequency_counter<double>(coeffs).save("coeffs");

		vector<int32_t> coeffs_int32 = vector<int32_t>(coeffs.begin(), coeffs.end());
		
		audio_t = frequency_counter<int32_t>(coeffs_int32);
	}

	Mdct(frequency_counter<int16_t> & audiofr, size_t window_size) : Mdct(audiofr.samples, window_size) {}

	void _mdct_transform_single(const size_t& w) {
		const double PI = 3.141592653589793238463;
		size_t window_offset = 2 * w * N;

		for (size_t k = 0; k < N; k++) {
			for (size_t n = 0; n < 2 * N; n++) {
				X[w][k] += audio_extended[window_offset + n]
					* sin(PI / 2 / N * (n + 0.5))
					* cos(PI / N * (n + 0.5 + static_cast<double>(N) / 2) * (k + 0.5));
			}
		}
	}

	void mdct_transform() {
		size_t index = 0;
		size_t max_index = audio_.samples.size();
		size_t window_size;

		// padding left
		for (window_size = 0; window_size < N / 2; window_size++)
			audio_extended.push_back(0);


		while (index < max_index) {
			for (window_size = 0; window_size < N; window_size++)
			{
				if (index < max_index)
					audio_extended.push_back(audio_.samples[index++]);
				else //fill 0 last window
					audio_extended.push_back(0);
			}
			if (index < max_index)
				index -= N / 2;
		}
		// padding right
		for (window_size = 0; window_size < N / 2; window_size++)
			audio_extended.push_back(0);

		cout << "From " << audio_.samples.size() << " input samples\n";
		cout << " extended to " << audio_extended.size() << " samples\n";
		cout << "Windows input: " << audio_.samples.size() / N
			<< " to " << audio_extended.size() / N << "\n";
		cout << "\ncalculating coefficientes...\n";

		max_index = audio_.samples.size() / N;

		for (size_t window = 0; window < max_index; window++) {
			if (window % 100 == 0) {
				cout << (float)window / max_index * 100 << "%\twindow: " << window << "/" << max_index << ")\t";
				cout << "samples: [" << 2 * window * N << ", " << 2 * window * N + 2 * N << "]\n";
			}
			X.push_back(vector<double>(N));
			_mdct_transform_single(window);
		}
	}

	void _mdct_invtransform_single(const size_t& w) {
		const double PI = 3.141592653589793238463;
		size_t window_offset = w * N;

		for (size_t n = 0; n < 2 * N; n++) {
			for (size_t k = 0; k < N; k++) {
				audio_extended[window_offset + n] += coeffs[w*N]
					* cos(PI / N * (n + 0.5 + static_cast<double>(N) / 2) * (k + 0.5));
			}
			audio_extended[window_offset + n] *= 2.0 / N * sin(PI / 2 / N * (n + 0.5));
		}
	}

	void mdct_invtransform() {
			size_t max_index = X.size();

			for (size_t window = 0; window < max_index; window++) {
				if (window % 100 == 0) {
					cout << (float)window / max_index * 100 << "%\twindow: " << window << "/" << max_index << ")\t";
					cout << "samples: [" << window * N << ", " << window * (N + 1) << "]\n";
				}
				_mdct_invtransform_single(window);
			}
	}

	auto entropy() { return audio_t.entropy(); }
	auto quantize(const int& factor) { audio_t.quantize(factor); }
	auto dequantize(const int& factor) { audio_t.dequantize(factor); }
	auto save(const string& filename) { audio_t.save(filename); }
	
};



int main(int argc, char** argv) {

	cout << "opening test.raw...\n";
	ifstream is("test.raw", ios::binary);
	vector<int16_t> v;

	int16_t num;
	while (raw_read(is, num)) {
		v.push_back(num);
	}

	frequency_counter<int16_t> freqs(v);
	
	/*cout << "Entropy: " << freqs.entropy() << "\n";
	

	cout << "Quantizing for 2600...\n";
	freqs.quantize(2600);
	cout << "Entropy: " << freqs.entropy() << "\n";

	cout << "Dequantizing for 2600...\n";
	freqs.dequantize(2600);

	freqs.save("output_qt.raw");

	vector<int16_t> differencies(v.size());
	freqs.diffs(differencies, v);
	frequency_counter<int16_t> fdifferencies(differencies);
	fdifferencies.save("output_diffs.raw");*/

	cout << "MDCT...\n";
	Mdct mdct = Mdct(freqs, 1024);

	cout << "Quantizing coeffs for 10000...\n";
	mdct.quantize(10000);
	cout << "Entropy: " << mdct.entropy() << "\n";

	cout << "Saving output_coeffs...\n";
	mdct.save("coeffs_qt");
	
	cout << "Dequantizing coeffs for 10000...\n";
	mdct.dequantize(10000);
	cout << "Entropy: " << mdct.entropy() << "\n";

	return 0;
}