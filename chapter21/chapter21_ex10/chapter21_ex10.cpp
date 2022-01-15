/*
	Chapter 21, exercise 10
	
	29.12.2018 15:30 - 16:46
*/
#include "Order.h"
#include "../std_lib_facilities.h"

struct Sort_by_addr{
	bool operator()(const Order& a, const Order& b) const
	{
		return a.addr() < b.addr();
	}
};

void test_vector(vector<Order>& orders)
{
	ofstream ofs{"orders_copy.txt"};
	if (!ofs) error("couldn't open orders_copy.txt");

	int max_length = 40;

	cout << "Total orders: " << orders.size() << '\n';
	
	cout << "---Before sort---\n";
	for (auto o : orders)
		cout << o.get_name() << '\n';

	sort(orders);
	cout << "---After sort---\n";
	for (auto o : orders)
		cout << o.get_name() << '\n';
	
	char ans;
	cout << "Do you want to see all orders?(y/n): ";
	cin >> ans;
	switch(ans) {
	case('y'):
		for (auto o : orders)
		o.print(max_length);
		break;
	default:
		break;
	}
/*	if (!cin) cin.clear();

	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "Do you want to make copy of all orders into orders_copy.txt?(y/n): ";
	cin >> ans;
	if (ans=='y')
		for (auto order : orders)
			ofs << order;
	cout << '\n';
*/

}

void test_list(list<Order>& lst)
{

	int max_length = 40;

	cout << "---Before sort---\n";
	for (auto o : lst)
		cout << o.addr() << '\n';

	lst.sort(Sort_by_addr());
	cout << "---After sort---\n";
	for (auto o : lst)
		cout << o.addr() << '\n';

	char ans;	
	cout << "Do you want to see all orders?(y/n): ";
	cin >> ans;
	if (ans=='y')
		for (auto order : lst)
			order.print(max_length);

}

void make_merge(const string& f1, const string& f2)
{
	ifstream ifs1{f1};
	if (!ifs1) error("couldn't open ", f1);
	ifstream ifs2{f2};	
	if (!ifs2) error("couldn't open ", f2);

	string common = "orders_merged.txt";
	ofstream ofs{common};
	if (!ofs) error("couldn't open ", common);
	
	merge(istream_iterator<Order>{ifs1}, istream_iterator<Order>{},
		istream_iterator<Order>{ifs2}, istream_iterator<Order>{},
		ostream_iterator<Order>{ofs, "\n"});

}

struct Sum_of_order {
	double operator()(double v, const Order& order) const
	{
		double sum = 0;
		auto purchases = order.get_purchases();	//can't use const vector<Purchase>& 
							//explicitly because in std_lib_facilities.h
							//used macro #define vector Vector
		for (auto buy : purchases)
			sum += buy.get_uprice()*buy.get_count();
		return v+sum;
	}

};

template<typename Cont, typename Cont2>
double get_sum(const Cont& first, const Cont2& second)
{
	double sum = 0;
	sum = accumulate(first.begin(), first.end(), sum, Sum_of_order()) + 
		accumulate(second.begin(), second.end(), sum, Sum_of_order());
	return sum;
}

int main()
try
{
	ifstream ifs{"orders.txt"};
	if (!ifs) error("couldn't open orders.txt");
		
	ifstream is{"orders_for_list.txt"};
	if (!is) error("couldn't open orders_for_list.txt");


	string file1 = "orders_copy_sort.txt";
	string file2 = "orders_for_list_sort_by_addr.txt";
	
	ofstream oos{file1};
	if (!oos) error("couldn't open ", file1);

	ofstream ofs{file2};
	if (!ofs) error("couldn't open ", file2);

	vector<Order> orders;
	for (Order order; ifs>>order; )
		orders.push_back(order);
	
	istream_iterator<Order> ii{is};
	list<Order> lst{ii, istream_iterator<Order>() };

	test_vector(orders);
	test_list(lst);

	for (auto buy : orders) oos << buy;
	for (auto buy : lst) ofs << buy;

	oos.close();
	ofs.close();
	make_merge(file1, file2);

	cout << "Sum of all orders from two files: " << get_sum(orders, lst) << " $\n";
}
catch(exception& e) {
	cerr << "exception: " << e.what() << '\n';
	return 1;
}
catch(...) {
	cerr << "exception\n";
	return 2;
}
