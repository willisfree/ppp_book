/*
	Chapter 19, exercise 8, 9

	03.09.2018 17:15 - 11.09.2018 21:30
*/

#include "std_lib_facilities.h"

template<typename T> class Allocator;

template<typename T, typename A = Allocator<T>> class Vec {
public:
	Vec() : sz{0}, elem{nullptr}, space{0} { }
	explicit Vec(int s) : sz{s}, elem{alloc.allocate(s)}, space{s}
	{
		for (int i=0; i<sz; ++i) alloc.construct(&elem[i]);
	}

	Vec(const Vec&);
	Vec& operator=(const Vec&);

	~Vec() { alloc.deallocate(elem); }

	T& at(int n);
	const T& at(int n) const;

	T& operator[](int n);
	const T& operator[](int n) const;

	int size() const { return sz; }
	int capacity() const { return space; }

	void resize(int newsize, T val = T());	//growth
	void push_back(const T&);
	void reserve(int newaloc);
private:
	A alloc;
	int sz;
	T* elem;
	int space;
};

struct deleter {	//functor for custom delete operation, using with unique_ptr
	void operator()(void* p) { free(p); }
};

template<typename T, typename A> Vec<T,A>::Vec(const Vec<T,A>& v)
	: sz{v.size()}, elem{alloc.allocate(sz)}, space{sz}
{
	uninitialized_copy(v.elem, v.elem+sz, elem);
//	for (int i=0; i<sz; ++i) alloc.construct(&elem[i], v.elem[i]);
}

template<typename T, typename A> Vec<T,A>& Vec<T,A>::operator=(const Vec<T,A>& v)
{
	if (this == &v) return *this;			//self-assignment
	if (v.size() <= space) {			//enough space, no need for new allocation
		copy(v.elem, v.elem+v.size(), elem);
		sz = v.size();
		return *this;
	}
	unique_ptr<T,deleter> p {alloc.allocate(v.size())};
	uninitialized_copy(v.elem, v.elem+v.size(), p.get());

	for (int i=0; i<sz; ++i) alloc.destroy(&elem[i]);
	alloc.deallocate(elem);

	elem = p.release();
	space = sz = v.size();
	
	return *this;
}

template<typename T, typename A> void Vec<T,A>::resize(int newsize, T val)
{
	reserve(newsize);
	for (int i=sz; i<newsize; ++i) alloc.construct(&elem[i], val);
	for (int i=newsize; i<sz; ++i) alloc.destroy(&elem[i]);
	sz = newsize;
}

template<typename T, typename A> void Vec<T,A>::push_back(const T& val)
{
	if (space==0) reserve(8);		//start with space for 8 elements
	else if (sz==space) reserve(2*space);	//get more space
	alloc.construct(&elem[sz], val);	//add value to the end
	++sz;					//increase the size
}

template<typename T, typename A> void Vec<T,A>::reserve(int newalloc)	//reserve raw memory(not initializd) in the heap
{
	if (newalloc <= space) return;		//never decrease allocation

	unique_ptr<T,deleter> p {alloc.allocate(newalloc)};
	uninitialized_copy(elem, elem+sz, p.get());
	
	for (int i=0; i<sz; ++i) alloc.destroy(&elem[i]);
	alloc.deallocate(elem);
	
	elem = p.release();
	space = newalloc;
}

template<typename T, typename A> T& Vec<T,A>::at(int n)
{
	if (n<0 || n >= sz) throw Range_error(n);
	return elem[n];
}

template<typename T, typename A> const T& Vec<T,A>::at(int n) const
{
	if (n<0 || n >= sz) throw out_of_range();
	return elem[n];
}

template<typename T, typename A> T& Vec<T,A>::operator[](int n)
{
	return elem[n];
}

template<typename T, typename A> const T& Vec<T,A>::operator[](int n) const
{
	return elem[n];
}

//------------------------------------------------------------------------------//

struct alloc_error : public exception {
public:
	alloc_error(const string& ss) : s{ss} {}

	virtual const char* what() const noexcept override
	{
		return s.c_str();
	}

private:
	string s;	//contain error info
};

//------------------------------------------------------------------------------//

template<typename T> class Allocator {
public:

	T* allocate(int n);		//allocate space for n objects of type T
	void deallocate(T* p);		//deallocate previously allocated objects of type T starting at p

	void construct(T* p, const T& v = T());	//construct a T with the value v in p
	void destroy(T* p);			//destroy the T in p	

};

template<typename T> T* Allocator<T>::allocate(int n)
{
	T* p = (T*)(malloc(n*sizeof(T)));
	if (!p) throw bad_alloc();
	return p;
}

template<typename T> void Allocator<T>::deallocate(T* p)
{
	free(p);
}

template<typename T> void Allocator<T>::construct(T* p, const T& v)
{
	if (p == nullptr) throw alloc_error("Allocator<T>::construct(T* p, const T& v) can't construct by nullptr");
	p = new(p) T(v);
}

template<typename T> void Allocator<T>::destroy(T* p)
{
	if (p)
		p->~T();
}

int main()
try
{
	int step = 10;
	int max_num = 100;
	int num = 6;

	Vec<int> v(200);
	
	for (int i=0; i<max_num; ++i)
		v[i] = i;
	for (int i=0; i<v.size(); i+=step) {
		for (int j=0; j<step; ++j) {
			if (i+j>=v.size()) break;
			cout << setw(2) << v[i+j] << ' ';
		}
		cout << '\n';
	}
	Vec<int> v1 = v;
	cout << "v1.capacity() = " << v1.capacity() << " v1.size() = " << v1.size() << '\n';
	v1.reserve(500);
	cout << "v1.capacity() = " << v1.capacity() << " v1.size() = " << v1.size() << '\n';
	v1.resize(15);
	cout << "v1.capacity() = " << v1.capacity() << " v1.size() = " << v1.size() << '\n';
	v1.push_back(num);
	cout << "v1.push_back(" << num << ")\n"; 	
	cout << "v1.capacity() = " << v1.capacity() << " v1.size() = " << v1.size() << '\n';
	v1.resize(100);
	for (int i=0; i<max_num; i+=step) {
		for (int j=0; j<step; ++j) {
			if (i+j>=v1.size()) break;
			cout << setw(2) << v1[i+j] << ' ';
		}
		cout << '\n';
	}
	Vec<int> vi(34);
	v1 = vi;
	cout << "v1 = vi\n";
	cout << "v1.capacity() = " << v1.capacity() << " v1.size() = " << v1.size() << '\n';
	for (int i=0; i<max_num; i+=step) {
		for (int j=0; j<step; ++j) {
			if (i+j>=v1.size()) break;
			cout << setw(2) << v1[i+j] << ' ';
		}
		cout << '\n';
	}
//try to understand differences between copy() and uninitialized_copy()
//the only difference is that uninitialized_copy() call constructor(which can contain lock or a file descriptor)
//so uninitialized_copy() must use only with uninitialized memory or you can get resource leak(because old element isn't destroy).
//copy() just make assignement 
string* pi = (string*)malloc(5*sizeof(string));
//pi[3] = "future";
new(&pi[3]) string{"future"};
cout << pi[3] << '\n';
//pi[3] = "fred";
new(&pi[3]) string{"fred"};
cout << pi[3] << '\n';
//pi[3] = "fin";
new(&pi[3]) string{"fin"};
cout << pi[3] << '\n';

//v[-200] = v.at(200);
}
catch (exception& e) {
	cerr << "exception: " << e.what() << '\n';
	return 2;
}
catch (...) {
	cerr << "exception\n";
	return 3;
}
