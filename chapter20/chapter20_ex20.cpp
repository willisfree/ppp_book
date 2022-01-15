/*
	Chapter 20, ex20

	06.11.2018 14:42 - 17:00
*/

#include "std_lib_facilities.h"
#include <chrono>

template<typename Container>
void sorted_insert_test(Container& cont, int n, const string& msg)
{
	using chrono::system_clock;

	auto t1 = system_clock::now();
	int num = 0;	
	for (int i=0; i<n; ++i) {	
		num = rand()%n;
		auto p = cont.begin();
		while (p!=cont.end() && *p<=num) ++p;
		cont.insert(p, num);
	}
	//for (auto v : cont) cout << v << ' ';		//debug; can slow down execution of program 
	auto t2 = system_clock::now();
	cout << "sorted insert of " << n << " values for " << msg << " took "
		<< chrono::duration_cast<chrono::milliseconds>(t2-t1).count() << " milliseconds\n";

}

int main()
try
{
	srand(time(0));
	int N = 10;
	cout << "Enter number of numbers, that will be generated: ";
	while (cin >> N) {
		vector<int> v;
		list<int> l;
		sorted_insert_test(v, N, "vector<int>");
		sorted_insert_test(l, N, "list<int>");
		cout << "\nEnter number of numbers, that will be generated: ";
	}
}
catch (exception& e) {
	cerr << "exception: " << e.what() << '\n';
}
catch (...) {
	cerr << "exception\n";
}
