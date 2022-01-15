#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include "Order.h"

using std::string;
using std::vector;
using std::istream;
using std::cout;
using std::ios_base;
using std::setw;

Order::Order(const string& n, const string& addr, const string& info)
	: name{n}, address{addr}, data{info} { }

void Order::add_buy(const Purchase& buy)
{
	purchases.push_back(buy);
}

void Order::print(int space) const
{
	cout << std::left;
	cout << "*********Order********\n" 
		<< setw(space) << "Name" << setw(space) << "Address" << setw(space) << "Additional info" << '\n'
		<< string(space*3, '-') << '\n';
	cout << setw(space) << name << setw(space) << address << setw(space) << data << '\n';
	cout << '\n' << name+"'s" << " purchases:\n";

	cout << setw(space) << "Name" << setw(space) << "Price" << setw(space) << "Count" << '\n'
		<< string(space*3, '-') << '\n';
	for (auto buy : purchases)
		buy.print(space);
	cout << '\n';
}

istream& operator>>(istream& is, Order& order)
{
	char ch1;
	if (is>>ch1 && ch1!='{') {
		std::cout << "ch1: " << ch1 << '\n';
		is.unget();
		is.clear(ios_base::failbit);
		return is;
	}
	if (is.eof()) return is;	//spent a lot of time to find this solution
	
	char ch2;
	char term = ';';
	string name;
	string addr;
	string data;
	if (getline(is>>std::ws, name, term))
		if (getline(is>>std::ws, addr, term))
			if (getline(is>>std::ws, data, term)) {
				order = Order{name, addr, data}; 
				for (Purchase buy; is>>buy; )
					order.add_buy(buy);
				is.clear();
				if(is>>ch2 && ch2=='}')
					return is;
			}	
	throw std::runtime_error("bad order");
}

ostream& operator<<(ostream& os , const Order& order)
{
	char term = ';';
	os << '{';
	os << order.name << term << order.address << term << order.data << term;
	for(auto buy : order.purchases) os << buy;
	os << '}';
	return os;
}

bool operator<(const Order& a, const Order& b)
{
	return a.get_name() < b.get_name();
}
