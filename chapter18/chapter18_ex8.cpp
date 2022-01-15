/*
Chapter 18, exercise 8

	14.07.2018 15:47 - 19.07.2018 15:34

*/

#include "std_lib_facilities.h"

string backwrd_cpy(const string& s)
{
	string sc {};
	for (int i = 0; i < s.size(); ++i) {
		sc.push_back(s[s.size()-i-1]);
	}
	return sc;
}

bool is_palindrome(const string& s)
{
	return (s == backwrd_cpy(s));
}

void test1()
{
	cout << "test1()\n";
	for (string s; cin >> s && s != "|"; ) {
		cout << s << " is";
		if (!is_palindrome(s)) cout << " not";
		cout << " a palindrome\n";
	}
}

char* backwrd_cpy(const char s[], int n)
{
	int i = 0;
	const char* ps = s;
	while(ps[i]) ++i;
	
	if(i > n) i = n;
	
	char* p = new char[i+1];	//+1 for '\0'

	for (int i = 0; i < n; ++i)
		p[i] = s[n-i-1];

	p[n] = '\0';
	return p;
}

bool is_palindrome(const char s[], int n)
{
	char* str = backwrd_cpy(s, n);
	for (int i = 0; i < n; ++i)
		if (s[i] != str[i]) {
			delete[] str;
			return false;
		}
	delete[] str;
	return true;
}

istream& read_word(istream& is, char* buffer, int max)
{
	is.width(max);
	is >> buffer;
	return is;
}

void test2()
{
	cout << "test2()\n";
	constexpr int max = 128;
	for (char s[max]; read_word(cin, s, max) && *s != '|'; ) {
		cout << s << " is";
		if(!is_palindrome(s, strlen(s))) cout << " not";
		cout << " a palindrome\n";
	}
}

char* backwrd_cpy(const char* first, const char* last)
//last already point to last_character +1
{
	int n = 0;
	while (&first[n] < last) ++n;

	char* p = new char[n+1];	//+1 for '\0'

	for (int i = 0; &first[i] < last; ++i)
		p[i] = last[-i-1];
	
	p[n] = '\0';
	return p;
}

bool is_palindrome(const char* first, const char* last)
{
	++last;		//make last point to last_character +1	//but maybe (first <= last) now worse
	
	char* p = backwrd_cpy(first, last);
	
	for (int i = 0; &first[i] < last; ++i)
		if ( p[i] != first[i]) {
			delete[] p;
			return false;
		}
	delete[] p;
	return true;
}

void test3()
{
	cout << "test3()\n";
	const int max = 128;
	for (char s[max]; read_word(cin, s, max) && *s != '|'; ) {
		cout << s << " is";
		if (!is_palindrome(&s[0], &s[strlen(s)-1]))
			cout << " not";
		cout << " a palindrome\n";
	}

}

int main()
{
	test1();
	test2();
	test3();
}
