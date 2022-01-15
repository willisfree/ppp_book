//definition for slist.h
//used with chapter20_ex14.cpp

template<typename Elem>
struct slist<Elem>::Link {
//	Link() : succ{nullptr}, val{Elem{}} { }

	Link(const Elem& v, Link* p = nullptr) : succ{p}, val{v} { }
	
	Link* succ;
	Elem val;
};

template<typename Elem>
class slist<Elem>::iterator {
public:
	iterator(Link* p) : curr{p} { }
	iterator& operator++() { curr = curr->succ; return *this; }
	Elem& operator*() { return curr->val; }
	Link* operator->() { return curr; }

	operator bool() const { return curr!=nullptr; }
	
	bool operator==(const iterator& it) { return curr==it.curr; }
	bool operator!=(const iterator& it) { return curr!=it.curr; }
private:
	Link* curr;
};

template<typename Elem>
slist<Elem>::slist() : first{nullptr} { }

template<typename Elem>
slist<Elem>::slist(const std::initializer_list<Elem> lst) : slist()
{
	auto p = begin();
	for (auto val : lst) p = insert_after(p, val);
}

template<typename Elem>
class slist<Elem>::iterator slist<Elem>::begin()
{
	return iterator(first);
}

template<typename Elem>
class slist<Elem>::iterator slist<Elem>::end()
{
	return iterator(nullptr);
}

template<typename Elem>
class slist<Elem>::iterator slist<Elem>::insert_after(iterator p, const Elem& val)	//insert val after p
{
	Link* ins = new Link{val};
	if (p) {
		ins->succ = p->succ;
		p->succ = ins;
	}
	else if (first) throw std::runtime_error("attemp to use slist<Elem>::insert_after(p, val) with p==nullptr, but list isn't empty");
	else {
		first = ins;
	}
	return iterator(ins);
}

template<typename Elem>
class slist<Elem>::iterator slist<Elem>::erase_after(iterator p)
	//return iterator to the element following the erased one, or end() if no such element exists.
{
	if (p) {
		if (p->succ) {
			Link* del = p->succ;
			p->succ = p->succ->succ;
			delete del;
			return p->succ;
		}
	}
	return end();
}

template<typename Elem>
void slist<Elem>::push_front(const Elem& val)
{
	Link* ins = new Link{val, first};
	//ins->succ = first;
	first = ins;
}

template<typename Elem>
void slist<Elem>::pop_front()
{
	Link* del = first;
	first = first->succ;
	delete del;
}

template<typename Elem>
Elem& slist<Elem>::front()
{
	return *begin();
}
