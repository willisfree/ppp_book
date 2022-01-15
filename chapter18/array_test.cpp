#include "std_lib_facilities.h"

struct A {
	int a;
	string s;

	A() : a{5}, s{"stone"}
	{ 
		cout << this << "-> A{}" << " a = " << a << " s = " << s << '\n';
	}
	~A() { cout << this << "-> ~A{}" << " a = " << a << " s = " << s << '\n'; }
};

int main()
{
	A la;
	A ta[10];
	A* pa = new A[2];
	delete[] pa;
}
