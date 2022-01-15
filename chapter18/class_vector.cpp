//Chapter 18, try_this
//class vector
//05.07.2018 18:27

#include <iostream>
//#include <algorithm>
//#include <iterator>
//#include <cmath>
//#include <string>
//#include <cstdlib>
//#include <array>

class vector {
	int sz;
	double* elem;
public:
	explicit vector(int s)
		: sz{s}, elem{new double[sz]}
	{
		for (int i = 0; i < sz; ++i)
			elem[i] = 0.0;
	}
	vector(const vector&);

	double operator[](int n) { return elem[n]; }
};

vector::vector(const vector& arg)
	: sz{arg.sz}, elem{new double[arg.sz]}
{
	std::copy(arg.elem, arg.elem+sz, elem);
}

int main()
{
	vector v(10);
	int x = v[2];
	v[3] = x;
}
