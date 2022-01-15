/*
	Chapter 20,
	ex6
	06.10.2018 23:11 - 08.10.2018 20:03
	ex8, 9
	12.10.2018 16:34
	ex10
	13.10.2018 14:28
*/
#include "std_lib_facilities.h"
#include "Document.cpp"

template<typename Iter>
void print(Iter first, Iter last)
{
	for (Text_iterator p = first; p!=last; ++p) {
		cout << *p;
	}
}

Text_iterator find_replace(Text_iterator first, Text_iterator last, const string& targ, const string& repl)
	//change first occurence of targ(et) in (first; last] sequence to repl(acement)
{
	auto p = find_txt(first, last, targ);
	if (p == last) return p;
	Line& l = p.get_line();

	auto p_end = p;
	for(int i=0; i<targ.size(); ++i)
		++p_end;

	auto it = l.erase(p.get_line_pos_it(), p_end.get_line_pos_it());
	l.insert(it, repl.begin(), repl.end());
}

int main()
try
{
	Document doc;

	string delim;
	cout << "Set some delimiter characters for words counting function: ";
	for (char ch; cin.get(ch); )
		delim.push_back(ch);

	cout << "Document contain " << doc.get_char_num(doc.begin(), doc.end()) << " characters.\n";
	cout << "Document contain " << doc.get_words_num_space(doc.begin(), doc.end()) << " words separated by whitespace.\n";
	cout << "Document contain " << doc.get_words_num_alpha(doc.begin(), doc.end())
		<< " words separated by non-alphabetic characters.\n";
	cout << "Document contain " << doc.get_words_num_custom(doc.begin(), doc.end(), delim)
		<< " words separated by following characters: ";
	for (auto c : delim) {
		if (c=='\n') cout << "\\n ";
		else cout << c << ' ';
	}
	cout << '\n';


	cout << "\t\tEnter some text here:\n";
	if (!cin) cin.clear();
	while (cin) {
		cout << "# ";
		cin >> doc;
	}

	string s;
	cout << "\t\tEnter text for find here:\n# ";
	if (!cin) cin.clear();
	cin >> s;
	auto p = find_txt(doc.begin(), doc.end(), s);
	if (p != doc.end()) {
		cout << "\t\tFound text:\n";
		print(p, doc.end());
		cout << endl;
	}

	string source;
	string target;
	cout << "Enter replaceable text here: ";
	cin >> source;
	cout << "Enter text for replacement here: ";
	cin >> target;
	auto pp = find_replace(doc.begin(), doc.end(), source, target);
	if (pp == doc.end()) cout << "Nothing wasn't replaced\n";

	cout << "\t\tYour document:\n";
	cout << doc;
	cout << "Document contain " << doc.get_char_num(doc.begin(), doc.end()) << " characters.\n";
	cout << "Document contain " << doc.get_words_num_space(doc.begin(), doc.end()) << " words separated by whitespace.\n";
	cout << "Document contain " << doc.get_words_num_alpha(doc.begin(), doc.end())
		<< " words separated by non-alphabetic characters.\n";
	cout << "Document contain " << doc.get_words_num_custom(doc.begin(), doc.end(), delim)
		<< " words separated by following characters: ";
	for (auto c : delim) {
		if (c=='\n') cout << "\\n ";
		else cout << c << ' ';
	}
	cout << '\n';

}
catch (exception& e) {
	cerr << "exception: " << e.what() << '\n';
}
catch (...) {
	cerr << "exception\n";
}
