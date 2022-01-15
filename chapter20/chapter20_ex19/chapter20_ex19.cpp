/*
	Chapter 20, ex19

	04.11.2018 12:44 - 13:55
*/

#include "list.h"
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
	Lib::list<int> l;
	cout << "l.size() = " << l.size() << '\n';
	auto p = l.begin();
	if (p == l.end()) cout << "l.begin() == l.end()\n";
	cout << "original list l: ";
	for (auto v : l) cout << v << ' ';
	cout << '\n';
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	cout << "l.size() = " << l.size() << '\n';
	cout << "l.front(): " << l.front() << " l.back(): " << l.back() << '\n';
	cout << "list l after push_back(): ";
	for (auto v : l) cout << v << ' ';
	cout << '\n';
	l.push_front(4);
	l.push_front(5);
	l.push_front(6);
	l.push_front(7);
	cout << "l.size() = " << l.size() << '\n';
	cout << "l.front(): " << l.front() << " l.back(): " << l.back() << '\n';
	cout << "list l after push_front(): ";
	for (auto v : l) cout << v << ' ';
	cout << '\n';
	l.pop_back();
	l.pop_front();
	l.pop_back();
	l.pop_front();
	l.pop_front();
	cout << "l.size() = " << l.size() << '\n';
	cout << "l.front(): " << l.front() << " l.back(): " << l.back() << '\n';
	cout << "list l after pop_back() and pop_front(): ";
	for (auto v : l) cout << v << ' ';
	cout << '\n';

}

void test2()
{
	Lib::list<double> ld = {4.2, 6.2, 7.1, 3.2};
	cout << "ld.size() = " << ld.size() << '\n';
	cout << "first = " << *ld.begin() << " last = " << *--ld.end() << '\n';
	cout << "original list:\t";
	for (auto p : ld) cout << setw(3) << p << ' ';
	cout << '\n';
	ld.insert(ld.begin(), 444);
	ld.insert(ld.end(), 333);
	ld.insert(++ld.begin(), 111);
	cout << "first = " << *ld.begin() << " last = " << *--ld.end() << '\n';
	cout << "ld.size() = " << ld.size() << '\n';
	cout << "after insert:\t";
	for (auto p : ld) cout << setw(3) << p << ' ';
	cout << '\n';
	ld.erase(--ld.end());
	ld.erase(--ld.end());
	ld.erase(ld.begin());
	ld.erase(++ld.begin());
	cout << "first = " << *ld.begin() << " last = " << *--ld.end() << '\n';
	cout << "ld.size() = " << ld.size() << '\n';
	cout << "after erase:\t";
	for (auto p : ld) cout << setw(3) << p << ' ';
	cout << '\n';
}

void test3()
{
	Lib::list<int> l;
	int i=0;
	while (cin>>i) l.push_back(i);
	auto p = high(l.begin(), l.end());
	if (p!=l.end()) cout << "the highest value was " << *p << '\n';
}

void test4()
{
	Lib::list<char> l = {'g','v','s','u'};
	auto it = l.begin();
	cout << *it << '\n';
	//--it;	//throw error
	auto end = l.end();
	++end;	//throw error
}

int main()
try
{
	test1();
	test2();
	test3();
	test4();
}
catch (exception& e) {
	cerr << "exception: " << e.what() << '\n';
}
catch (...) {
	cerr << "exception\n";
}
