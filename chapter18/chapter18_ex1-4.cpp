/* Chapter 18, exercises 1-4

	10.07.2018 
	ex1 13:01
	ex2 14:00

	11.07.2018
	ex3 12:52
	ex4 13:33
*/

#include "std_lib_facilities.h"

int strcmp(const char* s1, const char* s2)
{
	if (s1 == nullptr)
		cerr << "strcmp() get s1 with nullptr!\n";
		//throw exception

	if (s2 == nullptr)
		cerr << "strcmp() get s2 with nullptr!\n";
		//throw exception

	for (s1, s2; *s1; ++s1, ++s2)
		if (*s1 == *s2)
			strcmp(s1, s2);		//will be call after iteration
		else if (*s1 > *s2)
			return 1;	//s2 before s1
		else
			return -1;	//s1 before s2

	//s1 doesn't contain any characters now
	if (!*s2)	//s2 doen't contain any characters
		return 0;	//s1 equal s2
	else
		return -1;	//s1 before s2
}

char* strdup(const char* c_str)
{
	char* p = new char;
	char* pp = p;	//pointer to the first element of p
	while(*c_str) {
		*p = *c_str;
//		cerr << "*p = " << *p << '\n';
		++p;
		++c_str;
	}
	return pp;
}

bool is_cong(const char* s, const char* x, char** p)
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
	for (s, x; *x; ++s, ++x) {
			if(*s != *x) {
				*p = nullptr;
				return false;
			}
	}
	return true;
}

char* findx(const char* s, const char* x)
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
	while(*s) {
		if(*s == *x)
			if(is_cong(s, x, &p))
			return p;
	++s;

	/*		constexpr char* px = x;
			const char* ps = s;
			for (px, ps; *px; ++px, ++ps) {
			p = strdup(s);	//copy all characters from the first occurrence of the x to the end of s
//			cerr << p << '\n';
			if(*px != *ps) {
				p = nullptr;
				break;
			}
		}
	*/
	}
	return nullptr;	//just in case
}

int main()
{
	char cstr[] = "Hello!";
	char* pc = strdup(cstr);
	cout << "*pc = " << pc << '\n';
	delete[] pc;

	char sent[] = "Happy birthday, Garry!";
	char word[] = "day";
	char* occu = findx(sent, word);
	if (occu == nullptr)
		cerr << "nothing found\n";
	else {
		cout << "First occurrence of \"" << word << "\" in \"" << sent << "\" -> " << occu << '\n';
		delete[] occu;
	}
	char s1[] = "day";
	char s2[] = "days";
	int res = strcmp(s1, s2);
	if (res > 0)
		cout << "s1 is lexicographically after s2\n";
	else if (res == 0)
		cout << "s1 is lexicographically equals to s2\n";
	else
		cout << "s1 is lexicographically before s2\n";
	
	char t[] = {'i', 'n', 'd', 'y'};
	char* tc = strdup(t);
	cout << "*tc = " << tc << '\n';
	delete[] tc;
	char tsent[] = "indy developer.";
	char* toccu = findx(tsent, t);
	if (toccu == nullptr)
		cerr << "nothing found\n";
	else {
		cout << "First occurrence of \"" << t << "\" in \"" << tsent << "\" -> " << toccu << '\n';
		delete[] toccu;
	}
	char ts1[] = {'d', 'a', 'y', 's'};
        char ts2[] = {'d', 'a', 'y'};
        int tres = strcmp(ts1, ts2);
	if (tres > 0)
        	cout << "s1 is lexicographically after s2\n";
        else if (tres == 0)
        	cout << "s1 is lexicographically equals to s2\n";
        else
        	cout << "s1 is lexicographically before s2\n";



	char* dt = new char[4] {'i', 'n', 'd', 'y'};	//temp c_str in dynamic memory
	char* dtc = strdup(dt);
	cout << "*dtc = " << dtc << '\n';
	delete[] dtc;
	char dtsent[] = "indy developer.";
	char* toccur = findx(dtsent, dt);
	if (toccu == nullptr)
		cerr << "nothing found\n";
	else {
		cout << "First occurrence of \"" << dt << "\" in \"" << dtsent << "\" -> " << toccur << '\n';
		delete[] toccur;
	}
	delete[] dt;

	char* dts1 = new char[4] {'d', 'a', 'y', 's'};
        char* dts2 = new char[3] {'d', 'a', 'y'};
        int dtres = strcmp(dts1, dts2);
	if (dtres > 0)
        	cout << "s1 is lexicographically after s2\n";
        else if (dtres == 0)
        	cout << "s1 is lexicographically equals to s2\n";
        else
        	cout << "s1 is lexicographically before s2\n";
	delete[] dts1;
	delete[] dts2;
}
