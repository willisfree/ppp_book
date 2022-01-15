/*
 Chapter 18, exercises 1-5
 
 	14.07.2018 13:54
*/

#include "std_lib_facilities.h"

string cat_dot(const string& s1, const string& s2)
{
	char spr = '.';		//separator
	return s1 + spr + s2;
}

string cat_dot_mod(const string& s1, const string& s2, const string& spr)
{
	return s1 + spr + s2;
}

void ex5()
{
	string s1 = "Niels";
	string s2 = "Bohr";
	string sc = cat_dot(s1, s2);
	cout << sc << '\n';
}

void ex6()
{
	string s1 = "Niels";
	string s2 = "Bohr";
	string sep = "_";
	string sc = cat_dot_mod(s1, s2, sep);
	cout << sc << '\n';
}

char* cat_dot_cstr(const char* s1, const char* s2)
{
	char spr = '.';		//separator
	char* p = new char;
	char* pp = p;
	for (s1; *s1; ++s1) {
		*p = *s1;
		++p;
	}

	*p = spr;
	++p;

	for (s2; *s2; ++s2) {
		*p = *s2;
		++p;
	}
	return pp;
}

char* cat_dot_cstr_mod(const char* s1, const char* s2, const char* spr)
{
	char* p = new char;
	char* pp = p;
	for (s1; *s1; ++s1) {
		*p = *s1;
		++p;
	}

	for (spr; *spr; ++spr) {
		*p = *spr;
		++p;
	}

	for (s2; *s2; ++s2) {
		*p = *s2;
		++p;
	}
	return pp;
}

void ex7_1()
{
	char s1[] = "Niels";
	char s2[] = "Bohr";
	char* sc = cat_dot_cstr(s1, s2);
	cout << sc << '\n';
	delete[] sc;
}

void ex7_2()
{
	char s1[] = "Niels";
	char s2[] = "Bohr";
	char sep[] = " Henrik David ";
	char* sc = cat_dot_cstr_mod(s1, s2, sep);
	cout << sc << '\n';
	delete[] sc;
}


int main()
{
	ex5();
	ex6();
	ex7_1();
	ex7_2();
}
