/*
	Chapter 21, ex7

	25.11.2018 14:59 21:00
*/

#include "std_lib_facilities.h"

namespace Alg {	
	template<typename Ran, typename T>	//requires Random_access_iterator<Ran>()
		bool binary_search(Ran first, Ran last, const T& val)
		{
			while(first!=last-1) {
				Ran middle = first+(last-first)/2;
				if (*middle==val) return true;
				if (*middle<val) first = middle;
				else last = middle;
			}
			if(*first==val) return true;	//process last element\
							//if it's only one in container
			return false;
		}

	template<typename T>
	using lIt = typename list<T>::iterator;	//list iterator

	//use s_first because val can be larger than last element in [first, last) list;
	//so without s_first we'll fall to endless loop
	template<typename T>			//requires Forward_iterator<lIT>()
	bool binary_search_in_list(lIt<T> first, lIt<T> last, const T& val)
	{
		auto s_first = first;		//successor of the first
		++s_first;			//useful if only one element between [first, last)
		while(s_first!=last) {
			auto middle = next(first, distance(first, last)/2);	//expensive way
			if (*middle==val) return true;
			if (*middle<val) {
				s_first = first = middle;
				++s_first;
			}
			else last=middle;
		}
		if (*first==val) return true;		//process last element
		return false;
	}
/*
// works, but hasn't been tested in all cases
	template<typename T>			//requires Forward_iterator<lIT>()
	bool binary_search_in_list(lIt<T> first, lIt<T> last, const T& val)
	{
		int n = distance(first, last);	//number of values
		auto s_first = first;		//successor of the first
		++s_first;			//useful if only one element between [first, last)
		while(s_first!=last) {
			auto middle = next(first, n/=2);
			if (*middle==val) return true;
			if (*middle<val) {
				s_first = first = middle;
				++s_first;
			}
			else last=middle;
			if (n==1) n=2;			//ugly way
		}
		if (*first==val) return true;		//process last element
		return false;
	}
*/
}

void test_vector()
{
	cout << "test_for_vector\n";
	vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	int n = 0;
	while(cin) {
		cout << "enter integer value: ";
		cin >> n;
		cout << Alg::binary_search(v.begin(), v.end(), n) << '\n';
	}
}

void test_list()
{
	cout << "test_for_list\n";
	list<int> l = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	int n = 0;
	while(cin) {
		cout << "enter integer value: ";
		cin >> n;
		cout << Alg::binary_search_in_list(l.begin(), l.end(), n) << '\n';
	}
}

void test_string_list()
{
	cout << "test_for_string\n";
	list<string> l = {"Orange", "Plum", "Apple", "Kiwi", "Grape", "Quince"};
	l.sort();
	string s;
	while (cin >> s) {
		cout << Alg::binary_search_in_list(l.begin(), l.end(), s) << '\n';
	}
}

int main()
try
{
	test_vector();
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	test_list();
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	test_string_list();
}
catch (exception& e) {
	cerr << "exception: " << e.what() << '\n';
}
catch (...) {
	cerr << "exception\n";
}
