/*
	Chapter 21,
	ex3
	22.11.2018 16:04 - 23:52
	ex4
	23.11.2018 16:42 - 17:04
*/

#include "std_lib_facilities.h"

namespace Alg {
	template<typename In, typename T>	//requires Input_iterator<In>()
		int count(In first, In last, const T& val)
		{
			int count = 0;
			for ( ;first!=last; ++first)
				if (*first==val) ++count;
			return count;
		}
	template<typename In, typename Pred>	//requires Input_iterator<In>() && Predicate<Pred, Value_type<In>>()
		int count_if(In first, In last, Pred pred)
		{
			int count = 0;
			for ( ;first!=last; ++first)
				if (pred(*first)) ++count;
			return count;
		}
}

int main()
try
{
	srand(time(NULL));
	int val = 0;
	vector<int> v(10);
	int n = Alg::count(v.begin(), v.end(), val);
	for (auto value : v) cout << value << ' ';
	cout << '\n';
	cout << "value " << val <<  " occurs in vector<int> " << n << " times\n";

	generate(v.begin(), v.end(), []() { return rand()%10; });
	n = Alg::count(v.begin(), v.end(), val);
	for (auto value : v) cout << value << ' ';
	cout << '\n';
	cout << "value " << val <<  " occurs in vector<int> " << n << " times\n";

	int max = 5;
	n = Alg::count_if(v.begin(), v.end(), [&](int n) { return n < max; });
	cout << "numbers < " << max <<  " occur in vector<int> " << n << " times\n";

}
catch (exception& e) {
	cerr << "exception: " << e.what() << '\n';
}
catch (...) {
	cerr << "exception\n";
}
