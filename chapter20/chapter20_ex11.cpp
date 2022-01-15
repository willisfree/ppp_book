/*
	Chapter 20, ex11

	14.10.2018 14:23
*/

#include "std_lib_facilities.h"

template<typename F, typename L>
void list_to_vec(const list<F>& l, vector<L>& v)	//copy elements from list to vector
{
	auto v_begin = v.begin();
	auto v_end = v.end();
	for (auto p = l.begin(); p!=l.end(); ++p) {
		if (v_begin==v_end) return;
		*v_begin=*p;
		++v_begin;
	}
}

int main()
try
{
	int vec_size = 100;
	list<int> l = {5,4,3,2,1};
	vector<double> v(vec_size);
	list_to_vec(l, v);
	sort(v.begin(), v.end());
	for (auto d : v) cout << d << ' ';
	cout << '\n';
}
catch (exception& e) {
	cerr << "exception: " << e.what() << '\n';
}
catch (...) {
	cerr << "exception\n";
}
