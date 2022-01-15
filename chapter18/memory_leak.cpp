#include "std_lib_facilities.h"
//wrong memory allocation and free
struct A {
	int a;

	A() : a{5}
	{ 
		cout << this << "-> A{}" << " a = " << a << '\n';
	}

	A& operator=(const A& arg)
	{
		a = arg.a;
 		cout << this << "-> operator=" << " a = " << a << '\n'; 
		return *this;
	}

	A(int aa)
		: a{aa}	{ }

	~A() { cout << this << "-> ~A{}" << " a = " << a << '\n'; }
};

int main()
{
	A* pta = new A;		//allocate memory for one object
	A* ppt = pta;
	for (int i = 0; i < 3; ++i) {
		*ppt++ = i;
	}
	delete[] pta;		//try delete all 3 objects

//	A* pa = new A[5];
//	delete pa;
}
