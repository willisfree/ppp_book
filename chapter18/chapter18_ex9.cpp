/*
	Chapter 18, exercise 9
	how memory is allocating

	20.07.2018 14:30

*/

#include "std_lib_facilities.h"

void info(const void* a, const void* b, string s)
//IMOPRTANT: a pointer define first allocated object, b pointer define second allocated object
//print a and b adress with s's type storage
{
	int c = 0;
	if (a > b) {
		cout << a << " > " << b << '\n';
		c = 1;	// grow down
	}
	else if (a < b) {
		cout << a << " < " << b << '\n';
		c = -1;	//grow up
	}
	else 
		error("two identical adress in function info()\n");


	cout << s << " storage grows";
	switch (c) {
		case 1:
			cout << " downward.\n";
			break;
		case -1:
			cout << " upwards.\n";
			break;
		default:
			error("some error in function info() with c variable\n");
	}
}

int ia[2] {4, 5};

int ga = 0;
int gb = 0;

int main()
//on linux stack maybe grows upwards(at least i have on my computer)
{		
	info(&ia[0], &ia[1], "static array");

	info(&ga, &gb, "static");

	int sa[2] {7, 3};	//stack array
	info(&sa[0], &sa[1], "stack array");

	int* da = new int[2] {2, 3};
	info(&da[0], &da[1], "dynamic array");
	delete[] da;

	int c = 0;
	int d = 0;
	info(&c, &d, "stack");

	int* e = new int{3};
	int* f = new int{4};
	info(e, f, "dynamic");
	delete e;
	delete f;

	constexpr int ci = 1;
	constexpr double cd = 23.32;
	info(&ci, &cd, "stack");

	char a = 'f';
	char b = '\0';
	info(&a, &b, "stack");

}
