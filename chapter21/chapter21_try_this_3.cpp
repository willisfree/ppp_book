/*
	Chapter 21, try this 3

	13.11.2018 19:23 - 20.42
*/

#include "std_lib_facilities.h"

double weight_value(const pair<string,double>& a, const pair<string,double>& b)
{
	return a.second*b.second;
}

int main()
try
{
	map<string, double> dow_price = {
		{"MMM", 199.80}, {"AAPL", 194.35}, {"INTC", 48.005}, {"DIS", 116.97}
	};
	map<string, double> dow_weight = {
		{"MMM", 5.26}, {"AAPL", 5.19}, {"INTC", 1.25}, {"DIS", 3.12}
	};
	map<string, string> dow_name = {
		{"MMM", "3M Co."}, {"AAPL", "Apple Inc."}, {"INTC", "Intel Corp."}, {"DIS", "Walt Disney Co."}
	};

	double apple_price = dow_price["AAPL"];
	double intel_price = dow_price["INTC"];
	double disney_price = dow_price["DIS"];

	if (dow_price.find("MMM")!=dow_price.end())
		cout << "3M Company in the Dow\n";

	cout << "\ndata relevant only 11.11.2018\n";
	cout << "Symbol\tPrice\tWeight\tName\n";
	cout << "----------------------------\n";
	for (const auto& p : dow_price) {
		const string& symbol = p.first;
		cout << symbol << '\t'
			<< p.second << '\t'
			<< dow_weight[symbol] << '\t'
			<< dow_name[symbol] << '\n';
	}
	double djia = inner_product(
			dow_price.begin(), dow_price.end(),
			dow_weight.begin(),
			0.0,
			plus<double>(),
			weight_value);
	cout << "\nDow-Jones Index Average\t" << djia << '\n';
}
catch (exception& e) {
	cerr << "exception: " << e.what() << '\n';
}
catch (...) {
	cerr << "exception\n";
}
