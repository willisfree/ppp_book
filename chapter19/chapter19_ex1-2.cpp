/*
	Chapter 19, exercise 1, 2

	30.08.2018 18:11
*/

#include "std_lib_facilities.h"

template<typename T, typename U> double sum_of_prod(const vector<T>& a, const vector<U>& b)
{
	if (!((is_same<T, double>::value || is_same<T, int>::value) && (is_same<U, double>::value || is_same<U, int>::value)))
		error("template<typename T, typename U> int sum_of_prod(const vector<T>& a, const vector<U>& b)"
				" function doesn't support this type");
	double sum = 0;
	for (int i=0; i<a.size(); ++i) {
		if (i == b.size()) break;
		sum += (a[i]*b[i]);
	}
	
	if (sum < 0)
		error("sum variable overflow in"
			" template<typename T, typename U> int sum_of_prod(const vector<T>& a, const vector<U>& b");
	return sum;
}

template<typename T> void f(vector<T>& a, const vector<T>& b)
{
	for (int i=0; i<a.size(); ++i) {
		if (i == b.size()) break;
		a[i]+=b[i];
	}
}

int main()
try
{
	vector<int> v1 = {5, 1, 1};
	vector<int> v2 = {54, 2, 21, 1, 2};
	vector<double> vd = {4.413, 12.141, 35.123, 74.1234, 2.6};
	vector<string> vs = {"sadf", "sdf"};
	vector<char> vc = {'s', 'h', ';', 'l'};
	vector<bool> vb = {1, 0, 1 , 1, 1, 0, 0};

	cout << "vector v1\n";	
	for (int a : v1)
		cout << a << '\n';

	
	cout << "sum_of_prod(v1, vd) = " << sum_of_prod(v1, vd) << '\n';
	cout << "sum_of_prod(v1, v2) = " << sum_of_prod(v1, v2) << '\n';	
	
	f(v1, v2);
	//sum_of_prod(v1, vs); 	//error as expected
	//f(v1, vs);		//error as expected

	cout << "sum_of_prod(v1, vc) = " << sum_of_prod(v1, vc) << '\n';
	cout << "sum_of_prod(v1, vb) = " << sum_of_prod(v1, vb) << '\n';

	cout << "vector v1\n";	
	for (int a : v1)
		cout << a << '\n';
}
catch (exception& e) {
	cerr << "exception: " << e.what() << '\n';
}
catch (...) {
	cerr << "exception\n";
}
