/*
	Chapter 19, try_this

	27.08.2018 14:55
*/

#include "std_lib_facilities.h"

void suspicious(vector<int>& v, int s)
{
	int* p = nullptr;
	try {
		p = new int[s];

	} catch (bad_alloc) {
		cerr << "bad_allocation for p pointer\n";
		throw;
	}

	vector<int> v1;
	
	int* q = nullptr;
	try {
		q = new int[s];

	} catch (bad_alloc) {
		cerr << "bad_allocation for q pointer\n";
		throw;
	}
	vector<double> v2;

	delete[] p;
	delete[] q;
}

int main()
try
{
	vector<int> v = {4, 5, 1, 7, 12};
	int i = 0;
	
	while (cin >> i || !cin) {
		while (!cin) {
			cout << "Set number without any words or characters: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin >> i;
		}
		suspicious(v, i);
	}
}
catch (exception& e) {
	cerr << "exception: " << e.what() << '\n';
}
catch (...) {
	cerr << "exception\n";
}
