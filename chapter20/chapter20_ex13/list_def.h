//file for chapter20_ex12

/*
 * i had following error: In function `main':
 * chapter20_ex12.cpp:(.text+0x20): undefined reference to `Lib::list<int>::list()'
 * collect2: error: ld returned 1 exit status
 *
 * this helps
 * https://stackoverflow.com/questions/8752837/undefined-reference-to-template-class-constructor
 *
 * ways for solve:
 * 1.Explicitly instantiate the template, and its member definitions
 * 2.Copy the code into the relevant header file
*/

//template<typename C>
//using Iterator = typename C::iterator;

namespace Lib {

template<typename Elem>
list<Elem>::list() : first{nullptr} { }

template<typename Elem>
list<Elem>::list(std::initializer_list<Elem> l) : list() 
{
	for (const Elem& e : l) insert(end(), e);
}

template<typename Elem>
void list<Elem>::set_first(Link* p)
{
	first = p;
}

template<typename Elem>
class list<Elem>::iterator list<Elem>::begin()
{
	return first;
}

template<typename Elem>
class list<Elem>::iterator list<Elem>::end()
{
	return nullptr;
}

template<typename Elem>
class list<Elem>::iterator list<Elem>::last()	//doesn't work with empty list(cause error)
{
	return begin()->prev();
}

template<typename Elem>
class list<Elem>::iterator list<Elem>::insert(iterator p, const Elem& v)
//if p == iterator(nullptr) then insert elem before end() (after last elem) because iterator(nullptr) is the end() of the list
{
	Link* l = new Link{v};
	if (p!=end()) {
		//is p begin() ?
		if (iterator(p->prev())!=last()) p->prev()->set_succ(l);
		l->set_succ(p.get());

		l->set_prev(p->prev());
		p->set_prev(l);
	}
	else if (begin()!=end()) {			//list is not empty
		delete l;
		insert(last(), v);
		std::iter_swap(last(), --last());
		return last();
	}
	if (l->prev()==nullptr) {			//true if list is empty
		set_first(l);				//begin() of the list
		begin()->set_prev(l);			//begin()->prev() is the last elem
	}
	else if (iterator(l)==last())			//true if l inserted before begin()
		set_first(l);				//so in this case begin()->prev() is l
	return l;
}

template<typename Elem>
class list<Elem>::iterator list<Elem>::erase(iterator p)	//erase elem by p;
								//return elem behind p; don't try use p iterator after erase
{
	Link* tmp = p->succ();
	if (p!=begin()) p->prev()->set_succ(p->succ());
	else		set_first(tmp);					//p was the first elem in the list
	
	if (p->succ()!=nullptr)		p->succ()->set_prev(p->prev());
	else if (begin()!=nullptr)	begin()->set_prev(p->prev());	//p was the last elem in the list

	delete p.get();
	return tmp;
}

template<typename Elem>
void list<Elem>::push_back(const Elem& v)
{
	insert(end(), v);
}

template<typename Elem>
void list<Elem>::push_front(const Elem& v)
{
	insert(begin(), v);
}

template<typename Elem>
void list<Elem>::pop_back()
{
	erase(last());
}

template<typename Elem>
void list<Elem>::pop_front()
{
	erase(begin());
}

template<typename Elem>
size_t list<Elem>::size()
{
	size_t count = 0;
	for (auto p = begin(); p!=end(); ++p)
		++count;
	return count;
}

template<typename Elem>
Elem& list<Elem>::back()
{
	return *last();
}

template<typename Elem>
Elem& list<Elem>::front()
{
	return *begin();
}

template<typename Elem>
class list<Elem>::iterator {
public:
	iterator(Link* p) : curr{p} { }

	iterator& operator++()	{ curr = curr->succ(); return *this; }
	iterator& operator--()	{ curr = curr->prev(); return *this; }
	Elem& operator*()	{ return curr->value(); }
	Link* operator->()	{ return curr; }

	Link* get() { return curr; }

	bool operator==(const iterator& it) {return curr==it.curr; }
	bool operator!=(const iterator& it) { return curr!=it.curr; }

private:
	Link* curr;
};
}
