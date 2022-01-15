/*
	Chapter 19, exercise 10

	11.09.2018 21:37
*/

#include "std_lib_facilities.h"

namespace Lib {
	template<typename T> class unique_ptr {		//note: doesn't work with arrays
							//note: doesn't handle nullptr in operators
	public:
		explicit unique_ptr(T* ptr = nullptr) : p{ptr} { }
		~unique_ptr() { delete p; }

		T operator*() const { return *p; }
		T* operator->() const { return p; }
		T* release()
		{
			T* ptr = p;
			p = nullptr;
			return ptr;
		}
		const T* get() const { return p; }
	private:
		T* p;
	};
};

struct test {
	int a = 5;
	
	test() {cout << "test()\n";}
	test(const test& t) { cout << " (copy ctor of class test calls here) "; }
	~test() { cout << "~test()\n";}

	void print() const { cout << "a = " << a << '\n'; }
};

int main()
try
{
	Lib::unique_ptr<test> p {new test};
	cout << "p = " << p.get() << '\n';
	cout << "p->a = " << p->a << '\n';
	cout << "p->print(): ";
	p->print();
	cout << "*p = " << (*p).a << '\n';	//creat temp test object, that's why here call dtor
	cout << "*p.print(): ";
	(*p).print();				//creat temp test object, that's why here call dtor
	test* ptr = p.release();
	cout << "test* ptr = p.release()\n";
	cout << "p = " << p.get() << '\n';
	cout << "ptr->a = " << ptr->a << '\n';
	cout << "ptr->print(): ";
	ptr->print();
	delete ptr;
	//unique_ptr<test[]> l {new test[23]};
}
catch (exception& e) {
	cerr << "exception: " << e.what() << '\n';
}
catch (...) {
	cerr << "exception\n";
}
