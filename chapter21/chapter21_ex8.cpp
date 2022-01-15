/*
	Chapter 21, ex8

	05.12.2018 16:05 - 21:06
*/

#include "std_lib_facilities.h"
#include <set>

int main()
try
{
	string fname = "The C++ Programming Language.txt";
	ifstream ifs{fname};
	if (!ifs) error("can't open ", fname);

	map<string, int> words;
	for (string s; ifs>>s; )
		++words[s];

	vector<pair<string, int>> v {words.begin(), words.end()};
	sort(v, [](const pair<string, int>& p1, const pair<string, int>& p2) { return p1.second<p2.second; });

	for (const auto& p : v)
		cout << p.second << ": " << p.first << '\n';
}
catch (exception& e) {
	cerr << "exception: " << e.what() << '\n';
}
catch (...) {
	cerr << "exception\n";
}
