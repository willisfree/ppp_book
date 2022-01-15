/*
	Chapter 19, drills

	29.08.2018 12:42
*/

#include "std_lib_facilities.h"

template<typename T> struct S {
public:
	
	S(T v) : val{v} {}
	S<T>& operator=(const T& );
	T& set();

	T& get();	//identical to set()
	const T& get() const;
private:
	T val;
};

template<typename T> S<T>& S<T>::operator=(const T& v)
{
	if (val == v) return *this;
	val = v;
	return *this;
}

template<typename T> istream& operator>>(istream& is, vector<T>& v)
{
	char ch1, ch2, ch3, ch4;
	T v1, v2, v3;

	is >> ch1 >> v1 >> ch2 >> v2 >> ch3 >> v3 >> ch4;
	if (!is) return is;
	if (ch1 != '{' || ch2 != ',' || ch3 != ',' || ch4 != '}') {
		is.clear(ios_base::failbit);
		return is;
	}
	v.push_back(v1);
	v.push_back(v2);
	v.push_back(v3);
	
	return is;
}

template<typename T> ostream& operator<<(ostream& os, const vector<T>& v)
{
	int batch = 3;	//number of numbers in a row
	for (int i=0; i<v.size(); i+=batch) {
		os << '{';
		for (int j=0; j<batch; ++j)
			if ((i+j) >= v.size() )
				os << " -,";
			else
				os << ' '<< v[i+j] << ',';
		os << "}\n";
	}
	return os;
}


template<typename T> T& S<T>::set()
{
	return val;
}


template<typename T> T& S<T>::get()
{
	return val;
}

template<typename T> const T& S<T>::get() const
{
	return val;
}

template<typename T> void read_value(T& v)
{
	cout << ">";
	cin >> v.set();
	while (!cin) {
		cin.clear();
		cout << "set correct value: ";
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> v.set();
	}
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main()
try
{
	S<int> si = 20;
	S<char> sc = 'f';
	S<double> sd = 3.5;
	S<string> ss = string{"hello"};
	S<vector<int>> svi = vector<int>{1, 4, 5, 2, 7, 2, 11};

	cout << "S<int> = " << si.get() << " S<char> = "  << sc.get()
		<< " S<double> = " << sd.get() << " S<string> = " << ss.get() << '\n';
//	for (int i : svi.get())
//		cout << "S<vector<int>> = " << i << '\n';
	cout << svi.get();
//----------------------------------------------------------------------------------//
	//si.set() = 5;
	//ss.set() = string{"future"};
	
	si = 5;
	ss = "future";	
	cout << "si: " << si.get() <<  " ss: " << ss.get() << '\n';
//----------------------------------------------------------------------------------//
	read_value(si);
	read_value(sc);
	read_value(sd);
	read_value(ss);
	read_value(svi);


	cout << "S<int> = " << si.get() << " S<char> = "  << sc.get()
		<< " S<double> = " << sd.get() << " S<string> = " << ss.get() << '\n';
//	for (int i : svi.get())
//		cout << "S<vector<int>> = " << i << '\n';
	cout << svi.get();

}
catch (exception& e) {
	cerr << "exception: " << e.what() << '\n';
}
catch (...) {
	cerr << "exception\n";
}
