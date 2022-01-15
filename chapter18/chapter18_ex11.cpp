/*
	Chapter 18, exercise 11
	
	skip list

	24.07.2018 15:22 - 07.08.2018 23:07

*/

#include "std_lib_facilities.h"

//first level of skip_list is elements of vector with index 0 (e.g. succ[0] or prev[0])
struct skip_list {
public:
	skip_list(const int k, const string& d = "default")
		:key{k}, data{d} 
	{
		if (d == "header")
			for (int i = 0; i < MAX_LVL; ++i)
				succ.push_back(nullptr);

	}

	void insert(skip_list* l);			//insert l in skip_list
	void erase(const int key);			//remove element from skip_list by key
	string find(const int key) const;		//find data in skip_list by key
//	const skip_list* find(const int key) const;	//find data in const skip_list by key
	
	void debug() const;
	int rand_lvl() const;

private:
	const int MAX_LVL = 16;	//maximum number of levels in the skip list
	int key;			//data identifier
	string data;			//some data
	vector<skip_list*> succ;	//successors
	vector<skip_list*> prev;	//predecessors
};

int skip_list::rand_lvl() const
//generate random level between 1 and 16 inclusive
{
	const double p = 1.0/2;
	int lvl = 1;

	while (((double)rand() / RAND_MAX) < p && lvl < MAX_LVL)
		lvl += 1;
	return lvl;
}

void skip_list::debug() const
//print all skip_list's elements
{	
	const skip_list* ph = this;	//pointer to header
	const skip_list* p = ph;

	cout << "This skip_list is doubly linked, but backward arrows isn't displayed.\n";
	//lvl define header height
	for (int lvl = succ.size()-1; lvl >= 0; --lvl) {
		cout << "lvl: " << setw(2) << lvl << " header -> ";
		while (p->succ[lvl]) {
			const skip_list* pc = p;
			while (pc->succ[0]->key < p->succ[lvl]->key) {
				pc = pc->succ[0];
				//work with two-digit numbers only
				if (pc->succ[0]->key > 10)
					cout << "––––––";
				else
					cout << "–––––";
			}
			cout << p->succ[lvl]->key << " -> ";
			p = p->succ[lvl];
		}
		cout << '\n';
		p = ph;
	}
}

void skip_list::insert(skip_list* l)
//if l's key already exist then data will be modify by key
//else l will be add into list
{
	skip_list* p = this;			//first top left element (header)
	vector<skip_list*> update(MAX_LVL);	//contain all previous elements before l

	int lvl = succ.size()-1;		//lvl define header height
	while (lvl >= 0) {
		if (p->succ[lvl] == nullptr || p->succ[lvl]->key > l->key) {
			update[lvl] = p;
			--lvl;
		}
		else if (p->succ[lvl]->key < l->key) {
			p = p->succ[lvl];
		}
		else {	//if ==
			p->succ[lvl]->data = l->data;	//change old data
			return;
		}
	}
		//make an insert
		int r_lvl = rand_lvl();
		for (int i  = 0; i < r_lvl; ++i) {
			//element after l
			l->succ.push_back(update[i]->succ[i]);
			if (update[i]->succ[i] != nullptr)
				update[i]->succ[i]->prev[i] = l;
			
			//element before l
			update[i]->succ[i] = l;
			l->prev.push_back(update[i]);
		}
}

void skip_list::erase(const int key)
//erase element in skip_list by key
{
	skip_list* p = this;			//first top left element (header)
	vector<skip_list*> update(MAX_LVL);	//contain all previous elements before l

	int lvl = succ.size()-1;		//lvl define header height
	while (lvl >= 0) {
		if (p->succ[lvl] == nullptr || p->succ[lvl]->key > key)
			--lvl;
		else if (p->succ[lvl]->key < key)
			p = p->succ[lvl];
		else	//if ==
			break;
	}
		if (lvl == -1)
			lvl = 0;
		p = p->succ[lvl];	//p will be delete
		
		if (p == nullptr || p->key != key) {
			cout << "element with key number " << key << " wasn't deleted because wasn't found\n";
			return;
		}

		//delete element
		for (int i = 0; i < p->succ.size(); ++i) {
			p->prev[i]->succ[i] = p->succ[i];
			if (p->succ[i] != nullptr)
				p->succ[i]->prev[i] = p->prev[i];
		}
		delete p;
}

string skip_list::find(const int key) const
//find data in skip_list by key
{
	const skip_list* p = this;		//first top left element (header)
	vector<skip_list*> update(MAX_LVL);	//contain all previous elements before l

	int lvl = succ.size()-1;		//lvl define header height
	while (lvl >= 0) {
		if (p->succ[lvl] == nullptr || p->succ[lvl]->key > key)
			--lvl;
		else if (p->succ[lvl]->key < key)
			p = p->succ[lvl];
		else	//if ==
			return p->succ[lvl]->data;
	}
	cout << "element with key number " << key << " wasn't found\n";
	return "";
}

int main()
try
{
	srand(time(0));		//for rand_lvl() function

	//must always contain pointer of skip_list to header element because all operations start from header
	skip_list* header = new skip_list{-1, "header"};
	skip_list* sl = header;
	
	sl->debug();
	
	//just tests
	for (int i = 10; i < 20; ++i)
		sl->insert(new skip_list{i});
	sl->debug();

	for (int i = 0; i < 5; ++i)
		sl->insert(new skip_list{i});
	sl->debug();

	for (int i = 5; i < 10; ++i)
		sl->insert(new skip_list{i});
	sl->debug();

	for (int i = 6; i < 13; ++i)
		sl->erase(i);
	sl->debug();

	sl->erase(52);
//	sl->debug();

	skip_list* check = new skip_list (5, "apple");
	sl->insert(check);
	cout << sl->find(5) << '\n';

	for (int i = 0; i < 5; ++i)
		cout << sl->find(i) << '\n';

	//for big monitors :)
/*	for (int i = 25; i < 50; ++i)
		sl->insert(new skip_list{i});
	sl->debug();

	for (int i = 0; i < 10; ++i)
		sl->insert(new skip_list{i});
	sl->debug();
	
	for (int i = 10; i < 25 ; ++i)
		sl->insert(new skip_list{i});
	sl->debug();
*/

}
catch (exception& e) {
	cerr << "exception: " << e.what() << '\n';
}
catch (...) {
	cerr << "exception\n";
}
