//file for chapter20_ex12
//see #inlude at the end of this file

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

	iterator insert(iterator p, const Elem& v);	//insert v before p;
							//supposed that user set correct value in range [first, last) 
	iterator erase(iterator p);			//erase elem by p; return next after p
							//don't try use p iterator after erase
							//supposed that user set correct value in range [first, last) 

	void push_back(const Elem& v);			//insert v at the end
	void push_front(const Elem& v);			//insert v at the beginning
	void pop_back();				//delete last element
	void pop_front();				//delete first element

	size_type size();				//return count of elements in list
	Elem& back();					//return last elem by reference
	Elem& front();					//return first elem by reference

private:
	Link* first;
	Link* last;
};

template<typename Elem>
struct list<Elem>::Link {
	Link() : p{nullptr}, s{nullptr}, val{Elem{}} { }
	Link(const Elem& v) : p{nullptr}, s{nullptr}, val{v} { }
	
	Link*& prev()	{ return p; }
	Link*& succ()	{ return s; }
	Elem& value()	{ return val; }

private:
	Link* p;	//previous
	Link* s;	//successor
	Elem val;	//value
};
}
#include "list_def.h"
