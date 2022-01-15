/*
	Chapter 20, ex14

	27.10.2018 17:40 - 30.10.2018 15:07
*/


#include "slist_headers.h"
#include "std_lib_facilities.h"

template<typename Iter>
Iter high(Iter first, Iter last)
{
	Iter high = first;
	for (auto p = first; p!=last; ++p)
		if (*p>*high) high = p;
	return high;
}

void test1()
{
	slist<int> l;
	//cout << "l.size() = " << distance(l.begin(), l.end()) << '\n';
	auto p = l.begin();
	if (p == l.end()) cout << "l.begin() == l.end()\n";
	cout << "original list l: ";
	for (auto v : l) cout << v << ' ';
	cout << '\n';
	l.push_front(4);
	l.push_front(5);
	l.push_front(6);
	l.push_front(7);
	//cout << "l.size() = " << distance(l.begin(), l.end()) << '\n';
	cout << "l.front(): " << l.front() << '\n';
	cout << "list l after push_front(): ";
	for (auto v : l) cout << v << ' ';
	cout << '\n';
	l.pop_front();
	l.pop_front();
	l.pop_front();
	//cout << "l.size() = " << distance(l.begin(), l.end()) << '\n';
	cout << "l.front(): " << l.front() << '\n';
	cout << "list l after pop_front(): ";
	for (auto v : l) cout << v << ' ';
	cout << '\n';
}

void test2()
{
	slist<double> ld = {4.2, 6.2, 7.1, 3.2};
	//cout << "ld.size() = " << distance(ld.begin(), ld.end()) << '\n';
	cout << "first = " << *ld.begin() << '\n';
	cout << "original list:\t";
	for (auto p : ld) cout << setw(3) << p << ' ';
	cout << '\n';
	ld.insert_after(ld.begin(), 444);
	ld.insert_after(++ld.begin(), 333);
	ld.insert_after(++ld.begin(), 111);
	cout << "first = " << ld.front() << '\n';
	//cout << "ld.size() = " << distance(ld.begin(), ld.end()) << '\n';
	cout << "after insert:\t";
	for (auto p : ld) cout << setw(3) << p << ' ';
	cout << '\n';
	ld.erase_after(++++ld.begin());
	ld.erase_after(ld.begin());
	ld.erase_after(ld.begin());
	cout << "first = " << ld.front() << '\n';
	//cout << "ld.size() = " << distance(ld.begin(), ld.end()) << '\n';
	cout << "after erase:\t";
	for (auto p : ld) cout << setw(3) << p << ' ';
	cout << '\n';
}

void test3()
{
	slist<int> l;
	int i=0;
	cout << "enter some values: ";
	while (cin>>i) l.push_front(i);
	cout << "your input was: ";
	for (auto e : l) cout << e << ' ';
	cout << '\n';
	auto p = high(l.begin(), l.end());
	if (p!=l.end()) cout << "the highest value was " << *p << '\n';
}

int main()
try
{
	test1();
	test2();
	test3();
}
catch (exception& e) {
	cerr << "exception: " << e.what() << '\n';
}
catch (...) {
	cerr << "exception\n";
}
