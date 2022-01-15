//file for chapter20_ex19

namespace Lib {

template<typename Elem>
list<Elem>::list() : first{new Link{}}, last{first} { }

template<typename Elem>
list<Elem>::list(std::initializer_list<Elem> l) : list() 
{
	for (const Elem& e : l) insert(end(), e);
}

template<typename Elem>
class list<Elem>::iterator list<Elem>::begin()
{
	return first;
}

template<typename Elem>
class list<Elem>::iterator list<Elem>::end()
{
	return last;
}

template<typename Elem>
class list<Elem>::iterator list<Elem>::insert(iterator p, const Elem& v)
{
	Link* l = new Link{v};
	if (p->prev()) p->prev()->succ() = l;
	l->succ() = p.get();
	
	l->prev() = p->prev();
	p->prev() = l;
	
	if (l->prev()==nullptr) first = l; //begin() of the list
	return l;
}

template<typename Elem>
class list<Elem>::iterator list<Elem>::erase(iterator p)	//erase elem by p;
								//return elem behind p; don't try use p iterator after erase
{
	Link* tmp = p->succ();
	if (p->prev()) p->prev()->succ() = p->succ();
	else first = tmp;	//p was the first elem in the list
	p->succ()->prev() = p->prev();

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
	erase(--end());
}

template<typename Elem>
void list<Elem>::pop_front()
{
	erase(begin());
}

template<typename Elem>
typename list<Elem>::size_type list<Elem>::size()
{
	size_type count = 0;
	for (auto p = begin(); p!=end(); ++p)
		++count;
	return count;
}

template<typename Elem>
Elem& list<Elem>::back()
{
	return *--end();
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

	iterator& operator++() {
		if (curr->succ()==nullptr) throw std::runtime_error("out of range while incrementing Lib::list<Elem>::iterator");
		curr = curr->succ();
		return *this;
	}
	iterator& operator--() {
		if (curr->prev()==nullptr) throw std::runtime_error("out of range while decrementing Lib::list<Elem>::iterator");
		curr = curr->prev();
		return *this;
	}
	Elem& operator*() { return curr->value(); }
	Link* operator->() { return curr; }

	Link* get() { return curr; }

	bool operator==(const iterator& it) {return curr==it.curr; }
	bool operator!=(const iterator& it) { return curr!=it.curr; }

private:
	Link* curr;
};
}
