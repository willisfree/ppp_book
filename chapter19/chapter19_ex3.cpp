/*
	Chapter 19, exercise 3

	31.08.2018 18:27
*/

#include "std_lib_facilities.h"

template<typename T, typename A> class Pair {
public:
	Pair(T tt = T(), A aa = A()) : up{tt}, bottom{aa} { }
	Pair(A aa, T tt = T()) : up{tt}, bottom{aa} { }

	T get_up() const { return up; }
	A get_bottom() const { return bottom; }

private:
	T up;
	A bottom;
};

struct ND {
	ND(int i) : a{i} {}
	int a;
};

int main()
try
{	
	Pair<int,string> pr {"future"};
	cout << pr.get_up() << " " << pr.get_bottom() << '\n';

	Pair<int,string> pi {4};
	cout << pi.get_up() << " " << pi.get_bottom() << '\n';

	Pair<ND,string> ns {"home", 3};
	cout << ns.get_up().a << " " << ns.get_bottom() << '\n';

	Pair<int,double> p;
	cout << p.get_up() << " " << p.get_bottom() << '\n';

	int min = 100;
	int max = 400;
	vector<Pair<int, char>> sym;
	for (int i=min; i<max; ++i)
		sym.push_back(Pair<int, char>{i, char(i)});

	cout << "******symbols_tabel*******\n";
	int num = 10;
	for (int i=0; i<max-min; i+=num) {
		for (int j=0; j<num; ++j)
			cout << setw(5) << sym[i+j].get_up() << " ";
		cout << '\n';
		for (int j=0; j<num; ++j)
			cout << setw(5) << sym[i+j].get_bottom() << " ";
		cout << "\n\n";
	}
}
catch (exception& e) {
	cerr << "exception: " << e.what() << '\n';
}
catch (...) {
	cerr << "exception\n";
}
