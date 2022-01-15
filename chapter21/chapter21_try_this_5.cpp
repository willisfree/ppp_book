/*
	Chapter 21, try this 5

	14.11.2018 16:19 - 17:30
*/

#include "std_lib_facilities.h"

int main()
try
{
	string from = "chapter21_try_this_5/Input.txt", to = "chapter21_try_this_5/Output.txt";
	cout << "Enter input file: ";
	cin >> from;
	cout << "Enter output file: ";
	cin >> to;

	ifstream is{from};
	if (!is) error("can't open ", from);
	ofstream os{to};
	if (!os) error("can't open ", to);

	istream_iterator<string> ii{is};
	istream_iterator<string> eos;
	ostream_iterator<string> oo{os, "\n"};	//add '\'n

	int max_size = 10;
	vector<string> b(max_size);
	copy(ii, eos, b.begin());

//	vector<string> b{ii, eos};
	sort(b.begin(), b.end());
	copy(b.begin(), b.end(), oo);

}
catch (exception& e) {
	cerr << "exception: " << e.what() << '\n';
}
catch (...) {
	cerr << "exception\n";
}
