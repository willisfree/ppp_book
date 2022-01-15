/*
	Chapter 19, exercise 6, 7

	02.09.2018 21:11
*/

#include "std_lib_facilities.h"

template<typename T, typename U>
typename common_type<T, U>::type sum_of_prod(const vector<T>& a, const vector<U>& b)
{
	typename common_type<T, U>::type sum = 0;
	for (int i=0; i<a.size(); ++i) {
		if (i == b.size()) break;
		sum += a[i]*b[i];
	}
	
	if (sum < 0)
		error("sum variable overflow in"
			" template<typename T, typename U> int sum_of_prod(const vector<T>& a, const vector<U>& b");
	return sum;
}

template<typename T> struct Number {
	T v;

//	Number() : v{T()} {}
	Number<T>(T vv = T()) : v{vv} {}
	Number<T>(const Number<T>& i) : v{i.v} {}
	
	Number<T>& operator=(const Number<T>& i);
	Number<T> operator+(const Number<T>& i);
	Number<T> operator-(const Number<T>& i);
	Number<T> operator*(const Number<T>& i);
	Number<T> operator/(const Number<T>& i);
	Number<T> operator%(const Number<T>& i);
	Number<T> operator+=(const Number<T>& i);
	operator T() const { return v; }
};

template<typename T> Number<T>& Number<T>::operator=(const Number<T>& i)
{
	v = i.v;
	return *this;
}

template<typename T>  Number<T> Number<T>::operator+(const Number<T>& i)
{
	return v+i.v;
}

template<typename T> Number<T> Number<T>::operator+=(const Number<T>& i)
{
	return v+=i.v;
}

template<typename T> Number<T> Number<T>::operator-(const Number<T>& i)
{
	return v-i.v;
}

template<typename T> Number<T> Number<T>::operator*(const Number<T>& i)
{
	return v*i.v;
}

template<typename T> Number<T> Number<T>::operator/(const Number<T>& i)
{
	return v/i.v;
}

template<typename T> Number<T> Number<T>::operator%(const Number<T>& i)
{
	return v%i.v;
}

template<typename T> istream& operator>>(istream& is, Number<T>& i)
{
	return is >> i.v;
}

template<typename T> ostream& operator<<(ostream& os, const Number<T>& i)
{
	return os << i.v;
}

int main()
try
{
	Number<int> i = 4;
	cout << "i = " << i << '\n'
	       << "i*i = " <<  i*i << '\n';
	Number<int> f;
	cout << "set f: ";
	cin >> f;
	Number<int> div = f/i;
	cout << f << " / " << i << " = " <<  div << '\n';
	cout << f << " % " << i << " = " <<  f%i << '\n';
	cout << div << " + " << div << " - " << f << " = " << div+div-f << '\n';

	Number<double> d = 4.563;
	cout << "d = " << d << '\n'
	       << "d*d = " <<  d*d << '\n';
	Number<double> fd;
	cout << "set fd: ";
	cin >> fd;
	Number<double> ddv = fd/d;
	cout << fd << " / " << d << " = " <<  ddv << '\n';
//	cout << fd << " % " << d << " = " <<  fd%d << '\n';
	cout << ddv << " + " << ddv << " - " << fd << " = " << ddv+ddv-fd << '\n';

	Number<string> s = string{"future"};
	cout << "s = " << s << '\n'
	       << "s+s = " <<  s+s << '\n';
	Number<string> fs;
	cout << "set fs: ";
	cin >> fs;
	Number<string> ss = fs+s;
	cout << fs << " + " << s << " = " <<  ss << '\n';

	Number<char> ch{4};
	Number<char> ch1{'a'};
	Number<char> ch2 = ch+ch1;
	cout << ch << " + " << ch1 << " = " << ch2 << '\n';

	vector<Number<int>> vi = {4, 2, 1, 6, 123, 4345, 1234, 54, 123};
	vector<Number<double>> vd = {5.4, 24.12, 3.32, 23.5, 2.5, 4.4};
	
	double sum = sum_of_prod(vi, vi);
	cout << "sum of int = " << sum << '\n';
	sum = sum_of_prod(vd, vd);
	cout << "sum of double = " << sum << '\n';
	sum = sum_of_prod(vi, vd);
	cout << "sum of double and int = " << sum << '\n';
}
catch (exception& e) {
	cerr << "exception: " << e.what() << '\n';
}
catch (...) {
	cerr << "exception\n";
}
