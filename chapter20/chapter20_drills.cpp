/*
	Chapter 20, drils

	20.09.2018 14:17
*/

#include "std_lib_facilities.h"

template<typename Iter>
void increase(Iter first, Iter last, int n)
{
	for (Iter p = first; p!=last; ++p)
		*p+=n;
}

template<typename Iter1, typename Iter2>
Iter2 j_copy(Iter1 f1, Iter1 e1, Iter2 f2)
{
	for (Iter1 p = f1; p!=e1; ++p) {
		*f2 = *p;
		++f2;
	}
	return f2;
}

template<typename Iter>
int get_pos(Iter first, Iter last, Iter it)	//find number postition of 'it' in (first, last] sequence;
						//return negative number if not found
{
	int n = -1;
	for (Iter p = first; p!=last; ++p) {
		++n;
		if (p == it) return n;
	}
	return n;
}

template<typename Iter>
void print(Iter first, Iter last)
{
	for (auto p = first; p!=last; ++p)
		cout << setw(2) << *p << ' ';
}

int main()
try
{
	array<int, 10> a = {0,1,2,3,4,5,6,7,8,9};
	vector<int> v = {0,1,2,3,4,5,6,7,8,9};
	list<int> l = {0,1,2,3,4,5,6,7,8,9};
	
	array<int, 10> s_a = a;
	vector<int> s_v = v;
	list<int> s_l = l;

	print(s_a.begin(), s_a.end());
	cout << endl;
	print(s_v.begin(), s_v.end());
	cout << endl;
	print(s_l.begin(), s_l.end());

	increase(s_a.begin(), s_a.end(), 2);
	increase(s_v.begin(), s_v.end(), 3);
	increase(s_l.begin(), s_l.end(), 5);

	cout << endl << endl;
	print(s_a.begin(), s_a.end());
	cout << endl;
	print(s_v.begin(), s_v.end());
	cout << endl;
	print(s_l.begin(), s_l.end());

	j_copy(s_a.begin(), s_a.end(), s_v.begin());
	j_copy(s_l.begin(), s_l.end(), s_a.begin());

	cout << endl << endl;
	print(s_a.begin(), s_a.end());
	cout << endl;
	print(s_v.begin(), s_v.end());
	cout << endl;
	print(s_l.begin(), s_l.end());
	cout << endl;

	auto vi = find(s_v.begin(), s_v.end(), 3);	//vec::iter
	if (vi==s_v.end()) cout << "nothing found\n";
	else cout << "pos: " << vi-s_v.begin() << " val: " << *vi << '\n';

	auto lli = find(s_l.begin(), s_l.end(), 27);	//list::iter
	if (lli==s_l.end()) cout << "nothing found\n";
	else cout << "pos: " << get_pos(s_l.begin(), s_l.end(), lli) << " val: " << *lli << '\n';

	auto li = find(s_l.begin(), s_l.end(), 7);	//list::iter
	if (li==s_l.end()) cout << "nothing found\n";
	else cout << "pos: " << get_pos(s_l.begin(), s_l.end(), li) << " val: " << *li << '\n';
}
catch (exception& e) {
	cerr << "exception: " << e.what() << '\n';
}
catch (...) {
	cerr << "exception\n";
}
