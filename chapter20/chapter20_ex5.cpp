/*
	Chapter 20, ex5

	06.10.2018 22:30
*/

#include "std_lib_facilities.h"

template<typename T>
ostream& operator<<(ostream& os, const vector<T>& vec)
{
	for (auto e : vec)
		os << e << ' ';
	return os;
}

template<typename T>
istream& operator>>(istream& is, vector<T>& vec)
{
	T obj;
	while(is) {	
		is >> obj;
		if (!is) return is;
		vec.push_back(obj);
	}
	return is;
}

template<typename T>
void set(istream& is, vector<T>& vec, const string& msg)
{
	cout << msg;
	while (cin) cin >> vec;
	is.clear();
	is.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main()
try
{
	vector<int> vi = {1,2,3,4,5,6,7,8,9};	
	vector<string> vs = {"one", "two", "free", "four", "five"};
	vector<char> vc = {'a', 'b', 'c', 'd', 'e'};

	cout << vi << '\n' << vs << '\n' << vc << '\n';
	
	set(cin, vi, "set some ineteger numbers: ");
	set(cin, vs, "set some words: ");
	set(cin, vc, "set some characters: ");

	cout << vi << '\n' << vs << '\n' << vc << '\n';
}
catch (exception& e) {
	cerr << "exception: " << e.what() << '\n';
}
catch (...) {
	cerr << "exception\n";
}
