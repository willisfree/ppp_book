/*
	Chapter 19, try this 

	28.08.2018 15:55
*/

#include "std_lib_facilities.h"

template<typename T, typename A = allocator<T>> class my_vector {
	A alloc;
	int sz;
	T* elem;
	int space;
public:
	my_vector() : sz{0}, elem{nullptr}, space{0} {}
	explicit my_vector(int s) : sz{s}, elem{new T[s]}, space{s}
	{
		for (int i=0; i<sz; ++i)
			elem[i] = 0;
	}

	void reserve(int newalloc);

	int capacity() const { return space; }
	int size() const { return sz; }
};

template<typename T, typename A>
void my_vector<T,A>::reserve(int newalloc)
{
	if (newalloc <= space) return;
	unique_ptr<T*> p {alloc.allocate(newalloc)};
	for (int i=0; i<sz; ++i) alloc.construct(&p[i], elem[i]);
	for (int i=0; i<sz; ++i) alloc.destroy(&elem[i]);
	alloc.deallocate(elem, space);
	elem = p.release();
	space = newalloc;
}

int main()
try
{
	my_vector<int> mv(20);
	cout << mv.capacity() << '\n'
		<< mv.size() << '\n';
}
catch (exception& e) {
	cerr << "exception: " << e.what() << '\n';
}
catch (...) {
	cerr << "exception\n";
}
