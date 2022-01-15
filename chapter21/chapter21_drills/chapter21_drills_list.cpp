/*
	Chapter 21, drills with list

	17.11.2018 23:13 - 23:23
*/

#include "std_lib_facilities.h"

struct Item {
	string name;
	int iid;
	double value;
};

istream& operator>>(istream& is, Item& item)
{
	string name;
	int iid;
	double value;
	is >> name >> iid >> value;
	if (!is) return is;
	item = Item{name, iid, value};
	return is;
}

ostream& operator<<(ostream& os, const Item& item)
{
	return os << item.name << '\t' << item.iid << '\t' << item.value;
}

void gen_items(const string& name)
	//generate file with random items; one item per line; format: string(name), int(iid), double(value)
{
	ofstream ofs{name};
	int min = 'A', max = 'Z';
	int nitems = 10;
	int str_size = 3;
	for (size_t i=0; i<nitems; ++i) {
		for (size_t k=0; k<str_size; ++k) {
			ofs << char(min + rand()%(max-min));				//name
		}
		ofs << ' '<< i << ' '							//iid
			<< ((double)rand()/RAND_MAX)*100 << '\n';			//value
	}
}

template<typename C>	//Container<C>
void print(const C& c)
{
	for (const auto& v : c) cout << v << '\n';
}

bool cmp_item_by_iid(const Item& it1, const Item& it2)
{
	return it1.iid < it2.iid;
}

struct Cmp_item_by_value {	//larger than
	bool operator()(const Item& it1, const Item& it2) const
	{ return it1.value > it2.value; }
};

class Equal_by_iid {
	int val;
public:
	Equal_by_iid(int v) : val{v} { }
	bool operator()(const Item& it) const { return it.iid == val; }
};

int main()
try
{
	srand(time(0));
	string file = "data.txt";
	cout << "Enter file name: ";
	cin >> file;

	//gen_items(file);
	ifstream ifs{file};

	istream_iterator<Item> ii{ifs};
	istream_iterator<Item> eos;

	list<Item> vi {ii, eos};
	cout << "\t***original***\n";
	print(vi);
	
	vi.sort([](const Item& it1, const Item it2) { return it1.name < it2.name; });
	cout << "\t***after sort by name***\n";
	print(vi);
	
	vi.sort(cmp_item_by_iid);
	cout << "\t***after sort by iid***\n";
	print(vi);
	
	vi.sort(Cmp_item_by_value());
	cout << "\t***after sort by value***\n";
	print(vi);

	vi.push_back(Item{"horse shoe", 99, 12.34});
	vi.push_back(Item{"Canon S400", 9988, 499.95});
	cout << "\t***after insert***\n";
	print(vi);

	auto canon = find_if(vi.begin(), vi.end(), [](const Item& it) { return it.name == "Canon S400"; });
	if (canon!=vi.end())	vi.erase(canon);
	auto howk = find_if(vi.begin(), vi.end(), [](const Item& it) { return it.name == "Howk"; });
	if (howk!=vi.end())	vi.erase(howk);
	cout << "\t***after erase by name***\n";
	print(vi);

	int pan_id = 5;
	auto pan = find_if(vi.begin(), vi.end(), Equal_by_iid(pan_id));
	if (pan!=vi.end())	vi.erase(pan);
	int rony_id = 4;
	auto rony = find_if(vi.begin(), vi.end(), Equal_by_iid(rony_id));
	if (rony!=vi.end())	vi.erase(rony);
	cout << "\t***after erase by iid***\n";
	print(vi);


}
catch (exception& e) {
	cerr << "exception: " << e.what() << '\n';
}
catch (...) {
	cerr << "exception\n";
}
