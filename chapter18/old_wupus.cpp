/*
	Chapter 18, exercise 12
	
	Hunt the Wumpus

	Map can be imagine like a doubly-linked list where each element is connected to the other through one with help of additional link 	
	14:11 11.08.2018
*/

#include "std_lib_facilities.h"

class Room {
public:
	Room(int number, Room* s = nullptr, Room* p = nullptr, Room* ad = nullptr)
		:num{number}, succ{s}, prev{p}, addl{ad} { }

	Room* insert(Room* r);		//insert r before this object
	Room* add_addl(Room* map);	//adds additional links to map
	Room* make_loop(Room* map);	//connect first element with last	

	int get_num() const { return num; }
	Room* next() const { return succ; }
	Room* get_addl() const { return addl; }
	void debug() const;		//print debug info
private:
	int num;
	string value;	//can be "bat", "pit"
	Room* succ;
	Room* prev;
	Room* addl;	//additional link
};

Room* Room::insert(Room* r)	//insert r before this; return r
{
	if (r == nullptr) return this;
	if (this == nullptr) return r;

	r->succ = this;
	if (prev) prev->succ = r;	
	r->prev = prev;
	prev = r;

	return r;
}
Room* Room::add_addl(Room* map)	//adds additional links	to map
{
	while(map) {
		if (!map->get_addl())

	}
}

Room* create_map(const vector<int>& v)	//creates a map of 20 rooms with number from 1 to 20 in random order
{
	Room* map = nullptr;
	for (int i = 0; i < v.size(); ++i)
		map = map->insert(new Room{v[i]});

	return map;
//	map->debug();
}

vector<int> rand_order_vec()	//creates vector of 20 numbers from 1 to 20 in random order (without duplicates)
{
	int count = 20;
	vector<int> num(count);
	vector<int> tmp;
	for (int i = 0; i < count; ++i)
		tmp.push_back(i+1);

	for (int i = 0; i < num.size(); ++i) {
		int index = rand()%count;
		num[i] = tmp[index];
		--count;
		tmp[index] = tmp[count];
	}
	return num;
}

int main()
try
{
	srand(time(0));
	//generate map
	vector<int> num = rand_order_vec();
/*	for (int i = 0; i < num.size(); ++i)
		cout << num[num.size()-i-1] << " ";
	cout << endl; */
	
	Room* map = create_map(num);

	while (map) {
		cout << map->get_num() << " ";
		map = map->next();
	}

	//add addl links
	//
}
catch (exception& e) {
	cerr << "exception: " << e.what() << '\n';
}
catch (...) {
	cerr << "exception\n";
}
