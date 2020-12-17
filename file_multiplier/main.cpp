#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
	std::ifstream in;
	std::ofstream out;
	int n;

	if (argc == 3) {
		n = stoi(argv[2]);
		in.open(argv[1]);
		if (in.is_open()) {
			string out_filename = argv[2];
			out_filename += "_mul_";
			out_filename += argv[1];

			out.open(out_filename);
		}
		else {
			return -1;
		}
	}
	else {
		return -1;
	}

	string s;
	while (getline(in, s)) {
		for (int i = 0; i < n; i++) {
			out << s << endl;
		}
	}

	in.close();
	out.close();
}