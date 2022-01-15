/*
	Chapter 18, exercise 10

	21.07.2018 13:20

*/

#include "std_lib_facilities.h"

bool is_palindrome(const char s[], int n)
{
	int first = 0;
	int last = n-1;
	while (first < last) {
		if (s[first] != s[last]) return false;
		++first;
		--last;
	}
	return true;
}

void test1()
{
	constexpr int max = 10;
	for (char s[max]; cin.getline(s, 100000); ) {
		if (strlen(s) > max) error("string too long\n");
		
		cout << s << " is";
		if (!is_palindrome(s, strlen(s))) cout << " not";
		cout << " a palindrome\n";
	}

}

void test2()
{
	for (string s; getline(cin, s); ) {	
		cout << s << " is";
		if (!is_palindrome(s.c_str(), s.size())) cout << " not";
		cout << " a palindrome\n";
	}

}

int main()
try
{
//	test1();
	test2();
}
catch (exception& e) {
	cerr << "exception: " << e.what() << '\n';
}
catch (...) {
	cerr << "exception\n";
}
