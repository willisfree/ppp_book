/*
	Chapter 21, try this 2

	09.11.2018 19:03
*/

#include "std_lib_facilities.h"

struct Record {
	double unit_price;
	int units;
};

double price(double v, const Record& r)
{
	return v + r.units * r.unit_price;
}

int main()
try
{
	vector<Record> v = {{4.5, 3} , {5.7,5}, {1.1, 2}};
	double total = accumulate(v.begin(), v.end(), 0.0, price);
	cout << total << '\n';
}
catch (exception& e) {
	cerr << "exception: " << e.what() << '\n';
}
catch (...) {
	cerr << "exception\n";
}
