/*
	Chapter 20, ex15

	31.20.2018 16:58 - 1.11.2018 19:13
*/

#include "std_lib_facilities.h"

//class pvector is vector of pointers
template<typename T>
class pvector {
public:
	pvector();
	pvector(size_t n);
	pvector(initializer_list<T*> lst);
	~pvector();
	
	T* operator[](size_t n);

	T** begin();
	T** end();

	size_t size() const;

private:
	size_t sz;
	T** elem;
};

template<typename T>
pvector<T>::pvector() : sz{0}, elem{nullptr} { }

template<typename T>
pvector<T>::pvector(size_t n) : sz{n}, elem{new T*[sz]}
{
	for (int i=0; i<sz; ++i)
		elem[i]=nullptr;
}

template<typename T>
pvector<T>::pvector(initializer_list<T*> lst)
	:sz{lst.size()}, elem{new T*[sz]}
{
	copy(lst.begin(), lst.end(), elem);
}

template<typename T>
pvector<T>::~pvector()
{
	//deleting all objects by their pointers
	for (int i=0; i<sz; ++i)
		delete elem[i];
	//free up memory
	delete[] elem;
}

template<typename T>
T* pvector<T>::operator[](size_t n)
{
	return elem[n];
}

template<typename T>
T** pvector<T>::begin()
{
	return elem;
}

template<typename T>
T** pvector<T>::end()
{
	return elem+sz;
}

template<typename T>
size_t pvector<T>::size() const
{
	return sz;
}

struct test {
	test() { cout << "ctor\n"; }
	~test() { cout << "dtor\n"; }
};

int main()
try
{
	pvector<int> pv {new int{1}, new int{2}, new int{3}, new int{4}};
	for (auto p : pv) cout << *p << '\n';
	
	pvector<test> pl {new test, new test, new test, new test};
	
	for (int i=0; i<pv.size(); ++i)
		cout << *pv[i] << '\n';
}
catch (exception& e) {
	cerr << "exception: " << e.what() << '\n';
}
catch (...) {
	cerr << "exception\n";
}
