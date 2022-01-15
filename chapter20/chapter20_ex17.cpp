/*
	Chapter 20, ex 17
	
	01.11.2018 22:45 - 23:35
*/

#include "std_lib_facilities.h"

//deletes only those objects that were pass like pointers
template<typename T>
class ownership_vector {
public:
	ownership_vector() { }
	ownership_vector(const initializer_list<T*> lst)
	{
		for (T* p : lst) { v.push_back(p); owned.push_back(p); }
	}
	ownership_vector(const ownership_vector&) = delete;
	ownership_vector& operator=(const ownership_vector&) = delete;
	~ownership_vector()
	{

		for (T* p : owned) {
			cout << "deleting: " << *p << '\n'; 
			delete p;
		}
	}

	void push_back(T& r) { v.push_back(&r); };
	void push_back(T* p) { v.push_back(p); owned.push_back(p); };

	T& operator[](int i) { return *v[i]; }
	const T& operator[](int i) const { return *v[i]; }

	int size() const { return v.size(); }

private:
	vector<T*> v;
	vector<T*> owned;
};

template<typename T>
using own_vec = ownership_vector<T>;

int main()
try
{
	int a = 4;
	int b = 5;
	int c = 6;
	own_vec<int> ov = {new int{1}, new int{2}, new int{3}};
	ov.push_back(a);
	ov.push_back(b);
	ov.push_back(c);

	for (int i=0; i<ov.size(); ++i)
		cout << ov[i] << '\n';
}
catch (exception& e) {
	cout << "exception: " << e.what() << '\n';
}
catch (...) {
	cout << "exception\n";
}
