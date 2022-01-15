//Chapter 18, drills with arrays
//07.07.2018 14:15

#include "std_lib_facilities.h"


int ga[10] = {1, 2, 4, 8, 16};

void f(int a[], int n)
{
	int la[10];
	memcpy(la, ga, 10*sizeof(int));

	for (int i = 0; i < 10; ++i)
		cout << "la [" << i << "]" << " = " << la[i] << '\n';
	int* p = new int[n];
	for (int i = 0; i < n; ++i)
		p[i] = a[i];
	for (int i = 0; i < 10; ++i)
		cout << "p [" << i << "]" << " = " << p[i] << '\n';
	
	delete[] p;
}

int fct(int n)
{
	int f = 1;
	for (int i = 2; i <= n; ++i)
		f *= i;
	return f;
}

int main()
{
	f(ga, 10);
	int aa[10];
	for (int i = 0; i < 10; ++i)
		aa[i] = fct(i+1);
	f(aa, 10);
}
