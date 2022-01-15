/*
	Chapter 19, exercise 16

	15.09.2018 23:29 - 16.09.2018 19:01
*/

#include "std_lib_facilities.h"

template<typename T> class Allocator;

template<typename T, typename A> struct vec_base {
	A alloc;
	T* elem;
	int sz;
	int space;

	vec_base(const A& a, int s)
		:alloc{a}, elem{alloc.allocate(s)}, sz{s}, space{s} { }
	~vec_base() { alloc.deallocate(elem); }
};

template<typename T, typename A = Allocator<T>> class Vec {
public:
	explicit Vec(int s=0) : vb{new vec_base<T,A>(A{}, s)}
	{
		for (int i=0; i<vb->sz; ++i) vb->alloc.construct(&(vb->elem[i]));
	}

	Vec(const Vec&);
	Vec& operator=(const Vec&);

	~Vec()
	{
		for (int i=0; i<size(); ++i)
			vb->alloc.destroy(&(vb->elem[i]));
		delete vb;
	}

	T& at(int n);
	const T& at(int n) const;

	T& operator[](int n);
	const T& operator[](int n) const;

	int size() const { return vb->sz; }
	int capacity() const { return vb->space; }

	void resize(int newsize, const T val = T());	//growth
	void push_back(const T&);
	void reserve(int newaloc);
private:
	vec_base<T,A>* vb;
};

struct deleter {	//functor for custom delete operation, using with unique_ptr
	void operator()(void* p) { free(p); }
};

template<typename T, typename A> Vec<T,A>::Vec(const Vec<T,A>& v)
	:vb{new vec_base<T,A>(A{}, v.size())}
{
	uninitialized_copy(v.vb->elem, v.vb->elem+v.size(), vb->elem);
}

template<typename T, typename A> Vec<T,A>& Vec<T,A>::operator=(const Vec<T,A>& v)
{
	if (this == &v) return *this;			//self-assignment
	if (v.size() <= vb->space) {			//enough space, no need for new allocation
		copy(v.vb->elem, v.vb->elem+v.size(), vb->elem);
		for (int i=v.size(); i<vb->sz; ++i)
			vb->alloc.destroy(&(vb->elem[i]));	//if v.size() < this->vb->sz , then destroy elements in this range
		vb->sz = v.size();
		return *this;
	}
	unique_ptr<T,deleter> p {vb->alloc.allocate(v.size())};
	uninitialized_copy(v.vb->elem, v.vb->elem+v.size(), p.get());

	for (int i=0; i<vb->sz; ++i) vb->alloc.destroy(&(vb->elem[i]));
	vb->alloc.deallocate(vb->elem);

	vb->elem = p.release();
	vb->space = vb->sz = v.size();
	
	return *this;
}

template<typename T, typename A> void Vec<T,A>::resize(int newsize, const T val)
{
	reserve(newsize);
	for (int i=vb->sz; i<newsize; ++i) vb->alloc.construct(&(vb->elem[i]), val);
	for (int i=newsize; i<vb->sz; ++i) vb->alloc.destroy(&(vb->elem[i]));
	vb->sz = newsize;
}

template<typename T, typename A> void Vec<T,A>::push_back(const T& val)
{
	if (vb->space==0) reserve(8);				//start with space for 8 elements
	else if (vb->sz==vb->space) reserve(2*vb->space);	//get more space
	vb->alloc.construct(&(vb->elem[vb->sz]), val);		//add value to the end
	++(vb->sz);						//increase the size
}

template<typename T, typename A> void Vec<T,A>::reserve(int newalloc)	//reserve raw memory(not initializd) in the heap
{
	if (newalloc <= vb->space) return;		//never decrease allocation

	unique_ptr<T,deleter> p {vb->alloc.allocate(newalloc)};
	uninitialized_copy(vb->elem, vb->elem+vb->sz, p.get());
	
	for (int i=0; i<vb->sz; ++i) vb->alloc.destroy(&(vb->elem[i]));
	vb->alloc.deallocate(vb->elem);
	
	vb->elem = p.release();
	vb->space = newalloc;
}

template<typename T, typename A> T& Vec<T,A>::at(int n)
{
	if (n<0 || n >= vb->sz) throw Range_error(n);
	return vb->elem[n];
}

template<typename T, typename A> const T& Vec<T,A>::at(int n) const
{
	if (n<0 || n >= vb->sz) throw out_of_range();
	return vb->elem[n];
}

template<typename T, typename A> T& Vec<T,A>::operator[](int n)
{
	return vb->elem[n];
}

template<typename T, typename A> const T& Vec<T,A>::operator[](int n) const
{
	return vb->elem[n];
}

//------------------------------------------------------------------------------//
//it will be better use inheritance by runtime_error
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
//	Vec<int> err(-1);
	Vec<string> vs;
	cout << "vs.size() = " << vs.size() << " vs.capacity() = " << vs.capacity() << '\n';

	int step = 30;
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
	cout << "sizeof(int*) = " << sizeof(int*) << "\nsizeof(Vec<int>) = " << sizeof(Vec<int>)
		<< "\nsizeof(vec_base<T,A>) = " << sizeof(vec_base<int, Allocator<int>>)
		<< "\nsizeof(vector<int>) = " << sizeof(vector<int>) << '\n';
}
catch (exception& e) {
	cerr << "exception: " << e.what() << '\n';
	return 1;
}
catch (...) {
	cerr << "exception\n";
	return 2;
}
