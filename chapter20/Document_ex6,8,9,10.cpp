//for chapter20_ex6.cpp
#include <iostream>

template<typename Iter>
bool match(Iter first, Iter last, const string& s)
{
	for (int i = 0; i<s.size(); ++i) {
		if (first==last || s[i] != *first) return false;
		++first;
	}
	return true;
}

using namespace std;

using Line = vector<char>;

class Text_iterator {
public:
	Text_iterator(list<Line>::iterator ll, Line::iterator pp)
		:ln{ll}, pos{pp} { }

	char& operator*() { return *pos; }
	Text_iterator& operator++();

	list<Line>::iterator get_list_it() const { return ln; }
	Line::iterator get_line_pos_it() const { return pos; }
	Line& get_line() const { return *ln; }

	void* get_pos_addr() const { return &(*pos); }	//debug info

	bool operator==(const Text_iterator& other) const
	{ return ln == other.ln && pos == other.pos; }
	bool operator!=(const Text_iterator& other) const
	{ return !(*this == other); }

private:
	list<Line>::iterator ln;	//line number
	Line::iterator pos;		//character position in line
};

Text_iterator& Text_iterator::operator++()
{
	++pos;
	if (pos == (*ln).end()) {
		++ln;
		pos = (*ln).begin();	//bad if ln == line.end()
	}
	return *this;
}

ostream& operator<<(ostream& os, Text_iterator& it)
{
	os << it.get_pos_addr();
	return os;
}

//namespace std {
template<> struct std::iterator_traits<Text_iterator> {
	typedef ptrdiff_t			difference_type;
	typedef char 				value_type;
	typedef char*				pointer;
	typedef char&				reference;
	typedef bidirectional_iterator_tag	iterator_category;
};
//};

struct Document {
	list<Line> line;
	Document() { line.push_back(Line{}); }	//empty line in empty Document
						//because member function back() doesn't support empty containers
	Text_iterator begin()
	{ return Text_iterator{line.begin(), (*line.begin()).begin()}; }

	Text_iterator end()
	{
		auto last = line.end();
		--last;
		return Text_iterator{last, (*last).end()};
	}

	int get_char_num(Text_iterator first, Text_iterator last) const; //doesn't count '\n'-newline characters

	//counts number of words in text
	int get_words_num_space(Text_iterator first, Text_iterator last) const; //return number of words separated by whitespace and newlines
	int get_words_num_alpha(Text_iterator first, Text_iterator last) const; //return number of words separated by non-alphabetic symbols
	int get_words_num_custom(Text_iterator first, Text_iterator last, const string& delim) const; //return number of words separated by symbols from delim
};

int Document::get_char_num(Text_iterator first, Text_iterator last) const //doesn't count '\n' - newline characters
{
	int count = 0;
	while (first!= last) {
		if (*first != '\n') ++count;
		++first;
	}
	return count;
}

template<typename Iter>
Iter skip_to_char(Iter first, Iter last)
{
	char space = ' ';
	char new_line = '\n';
	for (Iter p = first; p!=last; ++p)
		if (*p!=space && *p!=new_line) return p;
	return last;
}

template<typename Iter>
Iter skip_to_space(Iter first, Iter last)
{
	char space = ' ';
	char new_line = '\n';
	for (Iter p = first; p!=last; ++p)
		if (*p==space || *p==new_line) return p;
	return last;
}

int Document::get_words_num_space(Text_iterator first, Text_iterator last) const
{
	int count = 0;
	while (first!=last) {	
		first = skip_to_char(first, last);
		if (first!=last) ++count;
		first = skip_to_space(first, last);
	}
	return count;
}

template<typename Iter>
Iter skip_to_alpha(Iter first, Iter last)
{
	for (Iter p = first; p!=last; ++p)
		if (isalpha(*p)) return p;
	return last;
}

template<typename Iter>
Iter skip_to_non_alpha(Iter first, Iter last)
{
	for (Iter p = first; p!=last; ++p)
		if (!isalpha(*p)) return p;
	return last;
}

int Document::get_words_num_alpha(Text_iterator first, Text_iterator last) const
{
	int count = 0;
	while (first!=last) {
		first = skip_to_alpha(first, last);
		if (first!=last) ++count;
		first = skip_to_non_alpha(first, last);
	}
	return count;
}

template<typename Iter, typename It>
bool is_in_range(Iter first, Iter last, const It c) //return true if [first, last) range contain c (third arg)
{
	for (auto p = first; p!=last; ++p)
		if (*p==*c) return true;
	return false;
}

int Document::get_words_num_custom(Text_iterator first, Text_iterator last, const string& delim) const
{
	bool word = false;
	int count = 0;
	auto it_begin = delim.begin();
	auto it_end = delim.end();

	for (auto p = first; p!=last; ++p) {
		if (!word && !is_in_range(it_begin, it_end, p.get_line_pos_it())) {
			word = true;
			++count;
		}
		else if (word && is_in_range(it_begin, it_end, p.get_line_pos_it()))
			word = false;
	}
	return count;
}

istream& operator>>(istream& is, Document& doc)
{
	for (char ch; is.get(ch); ) {
		doc.line.back().push_back(ch);
		if (ch == '\n') doc.line.push_back(Line{});
	}
	if (doc.line.back().size()) doc.line.push_back(Line{});
	return is;
}

ostream& operator<<(ostream& os, Document& doc)
{
	for (auto ch : doc) os << ch;
	return os;
}

Text_iterator find_txt(Text_iterator first, Text_iterator last, const string& s)
{
	if (s.size()==0) return last;
	char first_char = s[0];
	while (true) {
		auto p = find(first, last, first_char);
		if (p==last || match(p, last, s)) return p;
		first = ++p;
	}
}
