/*
	Chapter 21, ex5

	23.11.2018 17:35 - 19:08
*/

#include "std_lib_facilities.h"

namespace Alg {
	//all algorithms get first and last iterators [first,last], where last is really last, not past-the-end
	
	template<typename In, typename T>	//requires Input_iterator<In>()
		int count(In first, In last, const T& val)
		{
			int count = 0;
			for ( ;first!=last; ++first)
				if (*first==val) ++count;
			
			if (*first==val) ++count;	//check last elem
			return count;
		}
	template<typename In, typename Pred>	//requires Input_iterator<In>() && Predicate<Pred, Value_type<In>>()
		int count_if(In first, In last, Pred pred)
		{
			int count = 0;
			for ( ;first!=last; ++first)
				if (pred(*first)) ++count;
			
			if (pred(*first)) ++count;	//check last elem
			return count;
		}
	template<typename In, typename T>	//requires Forward_iterator<In>()
	//return first iterator if nothing was found,
	//so you must handle return result by hands,
	//i.e if (return result)==first && *(return result)!=val then nothing was found
		In find(In first, In last, const T& val)
		{
			for (auto p = first; p!=last; ++p)
				if (*p==val) return p;	
			
			if (*last==val) return last;
			return first;
		}
}

int main()
try
{
	srand(time(NULL));
	int val = 0;
	vector<int> v(10);
	int n = Alg::count(v.begin(), v.end()-1, val);
	for (auto value : v) cout << value << ' ';
	cout << '\n';
	cout << "value " << val <<  " occurs in vector<int> " << n << " times\n";

	generate(v.begin(), v.end(), []() { return rand()%10; });
	n = Alg::count(v.begin(), v.end()-1, val);
	for (auto value : v) cout << value << ' ';
	cout << '\n';
	cout << "value " << val <<  " occurs in vector<int> " << n << " times\n";

	int max = 5;
	n = Alg::count_if(v.begin(), v.end()-1, [&](int n) { return n < max; });
	cout << "numbers < " << max <<  " occur in vector<int> " << n << " times\n";

	val = 7;
	if (v.begin()!=v.end()) {
		auto p = Alg::find(v.begin(), v.end()-1, val);
		if (p==v.begin() && *p!=val) cout << "nothing was found\n";
		else	cout << "value " << val << " was found\n";
	}

}
catch (exception& e) {
	cerr << "exception: " << e.what() << '\n';
}
catch (...) {
	cerr << "exception\n";
}
