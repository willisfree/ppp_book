//Chapter 18, drills with vector
//08.07.2018 20:29

#include "std_lib_facilities.h"

vector<int> gv = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512};

void f(vector<int> vi)
{
	vector<int> lv(vi.size());
	lv = gv;
	for (int a : lv)
		cout << "lv : " << a << '\n';
	vector<int> lv2 = vi;
	for (int a : lv2)
		cout << "lv2 : " << a << '\n';
}

int fct(int n)
{
	int f = 1;
	for (int i = 2; i <= n; ++i)
		f*=i;
	return f;
}

int main()
{
	f(gv);
	vector<int> vv;
	for (int i = 0; i < 10; ++i)
		vv.push_back(fct(i+1));
	f(vv);
}
