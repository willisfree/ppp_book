/*
	Chapter 20, ex 7
	
	12.10.2018 16:14
*/

#include "std_lib_facilities.h"

template<typename Iter>
Iter low(Iter first, Iter last)
{
	Iter low = first;
	for (Iter p = first; p!=last; ++p)
		if (*low < *p) low = p;		//first characters of alpabet have less number code, than following
	return low;
}

int main()
try
{
	srand(time(0));
	vector<string> v = {"hello", "home", "end", "cat", "dell", "William", "Andy"};
	random_shuffle(v.begin(), v.end());
	for (auto& s : v)
		cout << s << ' ';
	cout << '\n';

	auto h = low(v.begin(), v.end());
	if (h != v.end()) cout << "Last string in lexicographical order is: " << *h << '\n';
	else cout << "nothing was found\n";

}
catch (exception& e) {
	cerr << "exception: " << e.what() << '\n';
}
catch (...) {
	cerr << "exception\n";
}
