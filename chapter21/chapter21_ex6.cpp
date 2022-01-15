/*
	Chapter 21, ex6

	24.11.2018 22:03 23:24
*/

#include "std_lib_facilities.h"
#include <set>

using Date = int;	//example: Date d = 24112018; //d is 24 of noveber 2018

struct Fruit {
	Fruit(const string& n = "", int c = 0, double uprice = 0.0, Date lsd = 0)
		: name{n}, count{c}, unit_price{uprice}, last_sale_date{lsd} { }
	
	string name;
	int count;
	double unit_price;
	Date last_sale_date;

};

ostream& operator<<(ostream& os, const Fruit& f)
{
	return os << "Name: " << f.name
		<< "\nCount: " << f.count
		<< " Unit_price: " << f.unit_price
	       	<< " Last_sale_date: " << f.last_sale_date;
}

struct Fruit_order {
	bool operator()(const Fruit& a, const Fruit& b)
	{
		return a.name < b.name;
	}
};

struct Ptr_Fruit_order {
	bool operator()(const Fruit* a, const Fruit* b)
	{
		return (*a).name < (*b).name;
	}
};

int main()
try
{
	vector<string> vs = {"Orange", "Grape", "Kiwi", "Apple", "Quince", "Plum"};
	int n = vs.size();
	set<Fruit*, Ptr_Fruit_order> inventory;
	
	for (int i=0; i<n; ++i)
		inventory.insert(new Fruit(vs[i]));
	for (auto v : inventory) cout << *v << '\n';
}
catch (exception& e) {
	cerr << "exception: " << e.what() << '\n';
}
catch (...) {
	cerr << "exception\n";
}
