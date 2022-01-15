/*
	Chapter 21, ex7 improvements

	29.11.2018 19:24 - 30.11.2018 17:07
*/

#include "std_lib_facilities.h"

namespace Alg {	
	template<typename Ran, typename T>	//requires Random_access_iterator<Ran>()
		bool binary_search(Ran first, Ran last, const T& val)
		{
			while(first!=last) {
				Ran middle = first+(last-first)/2;
				if (*middle==val) return true;
				if (*middle<val) first = ++middle;
				else last = middle;
			}
			return false;
		}

	template<typename T>
	using lIt = typename list<T>::iterator;	//list iterator

	template<typename T>			//requires Forward_iterator<lIT>()
	bool binary_search_in_list(lIt<T> first, lIt<T> last, const T& val)
	{
		while(first!=last) {
			auto middle = next(first, distance(first, last)/2);	//expensive way
			if (*middle==val) return true;
			if (*middle<val) first = ++middle;
			else last=middle;
		}
		return false;
	}

/*
 * binary_search_in_list() with optimization.
 *
 * About middle.
 * If between (first, last] is only one element then middle is this last element, so don't move forward.
 * If between (first, last] are two elements then middle is any of the elements, so don't move forward too.
 *
 */
	template<typename T>			//requires Forward_iterator<lIT>()
	bool binary_search_in_list_opt(lIt<T> first, lIt<T> last, const T& val)
	{
		int n = distance(first, last);	//number of values
		int not_move = 0;
		while(first!=last) {
			auto middle = next(first, ((n>2)?(n/=2):not_move));
			if (*middle==val) return true;
			if (*middle<val) first = ++middle;
			else last=middle;
		}
		return false;
	}
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
		cout << Alg::binary_search_in_list_opt(l.begin(), l.end(), n) << '\n';
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
