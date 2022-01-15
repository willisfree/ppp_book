/* Chapter 18, exercise 4
 
   all functions assume that user know the real size of c_string that he used like argument
	10.07.2018 
	ex1 13:01
	ex2 14:00
	
	ex3 12:52 11.07.2018
	ex4 15:01 12-13.07.2018 all functions get max variable
*/

#include "std_lib_facilities.h"

int strcmp(const char* s1, const char* s2, int max)
//it's impossible to make this function correct if s1 or s2 doesn't contain null terminator character
//max var define the longest c_str
{
	if (s1 == nullptr)
		cerr << "strcmp() get s1 with nullptr!\n";
		//throw exception

	if (s2 == nullptr)
		cerr << "strcmp() get s2 with nullptr!\n";
		//throw exception

	for (int i = 0; i < max; ++i)
		if (*s1 == *s2) {
			++s1;
			++s2;
		}
		else if (*s1 > *s2)
			return 1;	//s2 before s1
		else
			return -1;	//s1 before s2
}

char* strdup(const char* c_str, int max)
{
	char* p = new char;
	char* pp = p;	//pointer to the first element of p
	for (int i = 0; i < max; ++i) {
		*p = *c_str;
//		cerr << "*p = " << *p << '\n';
		++p;
		++c_str;
	}
	return pp;
}

bool is_cong(const char* s, const char* x, char** p, int xmax)
//compares all characters from x with x's amount characters from s
//if is congruent set p pointer to the first congruent character in string s and return true
//else return false
{
	if (s == nullptr) {
		cerr << "is_cong() get s with nullptr!\n";
		return false;
	}
	if (x == nullptr) {
		cerr << "is_cong() get x with nullptr!\n";
		return false;
	}

	*p = strdup(s);		//copy all characters from the first occurrence of the x to the end of s
	//! s pointer can be out of range, but i don't think it's serious
	for (int i = 0; i < xmax; ++i) {
//		cerr << "*p = " << *p << '\n';
			if(*s != *x) {
				*p = nullptr;
				return false;
			}
			++s;
			++x;
	}
	return true;
}

char* findx(const char* s, const char* x, int smax, int xmax)
{
	if (s == nullptr) {
		cerr << "findx() get s with nullptr!\n";
		return nullptr;
	}
	if (x == nullptr) {
		cerr << "findx() get x with nullptr!\n";
		return nullptr;
	}

	char* p = new char;
	for (int i = 0; i < smax; ++i) {
		if(*s == *x)
			if(is_cong(s, x, &p, xmax))
			return p;
	++s;	
	}
	return nullptr;		//just in case
}

ostream& display_cstr(ostream& os, const char* c_str, int number)
//print char array of number's size characters
{
	for (int i = 0; i < number; ++i) {
		os << *c_str;
		++c_str;
	}
	return os;
}


int main()
{
	char cstr[] = "Hello!";
	char* pc = strdup(cstr, 6);
	cout << "*pc = " << pc << '\n';
	delete[] pc;

	char sent[] = "Happy birthday, Garry!";
	char word[] = "day";
	char* occu = findx(sent, word, 22 ,3);
	if (occu == nullptr)
		cerr << "nothing found\n";
	else {
		cout << "First occurrence of \"" << word << "\" in \"" << sent << "\" -> " << occu << '\n';
		delete[] occu;
	}
	char s1[] = "day";
	char s2[] = "days";
	int res = strcmp(s1, s2, 4);
	if (res > 0)
		cout << "s1 is lexicographically after s2\n";
	else if (res == 0)
		cout << "s1 is lexicographically equals to s2\n";
	else
		cout << "s1 is lexicographically before s2\n";
	
	char t[] = {'i', 'n', 'd', 'y'};
	char* tc = strdup(t, 4);
	cout << "*tc = " << tc << '\n';
	delete[] tc;
	char tsent[] = "indy developer.";
	char* toccu = findx(tsent, t, 15, 4);
	if (toccu == nullptr)
		cerr << "nothing found\n";
	else {
		cout << "First occurrence of \"";
		display_cstr(cout, t, 4);
		cout << "\" in \"" << tsent << "\" -> " << toccu << '\n';
		delete[] toccu;
	}
	char ts1[] = {'d', 'a', 'y', 's'};
        char ts2[] = {'d', 'a', 'y'};
        int tres = strcmp(ts1, ts2, 4);
	if (tres > 0)
        	cout << "s1 is lexicographically after s2\n";
        else if (tres == 0)
        	cout << "s1 is lexicographically equals to s2\n";
        else
        	cout << "s1 is lexicographically before s2\n";



	char* dt = new char[4] {'i', 'n', 'd', 'y'};	//temp c_str in dynamic memory
	char* dtc = strdup(dt, 4);
	cout << "*dtc = " << dtc << '\n';
	delete[] dtc;
	char dtsent[] = "indy developer.";
	char* toccur = findx(dtsent, dt, 15, 4);
	if (toccu == nullptr)
		cerr << "nothing found\n";
	else {
		cout << "First occurrence of \"";
       		display_cstr(cout, dt, 4);
		cout << "\" in \"" << dtsent << "\" -> " << toccur << '\n';
		delete[] toccur;
	}
	delete[] dt;

	char* dts1 = new char[4] {'d', 'a', 'y', 's'};
        char* dts2 = new char[3] {'d', 'a', 'y'};
        int dtres = strcmp(dts1, dts2, 4);
	if (dtres > 0)
        	cout << "s1 is lexicographically after s2\n";
        else if (dtres == 0)
        	cout << "s1 is lexicographically equals to s2\n";
        else
        	cout << "s1 is lexicographically before s2\n";

	delete[] dts1;
	delete[] dts2;
}
