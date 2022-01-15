//unused file

//file for chapter20_ex12
/*had following error: In function `main':
chapter20_ex12.cpp:(.text+0x20): undefined reference to `Lib::list<int>::list()'
collect2: error: ld returned 1 exit status

this helps
https://stackoverflow.com/questions/8752837/undefined-reference-to-template-class-constructor

ways for solve:
1.Explicitly instantiate the template, and its member definitions
2.Copy the code into the relevant header file
*/
 
#include <string>

using Lib::list;

template<typename Elem>	list<Elem>::list() : first{new Link{}}, last{first} { }

template<typename Elem> class list<Elem>::iterator {
public:
	iterator(Link* p) : curr{p} { }

	iterator& operator++() { curr = curr->succ; return *this; }
	iterator& operator--() { curr = curr->prev; return *this; }
	Elem& operator*() { return curr->val; }

	bool operator==(const iterator& it) {return curr==it.curr; }
	bool operator!=(const iterator& it) { return curr!=it.curr; }

private:
	Link* curr;
};

template class list<int>;
template class list<std::string>;
