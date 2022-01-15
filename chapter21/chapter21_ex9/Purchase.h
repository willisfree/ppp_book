#include <string>
#include <iostream>
#include <iomanip>
#include <stdexcept>

using std::string;
using std::istream;
using std::ostream;
using std::ios_base;
using std::cout;
using std::setw;

class Purchase {
public:
	Purchase() {}
	Purchase(const string& n, double p, int c)
		: name{n}, unit_price{p}, count{c} { }

	inline void print(int space) const;
	
	inline friend ostream& operator<<(ostream& os, const Purchase& buy);
private:
	string name;		//product name
	double unit_price;	//product price
	int count;		//product count
};

inline void Purchase::print(int space) const
{
	cout << setw(space) << name << setw(space) << unit_price << setw(space) << count << '\n';
}

ostream& operator<<(ostream& os, const Purchase& buy)
{
	char term = ';';
	os << '(';
	os << buy.name << term << buy.unit_price << term << buy.count;
	os << ')';
	return os;
}

inline istream& operator>>(istream& is, Purchase& buy)
{
	char ch1;
	if (is>>ch1 && ch1!='(') {
		is.unget();
		is.clear(ios_base::failbit);
		return is;
	}
	if(is.eof()) return is;

	char ch2, ch3;
	char term = ';';
	string name;
	double price;
	int count;
	if (getline(is>>std::ws, name, term))
		if (is>>price>>ch2>>count>>ch3) {
			if(ch2==term && ch3==')') {
				buy = Purchase{name, price, count};
				return is;
			}
		}
	throw std::runtime_error("bad purchase");
}
