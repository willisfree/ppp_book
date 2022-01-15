/*
	Chapter 20,
	ex2 01.10.2018 21:29
	ex3 05.10.2018 22:30
*/

#include "std_lib_facilities.h"

double* high(double* first, double* last)
//return a pointer to the element  in [first; last) that has the highest value (if sequence have some such elements return pointer to last)
//return nullptr if nothing found;
{
	if (first == nullptr || last == nullptr) error("double* high(double*, double*) get nullptr as an argument.");
	double h = numeric_limits<double>::lowest();
	double* high = nullptr;
	for (double* p = first; p!=last; ++p)
		if (h <= *p) { high = p; h = *p; }
	return high;
}

double* center_high(double* first, double* last)
//return a pointer to the element  in [first; last) that has the highest value (if sequence have some such elements return pointer to last)
//return nullptr if nothing found;
{
	--last;		//point to the last elem now
	double h = *first;
	double* high = nullptr;
	while (first < last) {
		double* d = (*first<*last)?last:first; 
		if (h <= *d) { h = *d; high = d; }
		++first;
		--last;
	}
	if (first==last && *first > h) high = first; 	//if count of elements in sequence isn't even
	return high;
}

int main()
try
{
	srand(time(0));	
	int max = -3;
	int min = -20;
	int size = max-min;
	if (size<0) error("max var must contain bigger value than min");
	int range = max-min;
	int w = 3; //width

//get data
	fstream fs {"data_jill.txt", fstream::in | fstream::out | fstream::trunc}; //truncate all the file content while opening
	if (!fs) error("error while openning fs");
	for (int i=min; i<max; ++i)
		fs << rand()%range + min << ' ';
	fs.seekg(0);

	fstream fs_s {"data_jack.txt", fstream::in | fstream::out | fstream::trunc};
	if (!fs_s) error("error while openning fs_s");
	for (int i=min; i<max; ++i) {
		fs_s <<  rand()%range + min << ' ';
	}
	fs_s.seekg(0);

//read data
	double* jack_data = new double[size];
	for (int i=0; fs_s && i < size; ++i)
		fs_s >> jack_data[i];

	vector<double>* jill_data = new vector<double>;
	vector<double>& v = *jill_data;
	for (double i=0; fs >> i; )
		jill_data->push_back(i);
//check
	for (int i=0; i<size; ++i)
		cout << setw(w) << jack_data[i] << ' ';
	cout << endl;
	
	for (double s : v)
		cout << setw(w) << s << ' ';
	cout << endl;
//high	
	double* jack_high = center_high(jack_data, jack_data+size);

	double* jill_high = center_high(&v[0], &v[0]+v.size());

	if (jill_high)
		cout << "Jill's max: " << *jill_high << '\n';
	if (jack_high)
		cout << "Jack's max: " << *jack_high << '\n';
	
	double* jack = high(jack_data, jack_data+size);

	double* jill = high(&v[0], &v[0]+v.size());

	if (jill)
		cout << "Jill's max: " << *jill << '\n';
	if (jack)
		cout << "Jack's max: " << *jack << '\n';

	
	delete[] jack_data;
	delete jill_data;
}
catch (exception& e) {
	cerr << "exception: " << e.what() << '\n';
}
catch (...) {
	cerr << "exception\n";
}
