/*
	Chapter 20, try this

	20.09.2018 14:40
*/

#include "std_lib_facilities.h"

void j_copy(int* f1, int* e1, int* f2)	//just copy
//copy all elements from [f1, e1) to f2
{
	if (f1 == nullptr || e1 == nullptr || f2 == nullptr) error("j_copy() get a nullptr as an argument.");
	for (int* p = f1; p != e1; ++p) {
		*f2 = *p;
		++f2;
	}
}

int main()
try
{
	int num = 5;
	int* arr = new int[num] {5, 21, 5, 2, 7};	
	int a[num];
	j_copy(arr, arr+num, a);
	for (int i=0; i<num; ++i)
		cout << a[i] << '\n';

	vector<int> vi(num);
	j_copy(arr, arr+num, &vi[0]);
	for (int i : vi) cout << i << '\n';
}
catch (exception& e) {
	cerr << "exception: " << e.what() << '\n';
}
catch (...) {
	cerr << "exception\n";
}
