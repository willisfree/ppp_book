/*
	Chapter 19, exercise 5

	02.09.2018 18:40
*/

#include "std_lib_facilities.h"

struct Int {
	int v;

	Int() {}
	Int(int vv) : v{vv} {}
	Int(const Int& i) : v{i.v} {}
	Int& operator=(const Int& i);
	Int operator+(const Int& i);
	Int operator-(const Int& i);
	Int operator*(const Int& i);
	Int operator/(const Int& i);
};

Int& Int::operator=(const Int& i)
{
	v = i.v;
	return *this;
}

Int Int::operator+(const Int& i)
{
	return v+i.v;
}

Int Int::operator-(const Int& i)
{
	return v-i.v;
}

Int Int::operator*(const Int& i)
{
	return v*i.v;
}

Int Int::operator/(const Int& i)
{
	return v/i.v;
}

istream& operator>>(istream& is, Int& i)
{
	return is >> i.v;
}

ostream& operator<<(ostream& os, const Int& i)
{
	return os << i.v;
}

int main()
try
{
	Int i = 4;
	cout << "i = " << i << '\n'
	       << "i*i = " <<  i*i << '\n';
	Int f;
	cout << "set f: ";
	cin >> f;
	Int div = f/i;
	cout << f << " / " << i << " = " <<  div << '\n';
	cout << div << " + " << div << " - " << f << " = " << div+div-f << '\n';
}
catch (exception& e) {
	cerr << "exception: " << e.what() << '\n';
}
catch (...) {
	cerr << "exception\n";
}
