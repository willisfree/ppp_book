//slist.h for chapter20_ex14.cpp
//single-linked list
#include <iostream>

template<typename Elem>
class slist {
public:
	struct Link;
	class iterator;
	using size_type = size_t;
	using value_type = Elem;

	slist();
	slist(const std::initializer_list<Elem> lst);

	iterator begin();
	iterator end();

	iterator insert_after(iterator p, const Elem& val);
	iterator erase_after(iterator p);

	void push_front(const Elem& val);	//insert val before first elem
	void pop_front();			//delete first elem

	Elem& front();
private:
	Link* first;
};
