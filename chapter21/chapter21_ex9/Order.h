#include <string>
#include <vector>
#include "Purchase.h"

using std::string;
using std::vector;

class Order {
public:
	Order() { }
	Order(const string& n, const string& addr, const string& info);

	void add_buy(const Purchase& buy);	//add buy into order

	void print(int space) const;

	string get_name() const { return name; }
	string addr() const { return address; }
	friend ostream& operator<<(ostream& os, const Order& order);
private:
	string name;			//customer name
	string address;			//customer address
	string data;			//additional info
	vector<Purchase> purchases;	//customer purchases
};

istream& operator>>(istream& is, Order& order);
bool operator<(const Order& a, const Order& b);
