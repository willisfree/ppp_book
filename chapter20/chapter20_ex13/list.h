//file for chapter20_ex12
//see #inlude at the end of this file
/*
 * Note:
 * 1. every list<Elem>::iterator obj constructed with nullptr will be interpret like result of list<Elem>::end(),
 * because one-past-the-end elem is nullptr by design solution.
 * 2. begin()->prev() == --end(), but --end()->succ()!=begin() by design. So, the begin()->prev() point to the last elem.
 * 3. you can't decrement end(), so --end() cause error; instead --end() use last()
 *
 */

namespace Lib {
template<typename Elem> class list {
public:
	struct Link;
	class iterator;
	using size_type = unsigned long;
	using value_type = Elem;

	list();
	list(std::initializer_list<Elem> l);

	iterator begin();
	iterator end();
	iterator last();				//return iterator to the last elem
							//doesn't work with empty list(cause error)

	iterator insert(iterator p, const Elem& v);	//insert v before p;
							//supposed that user set correct value in range [first, last] 
	iterator erase(iterator p);			//erase elem by p; return next after p
							//don't try use p iterator after erase
							//supposed that user set correct value in range [first, last) 

	void push_back(const Elem& v);			//insert v at the end
	void push_front(const Elem& v);			//insert v at the beginning
	void pop_back();				//delete last element
	void pop_front();				//delete first element

	size_t size();					//return count of elements in list
	Elem& back();					//return last elem by reference
	Elem& front();					//return first elem by reference

private:
	void set_first(Link* p);			//set first elem
	Link* first;
};

template<typename Elem>
struct list<Elem>::Link {
	Link() : p{nullptr}, s{nullptr}, val{Elem{}} { }
	Link(const Elem& v) : p{nullptr}, s{nullptr}, val{v} { }

	Link* prev() const { return p; }
	Link* succ() const { return s; }

	void set_prev(Link* pp) { p = pp; }
	void set_succ(Link* ss) { s = ss; }
	Elem& value()	{ return val; }

private:
	Link* p;	//previous
	Link* s;	//successor
	Elem val;	//value
};
}
#include "list_def.h"
