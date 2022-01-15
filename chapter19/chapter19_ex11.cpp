/*
	Chapter 19, exercise 10

	13.09.2018 0:14 - 13.09.2018 19:00
*/

#include "std_lib_facilities.h"

template<typename T> class counted_ptr {
public:
	explicit counted_ptr(const T& obj) : p{new T{obj}}, counter{new int{1}} { }
	
	counted_ptr(const counted_ptr<T>& cp) : p{cp.get()}, counter{cp.get_counter()}
	{
		++(*counter);
	}
	counted_ptr<T>& operator=(const counted_ptr<T>& arg)
	{
		if (this == &arg) return *this;
		if (*counter == 1) {
			delete p;
			delete counter;
		}
		p = arg.get();
		counter = arg.get_counter();
		return *this;
	}
	~counted_ptr()
	{	
	//	cout << "COUNTER: " << *counter << '\n';
		if (*counter == 1) {
			delete p;
			delete counter;
			cout << "~counted_ptr()\n";
			return;
		}
		--(*counter);
	}

	T operator*() { return *p; }
	const T operator*() const { return *p; }
	T* operator->() { return p; }
	const T* operator->() const { return p; }

	T* get() const { return p; }
	int* get_counter() const { return counter; }
	int use_count() const { return *counter; }

private:
	T* p;
	int* counter;
};

struct test {
	int a = 5;
	int r = rand() % 100;

	test(int i) : a{i} {cout << "test(" << i << ")\n";}
	test() {cout << "test()\n";}
	test(const test& t) { cout << " (copy ctor of class test calls here) "; }
	~test() { cout << "~test()\n";}

	void print() const { cout << "a = " << a << '\n'; }
};

ostream& operator<<(ostream& os, const test& t)
{
	os << "a = " << t.a << " r = " << t.r;
}

template<typename T> counted_ptr<T> test0(counted_ptr<T> arg)
{
	cout << "*********test0(arg)*********\n";
	cout << "USE_COUNT: " << arg.use_count() << '\n';
	counted_ptr<T>* p = new counted_ptr<T>{arg};
	cout << "USE_COUNT: " << arg.use_count() << '\n';
	cout << "********end_of_test0()******\n";
	counted_ptr<T> r = *p;
	delete p;
	return r;
}

template<typename T> void test1(counted_ptr<T> arg)
{
	cout << "*********test1(arg)*********\n";
	cout << "USE_COUNT: " << arg.use_count() << '\n';
	arg = test0(arg);
	cout << "USE_COUNT: " << arg.use_count() << '\n';
	cout << *arg;
	cout << "******end_of_test1(arg)*******\n";
}

template<typename T> void test2(const vector<counted_ptr<T>>& arg)
{
	cout << "*********test2(arg)*********\n";
	for (const counted_ptr<T>& a : arg) {
		cout << *a << '\n';
		a->print();
	}
}

void base_operators()
{
	cout << "*********base_operators()*********\n";
	counted_ptr<test> p {test{}};
	cout << "p = " << p.get() << '\n';
	cout << "p->a = " << p->a << '\n';
	cout << "p->print(): ";
	p->print();
	cout << "*p = " << (*p).a << '\n';	//creat temp test object, that's why here call dtor
	cout << "*p.print(): ";
	(*p).print();				//creat temp test object, that's why here call dtor

}

void count_ptr_t()
{
	cout << "*********count_ptr_t()*********\n";
	counted_ptr<int> ci {34};
	cout << "ci.use_count() = " << ci.use_count() << '\n';
	cout << "*ci.get() = " << *ci.get() << '\n';

	counted_ptr<int> cc {ci};
	cout << "cc.use_count() = " << cc.use_count() << '\n';
	cout << "*cc.get() = " << *cc.get() << '\n';
	cout << "ci.use_count() = " << ci.use_count() << '\n';
	cout << "*ci.get() = " << *ci.get() << '\n';

	counted_ptr<int> cd {cc};
	ci = cc;	//shallow copy(in this case nothing was changed)
	cout << "cd.use_count() = " << cd.use_count() << '\n';
	cout << "*cd.get() = " << *cd.get() << '\n';
	cout << "ci.use_count() = " << ci.use_count() << '\n';
	cout << "*ci.get() = " << *ci.get() << '\n';
	cout << "cc.use_count() = " << cc.use_count() << '\n';
	cout << "*cc.get() = " << *cc.get() << '\n';
}

int main()
try
{
	srand(time(0));
	count_ptr_t();
	base_operators();
	cout << "********main********\n";
	counted_ptr<test> t{test{7}};
	cout << "USE_COUNT: " << t.use_count() << '\n';
	test1(t);

	vector<counted_ptr<test>> vp;
	for (int i=0; i<10; ++i) {
		vp.push_back(t);
		cout << "USE_COUNT: " << vp[i].use_count() << '\n';
	}
	test2(vp);
}
catch (exception& e) {
	cerr << "exception: " << e.what() << '\n';
}
catch (...) {
	cerr << "exception\n";
}
