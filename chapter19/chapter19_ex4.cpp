/*
	Chapter 19, exercise 4

	31.08.2018 21:45
*/

#include "std_lib_facilities.h"

struct God {

	God(string n, string m, string v, string w)
		: name{n}, mythology{m}, vehicle{v}, weapon{w} {}

	string name;
	string mythology;
	string vehicle;
	string weapon;
};	

ostream& operator<<(ostream& os, const God& g)
{
	os << "Name: " << g.name << ", Mythology: " << g.mythology
		<< ", Vehicle: " << g.vehicle << ", Weapon: " << g.weapon;
	return os;
}

bool operator>(const God& l, const God& r)
{
	return (l.name > r.name); 
}

bool operator<(const God& l, const God& r)
{
	return !(l > r); 
}

bool operator==(const God& l, const God& r)
{
	return (l.mythology == r.mythology);
}

template<typename T> struct Link {	
	T value;
	Link* prev;
	Link* succ;
	Link(const T& v, Link* p = nullptr, Link* s = nullptr)
		: value{v}, prev{p}, succ{s} {}

	Link<T>* insert(Link<T>* p);		//insert p before this
	Link<T>* add(Link<T>* p);		//add p after this
	Link<T>* add_ordered(Link<T>* p);	//add element into list in lexicographical order
	Link<T>* find(const T& v);		//find elem in list by v
	Link<T>* erase();			//erase this from list; return this->succ
	Link<T>* clear() { prev = nullptr; succ = nullptr; }
	void debug() const { cout << value; }
};

template<typename T> Link<T>* Link<T>::insert(Link<T>* p)
{
	if (p == nullptr) return this;
	if (this == nullptr) return p;
	p->succ = this;
	if (prev) prev->succ = p;
	p->prev = prev;
	prev = p;

	return p;
}

template<typename T> Link<T>* Link<T>::add(Link<T>* p)
{
	if (p == nullptr) return this;
	if (this == nullptr) return p;
	p->prev = this;
	if (succ) succ->prev = p;
	p->succ = succ;
	succ = p;
	
	return p;
}

template<typename T> Link<T>* Link<T>::add_ordered(Link<T>* p)
{
	if (p == nullptr) return this;
	if (this == nullptr) return p;

	Link<T>* lst = this; //list
	while (p->value > lst->value) {	//! isn't hadle ==
		if (lst->succ == nullptr) {
			lst->add(p);
			return this;
		}
		lst = lst->succ;
	}	
	lst->insert(p);

	if (p->prev == nullptr) return p; 	//if p is first elem
	return this;
}

template<typename T> Link<T>* Link<T>::find(const T& v)
{
	Link<T>* p = this;
	while (p) {
		if (v == p->value) return p;
		p = p->succ;
	}
	return nullptr;
}

template<typename T> Link<T>* Link<T>::erase()
{
	if (this == nullptr) return this;
	if (succ) succ->prev = prev;
	if (prev) prev->succ = succ;
	return succ;
}

template<typename T> void print_all(const Link<T>* p)
{
	while (p) {
		cout << p->value << "\n\n";
		p = p->succ;
	}
}

template<typename T> Link<T>* make_lst(const T& v, Link<T>* f_lst, Link<T>*& s_cpy)
	//move all elements that are equal to v from s_lst to f_lst
{
	Link<T>* s_lst = s_cpy;
	while (s_lst) {
		s_lst = s_lst->find(v);
		if (s_lst) {
			Link<T>* p = s_lst;
			if (s_lst == s_cpy) s_cpy = s_cpy->succ;	//removable elem(s_lst) is s_cpy, thats why we move s_cpy forward
			s_lst = s_lst->erase();
			f_lst = f_lst->add_ordered(p->clear());
		}
	}
	return f_lst;
}

int main()
try
{
	//Norse
	God Thor {"Thor", "Norse", "", "hammer"};
	God Odin {"Odin", "Norse", "Eight-legged flying horse called Sleipner", "Spear called Gungnir"};
	God Freia {"Freia", "Norse", "Chariot with two wild cats", ""};
	//Greek
	God Zeus {"Zeus", "Greek", "", "lightning"};
	God Hera {"Hera", "Greek", "", "wand"};
	God Athena {"Athena", "Greek", "", "spear"};
	God Ares {"Ares", "Greek", "horses", "spear"};
	God Poseidon {"Poseidon", "Greek", "Horse", "trident"};
	God Aphrodite {"Aphrodite", "Greek", "", "roses"};
	//Roman
	God Mars {"Mars", "Roman", "", "spear"};
	God Jupiter {"Jupiter", "Roman", "", "lightning"};
	God Quirin {"Quirin", "Roman", "", "spear"};
	
	//all gods
	Link<God>* all_gods = new Link<God>{Thor};
//	all_gods = all_gods->insert(new Link<God>{Zeus});
	all_gods = all_gods->insert(new Link<God>{Aphrodite});
//	all_gods = all_gods->insert(new Link<God>{Quirin});
	all_gods = all_gods->insert(new Link<God>{Mars});
	all_gods = all_gods->insert(new Link<God>{Freia});
	all_gods = all_gods->insert(new Link<God>{Ares});
	all_gods = all_gods->insert(new Link<God>{Hera});
//	all_gods = all_gods->insert(new Link<God>{Athena});
	all_gods = all_gods->insert(new Link<God>{Jupiter});
	all_gods = all_gods->insert(new Link<God>{Poseidon});	
	all_gods = all_gods->insert(new Link<God>{Odin});

	all_gods = all_gods->add_ordered(new Link<God>{Zeus});
	all_gods = all_gods->add_ordered(new Link<God>{Quirin});
	all_gods = all_gods->add_ordered(new Link<God>{Athena});
	print_all(all_gods);
		cout << '\n';
	//norse gods
	Link<God>* norse_gods = nullptr;
	norse_gods = make_lst(God{"", "Norse", "", ""},norse_gods, all_gods);
	
	print_all(norse_gods);
		cout << '\n';	
	
	//greek gods
	Link<God>* greek_gods = nullptr;
	greek_gods = make_lst(God{"", "Greek", "", ""}, greek_gods, all_gods);
	
	print_all(greek_gods);
		cout << '\n';
	
	//roman gods
	Link<God>* roman_gods = nullptr;
	roman_gods = make_lst(God{"", "Roman", "", ""},roman_gods, all_gods);
	
	print_all(roman_gods);
		cout << '\n';
	cout << all_gods << '\n';
}
catch (exception& e) {
	cerr << "exception: " << e.what() << '\n';
}
catch (...) {
	cerr << "exception\n";
}
