// lossless compression.cpp
#include "bits/stdc++.h"
using namespace std;
using namespace std::chrono;



string sx = "abcdefghijklmnopqrstuvwxyz0123456789";



vector<int> run_length_encoding_compressor(string &s) {
	auto start = high_resolution_clock::now();

	vector<int> v;
	int n = s.size();
	for (int i = 0; i < n; i++) {
		int j = i + 1;
		while (j < n and s[j] == s[i]) {
			j++;
		}
		v.push_back(j - i); v.push_back(s[i]);
		i = j - 1;
	}

	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	cout << "Compression time: " << duration.count() << " ms" << endl;
	double speed = int(s.size());
	speed /= duration.count(); speed *= 1e6;
	speed /= 1024 * 1024;
	cout << "Compression Speed: " << setprecision(6) << speed << " MB/s" << endl;
	cout << '\n';

	return v;
}
string run_length_encoding_decompress(vector<int> &data) {

	assert(data.size() % 2 == 0); // s must be of format (len, char)

	auto start = high_resolution_clock::now();

	int n = data.size();
	string final;
	for (int i = 0; i < n; i += 2) {
		string str(data[i], char(data[i + 1]));
		final.insert(final.end(), str.begin(), str.end());
	}

	auto stop = high_resolution_clock::now();


	auto duration = duration_cast<microseconds>(stop - start);
	cout << "De-compression time: " << duration.count() << " ms" << endl;
	double speed = int(data.size()) * 32;
	speed /= duration.count(); speed *= 1e6;
	speed /= 1024 * 1024;
	cout << "De-compression Speed: " << setprecision(6) << speed << " MB/s" << endl;
	cout << '\n';

	return final;
}


vector<int> dictionary_coder_compress_lzw(string &s) {
	auto start = high_resolution_clock::now();

	unordered_map<string, int> dict; //using 1 indexing while initializing sx elements

	int counter = 0;

	for (int i = 0; i < int(sx.size()); i++) { // initilizing dictionary
		string t; t += sx[i];
		dict[t] = (counter++);
	}
	vector<int> vc;
	string w;

	for (char k : s) {
		int w_id = dict[w];
		w += k;
		if (dict.find(w) != dict.end()) {
			//element found in dict
		} else {
			vc.push_back(w_id);
			dict[w] = (counter++);
			w = k;
		}
	}
	vc.push_back(dict[w]);

	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	cout << "Compression time: " << duration.count() << " ms" << endl;
	double speed = int(s.size());
	speed /= duration.count(); speed *= 1e6;
	speed /= 1024 * 1024;
	cout << "Compression Speed: " << setprecision(6) << speed << " MB/s" << endl;

	cout << "Compression Memory usage: " << double(dict.size() * 64) / 1024.0 << " KB" << endl;
	cout << '\n';
	return vc;
}


string dictionary_coder_decompress(vector<int> &data) {
	auto start = high_resolution_clock::now();

	int n = int(data.size());

	unordered_map<int, string> dict;
	int counter = 0;
	for (auto x : sx)
	{	//	string t; t += x;
		dict[counter++] = string(1, x);
	} // dictionary initialized
	string w;
	string final;
	for (int i = 0; i < n; i++) {
		string str = dict[data[i]];
		final.insert(final.end(), str.begin(), str.end());
		// dbg(final);
		if (i + 1 < n) {
			char ch;
			if (dict[data[i + 1]].size() == 0)
				ch = str[0];
			else
				ch = dict[data[i + 1]][0];

			// assert(dict[data[i + 1]].size() > 0);
			str += ch;
			dict[counter++] = str;
		}
	}

	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	cout << "De-compression time: " << duration.count() << " ms" << endl;
	cout << "De-compression Memory usage: " << dict.size() << endl;
	double speed = int(data.size()) * 32;
	speed /= duration.count(); speed *= 1e6;
	speed /= 1024 * 1024;
	cout << "De-compression Speed: " << setprecision(6) << speed << " MB/s" << endl;
	cout << "De-compression Memory usage: " << double(dict.size() * 64) / 1024.0 << " KB" << endl;

	cout << '\n';


	// cout << "Length of Dictionary while de-compressing: " << dict.size() << endl;

	return final;

}


int32_t main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	freopen("./data/data_random.txt", "r", stdin);

	string data; cin >> data;

	//data is ready to be used;
	cout << "--Compression using Run length encoding algorithm--\n\n";
	auto compressed = run_length_encoding_compressor(data);
	auto decomp = run_length_encoding_decompress(compressed);
	cout << "\n";

	cout << "Input data size: " << (data.size()) << " bytes\n";
	cout << "Compressed Data size: " << compressed.size() << " bytes\n";
	cout << "\n\n";
	// for (auto x : compressed) cout << x << " ";
	// cout << endl;
	// cout << decomp << endl;
	double compression_ratio = data.size();
	compression_ratio /= compressed.size();
	cout << "Compression Ratio: " << setprecision(6) << compression_ratio << endl;

	cout << "Was the compression lossless? ";
	cout << (data == decomp ? "True" : "False") << endl;


	cout << "\n\n--Compression using Dictionary Coder LZW algorithm--\n\n";
	compressed = dictionary_coder_compress_lzw(data);
	decomp = dictionary_coder_decompress(compressed);
	cout << '\n';
	cout << "Input data size: " << (data.size()) << " bytes\n";
	cout << "Compressed Data size: " << compressed.size() << " bytes\n";
	cout << "\n\n";
	// cout << decomp << endl;
	compression_ratio = data.size();
	compression_ratio /= compressed.size();
	cout << "Compression Ratio: " << setprecision(6) << compression_ratio << endl;

	cout << "Was the compression lossless? ";
	cout << (data == decomp ? "True" : "False") << endl;




	return 0;
}