/*
	Chapter 20, ex18

	02.11.2018 19:01 - 03.11.2018 16:42
*/

#include "std_lib_facilities.h"

//protected vector; diff from usual vector by range-cheked iterators and lack some member functions
template<typename T>
class pr_vector {
public:
	using size_type = typename vector<T>::size_type;
	class iterator;

	pr_vector() {}
	pr_vector(size_t n) : v(n) { }
	pr_vector(initializer_list<T> lst) : v{lst} { }

	iterator begin() { return iterator(v.begin(), v.end(), v.begin()); }
	iterator end() { return iterator(v.begin(), v.end(), v.end()); }

	void push_back(T val) { v.push_back(val); }

	size_type size() const { return v.size(); }
private:
	vector<T> v;
};

//random-access iterator
template<typename T>
class pr_vector<T>::iterator {
public:
	using vec_it = typename vector<T>::iterator;

	iterator(vec_it begin, vec_it end, vec_it it)	//begin must be result of begin()
							//end must be result of end()
		: first{begin}, last{end}, curr{it} { }

	iterator(const iterator& it)
		: first{it.first}, last{it.last}, curr{it.curr} { }

	iterator& operator++() {
		if (curr==last) throw runtime_error("out of range, while incrementing pr_vector::iterator");
		++curr;
		return *this;
	}
	iterator& operator--() {
		if (curr==first) throw runtime_error("out of range, while decrementing pr_vector::iterator");
		--curr;
		return *this; 
	}
	iterator operator+(size_type n) {
		if (last-curr < n) throw runtime_error("out of range, while using operator+() of pr_vector::iterator");
		return iterator(first, last, curr+n);
	}
	iterator operator-(size_type n) {
		if (curr-first < n) throw runtime_error("out of range, while using operator-() pr_vector::iterator"); 
		return iterator(first, last, curr-n);
	}
	iterator& operator+=(size_type n) {
		//*this = operator+(n);
		if (last-curr < n) throw runtime_error("out of range, while using operator+=() of pr_vector::iterator");
		curr+=n;
		return *this;
	}
	iterator& operator-=(size_type n) {
		if (curr-first < n) throw runtime_error("out of range, while using operator-=() pr_vector::iterator");
		curr-=n;
		return *this;
	}
	int operator-(const iterator& it) {
		return curr-it.curr;
	}

	T& operator*() { return *curr; }
	
	bool operator==(const iterator& it) { return it.curr==curr; }
	bool operator!=(const iterator& it) { return it.curr!=curr; }

private:
	vec_it first;	//first elem of vector
	vec_it last;	//last elem of vector
	vec_it curr;	//current elem of vector
};

int main()
try
{
	pr_vector<int> prv {1,2,3,4,5};
	cout << "prv.size(): " << prv.size() << '\n';
	cout << "pr_vector<int> prv: ";
	for (auto val : prv) cout << val << ' ';
	cout << '\n';
	pr_vector<char> v = {'a', 'c', 'f', 'g'};
	cout << "pr_vector<char> v: ";
	for (auto val : v) cout << val << ' ';
	cout << '\n';
	auto it = v.begin();
	//throw exception
	//cout << "it: " << *it << " it+5: " << *(it+5) << " it: " << *it << '\n';
	++it;
	cout << "it: " << *it << " | it-1: " << *(it-1) << " | it: " << *it << '\n';
	
	auto an_it = v.begin();
	an_it+=3;
	cout << "an_it: " << *an_it << '\n';
	cout << "an_it: " << *(an_it-=3) << "\nan_it: " << *an_it << '\n';
	//throw exception
	//cout << "an_it: " << *(an_it-=1) << '\n';
	cout << "v.size(): " << v.end() - v.begin() << '\n';

	if (it!=an_it) cout << "lol\n";
	else cout << "it == an_it\n";
}
catch (exception& e) {
	cerr << "exception: " << e.what() << '\n';
}
catch (...) {
	cerr << "exception\n";
}
