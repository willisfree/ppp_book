/*
	Chapter 19, exercise 12

	14.09.2018 12:47
*/

#include "std_lib_facilities.h"

class File_handle {
public:
	File_handle(const string& filename)
	{
		fs.open(filename);
		if (!fs) error("file wasn't opened: ", filename);
		else cout << "file was opened.\n"; 
	}
	~File_handle() { fs.close(); cout << "file was closed.\n"; }
	fstream& get() { return fs; }

private:
	fstream fs;
};

int main()
try
{
	File_handle fl{"te_c.cpp"};
	File_handle fo{"out.txt"};

	string ss{"future"};
	fo.get() << ss;		//write ss into fo

	string s;
	for (fstream& fs = fl.get(); fs >> s; )
		cout << s << '\n';	//print all fl content

	fl.get().clear();		//clear fl.eof() or others state
	fl.get().seekp(0);		//go to the top of the file	
	fl.get() << ss;			//write ss into fl

}
catch (exception& e) {
	cerr << "exception: " << e.what() << '\n';
}
catch (...) {
	cerr << "exception\n";
}
