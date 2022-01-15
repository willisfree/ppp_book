/*
	Chapter 20, try this

	27.09.2018 21:07
*/

#include "std_lib_facilities.h"

//return 0 if [first, last) == [compFirst, compLast)
//1 if [first, last) >  [compFirst, compLast)
//-1 if [first, last) < [compFirst, compLast)
template<typename fIter, typename sIter>
int alph_order_comp(fIter first, fIter last, sIter compFirst, sIter compLast)
{
	int equal = 0;		//p equal to comparison sequence
	int before = -1;	//p before
	int after = 1;		//p after

	//compare by length
	sIter comp_p = compFirst;
	for (fIter p = first; p!=last; ++p) {
		if (comp_p == compLast) return after;	//comparison sequence has ended
		++comp_p;
	}
	if (comp_p != compLast) return before;	//comparison sequence hasn't ended

	//two sequences have equal length
	for (fIter p = first; p!=last; ++p) {
		if (*p > *compFirst) return after;
		else if (*p < *compFirst) return before;
		++compFirst;
	}
	return equal;
}

template<typename fIter, typename sIter>
bool compare(fIter first, fIter last, sIter compFirst, sIter compLast)
	//return true if [first, last) equal to [compFirst, compLast)
{
	for (fIter p = first; p!=last; ++p) {
		if (compFirst == compLast) return false;	//comparison sequence has ended (sequences have diff length)
		if (*p != *compFirst) return false;
		++compFirst;
	}
	if (compFirst != compLast) return false;	//comparison sequence hasn't ended (sequences have diff length)
	return true;
}

template<typename Iter>
void print(Iter first, Iter last)
{
	for (Iter p=first; p!=last; ++p)
		cout << *p;
}

template<typename Iter>
void f(Iter firstIter, Iter lastIter)
{
	if (firstIter == lastIter) return;

	

	int count = 0;
	for (Iter p = firstIter; p!=lastIter; ++p) {
		++count;
		cout << *p;
	}
	vector<int> h = {5,4,3,2,1};
	if (compare(firstIter,lastIter, h.begin(), h.end())) {
		cout << " equals to ";
		print(h.begin(), h.end());
	}
	else {
		cout << " doesn't equal to ";
		print(h.begin(), h.end());
	}
	string s = "Howdy";
	int res = alph_order_comp(firstIter,lastIter, s.begin(), s.end());
	if (res > 0)
		cout << ", and stay after " << s;
	else if (res < 0)
		cout << ", and stay before " << s;
	else
		cout << ", and equal to " << s;
	
	cout << "; size = " << count;

}

int main()
try
{
	int n = 5;
	int a[] = {5,4,3,2,1};
	vector<int> v = {5,4,3,2,1};
	list<int> l = {5,4,3,2,1};

	f(a, a+n);
	cout << endl;
	f(v.begin(), v.end());
	cout << endl;
	f(l.begin(), l.end());
	cout << endl;
}
catch (exception& e) {
	cerr << "exception: " << e.what() << '\n';
}
catch (...) {
	cerr << "exception\n";
}
