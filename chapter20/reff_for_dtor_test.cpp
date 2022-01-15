#include <iostream>

struct test {
	int n;
	test(int nn) : n{nn} { std::cout << "ctor()\n"; }
	~test() { std::cout << "dtor()\n"; }
};

int main()
{
	test* p = new test{5};
	test& tref = *p;
	std::cout << tref.n << '\n';
	//delete p;
}
