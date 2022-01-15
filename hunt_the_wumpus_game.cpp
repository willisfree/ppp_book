/*
	Chapter 18, exercise 12
	
	Hunt the Wumpus

	Map can be imagine like a doubly-linked list where each element is connected to the other through one with help of additional link 	
	14:11 11.08.2018 - 19:15 18.08.2018
*/

#include "std_lib_facilities.h"

constexpr int NUM_OF_ROOMS = 20;	//number of rooms in the map (this program works only with 20(like a number of vertices in regular dodecahedron) rooms, more or less rooms can lead to crahes)

//ATTENTION: it's assumed that the list doesn't contain the same room numbers
class Room {
public:
	Room(int number, Room* s = nullptr, Room* p = nullptr, Room* ad = nullptr)
		:num{number}, succ{s}, prev{p}, addl{ad} { }

	Room* insert(Room* r);		//insert r before this object
	Room* find(const int n);	//find element by number
	void add_addl();		//adds additional links to map
	void make_loop();		//connects the first element with the last one
	void add_hazards();		//adds 2 pits, 2 bats and 1 wumpus
	void change_wumpus(bool b) { wumpus = b; }	//delete or set wumpus into room


	vector<Room*> get_ways() const;	//return succ, prev and addl into vector	
	Room* find_in_room(const int n) const; 	//return one of three possible ways for room, using number
	int get_num() const { return num; }
	Room* next() const { return succ; }
	Room* previous() const { return prev; }
	Room* additional() const { return addl; }
	bool check_pit() const { return pit; }
	bool check_bat() const { return bat; }
	bool check_wumpus() const { return wumpus; }
	
	void debug() const;		//print debug info
private:
	int num;	//number of room
	bool pit = false;
	bool bat = false;
	bool wumpus = false;
	Room* succ;	//successor
	Room* prev;	//predecessor
	Room* addl;	//additional link
};

Room* Room::find_in_room(const int n) const 	//return one of three possible ways for room, using number
{
	if (succ->num == n) return succ;
	if (prev->num == n) return prev;
	if (addl->num == n) return addl;
	return nullptr;
}

vector<Room*> Room::get_ways() const	//return succ, prev and addl into vector	
{
	vector<Room*> v;
	v.push_back(succ);
	v.push_back(prev);
	v.push_back(addl);
	return v;
}

void Room::debug() const	//print cave's state (number of room, pits, bats and wumpus)
{
	if (this == nullptr) {
		cerr << "try to call \"void Room::debug()\" function with nullptr of this object\n";
		return;
	}
	const Room* map = this;
	for (int i = 0; i < NUM_OF_ROOMS; ++i) {
		cout << "\n\tROOM " << map->num
			<< "\nsucc: " << map->succ->num
			<< " prev: " << map->prev->num
			<< " addl: " << map->addl->num << '\n';
		if (map->pit)
			cout << "PIT\n";
		if (map->bat)
			cout << "BAT\n";
		if (map->wumpus)
			cout << "WUMPUS here\n";		
	map = map->succ;
	}

}

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

bool is_closed(const Room* map)	//check list is closed or not; return true if is closed
{
	bool res = false;
	int n = map->get_num();
	while (map->next()) {
			if (map->next()->get_num() == n) {
			res = true;
			break;
		}
		map = map->next();
	}
	return res;
}

Room* Room::find(const int n)	//find element by number
				//works only with closed lists
				//it's assumed that the list doesn't contain the same room numbers
{
	if (this == nullptr) {
		cerr << "try to call \"Room* Room::find(const int n)\" function with nullptr of this object\n";
		return nullptr;
	}
	Room* map = this;
	if (!is_closed(map)) error ("try to use \"Room* Room::find(const int n)\" function with non-closed list\n");

	Room* tmp = map;
	int count = 0; //count of i
	while (count < 2) {
		if (map->num == n) return map;
		if (map == tmp) ++count;
		map = map->succ;	
	}
	return nullptr;
}

void Room::add_addl()	//adds additional links	to map
{
	if (this == nullptr) {
		cerr << "try to call \"void Room::add_addl()\" function with nullptr of this object\n";
		return;
	}
	Room* map = this;
	//move to the first element (begining of the list)
	while (map->prev)
		map = map->prev;
	
	//add addl
	while (map) {
		if (!map->addl) {
			Room* thr_one = map->succ->succ;	//element through one relative to map
			map->addl = thr_one;
			thr_one->addl = map;
		}
		map = map->succ;
	}
}

void Room::make_loop()	//connects the first element with the last one
{
	if (this == nullptr) {
		cerr << "try to call \"void Room::make_loop()\" function with nullptr of this object\n";
		return;
	}
	if (is_closed(this)) {
		cerr << "try to call \"void Room::make_loop()\" function with closed list\n";
		return;
	}
	Room* first = this;
	Room* last = this;
	//move to the begining of the list
	while (first->prev)
		first = first->prev;
	//move to the end of the list
	while (last->succ)
		last = last->succ;
	//loop
	last->succ = first;
	first->prev = last;
}

void Room::add_hazards()	//adds 2 pits, 2 bats and 1 wumpus
{
	if (this == nullptr) {
		cerr << "try to call \"void Room::add_hazards()\" function with nullptr of this object\n";
		return;
	}

	Room* map = this;
//	int count = NUM_OF_ROOMS;		//number of rooms

	int n = 1 + rand()%NUM_OF_ROOMS;
	for (int i = 0; i < 2; ++i) {
		//pits
		while (map->find(n)->pit || map->find(n)->bat)
			n = 1 + rand()%NUM_OF_ROOMS;
		map->find(n)->pit = true;
		//bats
		while (map->find(n)->pit || map->find(n)->bat)
			n = 1 + rand()%NUM_OF_ROOMS;
		map->find(n)->bat = true;
		}
	//wumpus
	n = 1 + rand()%NUM_OF_ROOMS;
	map->find(n)->wumpus = true;
}

Room* safe_room(Room* map);

Room* create_map(const vector<int>& v)	//creates a map of 20 rooms with number from 1 to 20 in random order
					//adds additional links, hazards and make the map closed
{
	if (v.size() != NUM_OF_ROOMS)
		error("function with name \"Room* create_map(const vector<int>& v)\" get vector with size diff from NUM_OF_ROOMS constant");
	Room* map = nullptr;
	for (int i = 0; i < v.size(); ++i)
		map = map->insert(new Room{v[i]});
	map->add_addl();
	map->make_loop();
	map->add_hazards();
	return safe_room(map);
}

vector<int> rand_order_vec()	//creates vector of 20 numbers from 1 to 20 in random order (without duplicates)
{
	int count = NUM_OF_ROOMS;		//number of rooms in the map 
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

void instructions()
{
	cout << "WELCOME TO 'HUNT THE WUMPUS'\n\tThe wumpus lives in a cave of 20 rooms: each room has 3 tunnels leading to other rooms. (look at a dodecahedron to see how this works. if you don't know what a dodecahedron is, ask someone)\n***\nHAZARDS:\nbottomless pits - two rooms have bottomless pits in them if you go there: you fall into the pit (& lose!)\nsuper bats  - two other rooms have super bats. if you go there, a bat grabs you and takes you to some other room at random. (which might be troublesome)\n\nWUMPUS:\nthe wumpus is not bothered by the hazards (he has sucker feet and is too big for a bat to lift). usually he is asleep. two things wake him up: your entering his room or your shooting an arrow.\nif the wumpus wakes, he moves (p=0.75) one room or stays still (p=0.25). after that, if he is where you are, he eats you up (& you lose!)\n\nYOU:\neach turn you may move or shoot a crooked arrow\n\nMOVING:\nyou can go one room (thru one tunnel)\n\nARROWS:\nyou have 5 arrows. you lose when you run out.\neach arrow can go from 1 to 5 rooms: you aim by telling the computer the rooms you want the arrow to go to. if the arrow can't go that way (ie no tunnel) it moves at random to the next room.\nif the arrow hits the wumpus: you win.\nif the arrow hits you: you lose.\n\nWARNINGS:\nwhen you are one room away from wumpus op hazard, the computer says:\nWUMPUS - 'i smell a Wumpus'\nBAT - 'bats nearby'\nPIT - 'i feel a draft'\n";
}

char correct_ans(char a, char b, istream& is)	//response user's answer; return correct
		//two first args define correct answers, third arg defines user's answer
{
	char ans;
	cin >> ans;
	while ((tolower(ans) != a) && (tolower(ans) != b)) {
			cout << "set correct answer: '" << a << "' or '" <<  b << "'\n:";
			is.ignore(numeric_limits<streamsize>::max(), '\n');
			cin >> ans;
		}
	is.ignore(numeric_limits<streamsize>::max(), '\n');
	return ans;
}

void poss_ways(Room* map)	//print possible ways
{
	if (map == nullptr) {
		cerr << "try to call \"void poss_ways(Room* map)\" function with nullptr of map\n";
		return;
	}
	cout << "You are in room:\t" << map->get_num()
		<< "\nTunnels lead to:\t" << map->next()->get_num() << "\t" << map->previous()->get_num()
	       	<< "\t" << map->additional()->get_num() << "\n\n";
}

Room* select_path(Room* map)	//user select path (number of room for move)
{
	if (map == nullptr) {
		cerr << "try to call \"Room* select_path(Room* map)\" function with nullptr of map\n";
		return nullptr;
	}
	int ans = 0;
	cout << "Where to? : ";
	cin >> ans;
	Room* way = map->find_in_room(ans);
	while (way == nullptr) {
		cout << "set correct way: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> ans;
		way = map->find_in_room(ans);
	}
	cout << '\n';
	return way;
}

void print_hazards(const Room* map)
{
	if (map == nullptr) {
		cerr << "try to call \"void print_hazards(const Room* map)\" function with nullptr of map\n";
		return;
	}
	vector<Room*> ways = map->get_ways();
	for (int i = 0; i < ways.size(); ++i) {
		if (ways[i]->check_bat())
			cout << "Bats nearby!\n";
		if (ways[i]->check_pit())
			cout << "I feel a draft!\n";
		if (ways[i]->check_wumpus())
			cout << "I smell a Wumpus!\n";
	}
}

bool is_lose(const Room* map)	//check if the player lose; return true if lose
{
	if (map == nullptr)
		error("try to call \"bool is_lose(const Room* map)\" function with nullptr of map");
	
	if (map->check_wumpus()) {
		cout << "...OOPS! BUMPED A WUMPUS!\n";
		return true;
	}
	if (map->check_pit()) {
		cout << "YYYIIIIEEEE . . . FELL IN PIT HA HA HA - YOU LOSE!\n";
		return true;
	}
	return false;
}

Room* snatch(Room* map)		//return random room in the cave
{
	if (map == nullptr) {
		cerr << "try to call \"Room* snatch(Room* map)\" function with nullptr of map\n";
		return nullptr;
	}
	cout << "ZAP--SUPER BAT SNATCH! ELSEWHEREVILLE FOR YOU!\n";
	return map->find(1+rand()%NUM_OF_ROOMS);
}

Room* safe_room(Room* map)	//return room without hazards
{
	while (map->check_pit() || map->check_bat() || map->check_wumpus())
		map = map->next();
	return map;
}

bool wumpus_move(Room* map, Room* player)	//change wumpus location
{
	double p = 1/4;
	vector<Room*> ways = map->get_ways();
	for (int i = 0; i < ways.size(); ++i)
		if (ways[i]->check_wumpus())
			if (rand()/double(RAND_MAX) < p) {	//move wumpus
				cout << "Wumpus moved to another room\n";
				ways[i]->change_wumpus(false);
				ways[i]->additional()->change_wumpus(true);
				if (ways[i]->additional() == player) {
					cout << "...OOPS! BUMPED A WUMPUS!\n";
					return true;
				}
			}
	return false;
}

bool shoot(Room* map, int n)	//diff arrow location with player location and wumpus location; return true if player lose or win
{
	Room* player = map;
	int num = 0;
	for (int i = 0; i < n; ++i) {
		cout << "Room? # ";
		cin >> num;
		while (num < 1 || num > NUM_OF_ROOMS) {
			cout << "set correct number: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin >> num;
		}
		//arrow select random way
		if (map->find_in_room(num) == nullptr) {
			cout << "You make mistake, arrow select random way\n";
			int rand_num = 0;
			while (i < n) {
				rand_num = 1+rand()%NUM_OF_ROOMS;
				cout << "Room? # " << rand_num << '\n';
				if (map->find(rand_num)->check_wumpus()) {
					cout << "AHA! YOU GOT THE WUMPUS! HEE HEE HEE - THE WUMPUS'LL GETCHA NEXT TIME!!\n";
					return true;
				}
				if (map->find(rand_num) == player) {
					cout << "HA HA HA YOU KILLED YOURSELF!\n";
					return true;
				}
				if (wumpus_move(map->find(rand_num), player))
					return true;
				++i;
			}
		}
		else {
			map = map->find_in_room(num);
			if (map->check_wumpus()) {
				cout << "AHA! YOU GOT THE WUMPUS! HEE HEE HEE - THE WUMPUS'LL GETCHA NEXT TIME!!\n";
				return true;
			}
			cout << map->get_num() << "         ------       " << player->get_num() << '\n'; 
			if (map == player) {
				cout << "HA HA HA YOU KILLED YOURSELF!\n";
				return true;
			}
			if (wumpus_move(map, player))
				return true;
		}
	}
	return false;	
}

bool make_shoot(Room* map)		//ask player number of rooms; return true if player lose or win
{
	if (map == nullptr)
		error ("try to call \"void make_shoot(const Room* player)\" function with nullptr of map");
	int count = 0;
	cout << "Number of rooms? (1-5): ";
	cin >> count;
	while (count < 1 || count > 5) {
			cout << "set correct number of rooms: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> count;
	}
	return shoot(map, count);
}

void game()
{	
	char yes = 'y', no = 'n';
	char shoot = 's', move = 'm';
	char ans;
	bool end_of_game = false;
	int arrows = 5;

	//generate map
	vector<int> num = rand_order_vec();	
	Room* map = create_map(num);
	Room* old_map = map;

	while (true) {
		cout << "Instructions? (y-n): ";
		ans = tolower(correct_ans(yes, no, cin));
		if (ans == yes)
			instructions();
		
		while (!end_of_game) {
			print_hazards(map);
			poss_ways(map);
			cout << "Shoot or move? (s-m): ";
			ans = tolower(correct_ans(shoot, move, cin));
			if (ans == move) {
				map = select_path(map);
				end_of_game = is_lose(map);
				if (!end_of_game) {
					if (map->check_bat())
						map = snatch(map);
					end_of_game = is_lose(map);
				}
			}
			else if (ans == shoot) {	
				end_of_game = make_shoot(map);	
				--arrows;
				if (arrows == 0) {
					cout << "You lost all your arrows.\n";
					end_of_game = true;
				}
				if (!end_of_game)
					cout << "Arrows left: " << arrows << "\n\n";
			}
		}
		cout << "The same setup? (y-n): ";
		ans = tolower(correct_ans(yes, no, cin));
		cout << ans << '\n';
		if (ans == no) {
			num = rand_order_vec();
			map = create_map(num);
			old_map = map;
		}
		else if (ans == yes)
			map = old_map;
		end_of_game = false;
		arrows = 5;
	}
}

int main()
try
{
	srand(time(0));
	game();
}
catch (exception& e) {
	cerr << "exception: " << e.what() << '\n';
}
catch (...) {
	cerr << "exception\n";
}
