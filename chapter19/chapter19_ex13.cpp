/*
	Chapter 19, exercise 13

	14.09.2018 16:00
*/

#include "std_lib_facilities.h"

//contain some mess of object's type designations(when print obj's type) because of copy ctor and operator=

class Tracer {
public:
	Tracer(const string& s = "not define") : msg{s} { cout << "ctor() of " << msg << '\n'; }
	Tracer(const Tracer& t) : msg{t.msg} { cout << "copy ctor() of " << msg << '\n'; }
	Tracer& operator=(const Tracer& t)
	{
		cout << "operator= of " << msg << '\n';	
		msg = t.msg;
	}
	~Tracer() { cout << "~dtor of " << msg << '\n'; }

private:
	string msg;
};

struct Explore {
	int n;
	double d;
	Tracer t{"member obj"};
};

void local()
{
	Tracer t{"local obj"};
	Tracer c = t;
	t = c;
	Tracer d;
	d = c = t;
}

void member()
{
	Explore e;
	Explore* pe = new Explore[10];
	delete[] pe;
}

void heap()
{
	Tracer* tp = new Tracer{"heap obj"};
	Tracer* p = tp;
	Tracer t = *p;	//ctor of local obj
	delete tp;
}

Tracer st{"static obj"};
Tracer ta[4];

Tracer t_cpy(Tracer t)
{
	Tracer tc = t;	//maybe optimize by compiler
	return tc;
}

int main()
try
{
	for (int i=0; i<4; ++i)
		ta[i] = st;
	local();
	member();
	heap();
	Tracer t = t_cpy(Tracer{"temp local obj"});
}
catch (exception& e) {
	cerr << "exception: " << e.what() << '\n';
}
catch (...) {
	cerr << "exception\n";
}
