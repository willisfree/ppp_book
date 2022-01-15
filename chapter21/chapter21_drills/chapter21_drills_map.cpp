/*
	Chapter 21, drills with map

	17.11.2018 23:23 - 19.11.2018 19:35
*/

#include "std_lib_facilities.h"

template<typename T, typename U>
ostream& operator<<(ostream& os, const pair<T, U>& pair)
{
	return os << pair.first << '\t' << pair.second;
}

template<typename C>
void print(const C& c)
{
	for (auto v : c) cout << v << '\n';
}

template<typename T, typename U, typename C = map<T,U>>
bool read_pair(C& c, istream& is, T stop)	//return true if input was correct and pair was inserted; false in another way
{
	T first;
	U second;
	is >> first >> second;
	if (!is) error("wrong value");
	if (first==stop) return false;
	c.insert(make_pair(first,second));
	return true;
}

int main()
try
{
	srand(time(NULL));
	//1
	map<string, int> msi;
	
	//2
	int nwords = 10;
	int max_rand = 30;
	ifstream ifs{"data_map.txt"};
	istream_iterator<string> is{ifs};
	istream_iterator<string> eos;
	
	while (is!=eos) {
		msi[*is]=rand()%max_rand;
		++is;
	}
	
	//3
	cout << "\t***original map***\n";
	print(msi);	
	
	//4
	//for (auto p = msi.begin(); p!=msi.end(); ++p)	msi.erase(p);
	cout << "\t***after erase two elements***\n";
	auto andy = msi.find("Andy");
	auto rony = msi.find("Rony");
	msi.erase(andy);
	msi.erase(rony);

	print(msi);
	cout << "\t***end of erase***\n";

	//5,6
	string terminate = "|";
	bool read_state = true;
	while (read_state) {
		cout << "enter pair<string, int> of value: ";
		read_state = read_pair<string, int>(msi, cin, terminate);
	}	
	
	//7
	cout << "\t***after insert elements***\n";
	print(msi);

	//8
	int sum = accumulate(msi.begin(), msi.end(), 0, [](int init, const pair<string, int>& p) { return init+p.second; });
	cout << "\nsum of all elements: ";
	cout << sum << '\n';

	//9
	map<int, string> mis;

	//10
	for (auto p : msi)
		mis[p.second]=p.first;

	//11
	cout << "\t***original map<int, string> mis***\n";
	print(mis);
}
catch (exception& e) {
	cerr << "exception: " << e.what() << '\n';
}
catch (...) {
	cerr << "exception\n";
}
