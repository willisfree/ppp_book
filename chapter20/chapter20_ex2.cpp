/*
	Chapter 20, ex2

	01.10.2018 21:29
*/

#include "std_lib_facilities.h"

double* high(double* first, double* last)
//return a pointer to the element  in [first; last) that has the highest value
//return nullptr if nothing found;
{
	if (first == nullptr || last == nullptr) error("double* high(double*, double*) get nullptr as an argument.");
	double h = numeric_limits<double>::lowest();
	double* high = nullptr;
	for (double* p = first; p!=last; ++p)
		if (h < *p) { high = p; h = *p; }
	return high;
}

int main()
try
{
	srand(time(0));	
	int max = -4;
	int min = -20;
	unsigned size = max-min;


	fstream fs {"data_jill.txt"};
	for (int i=min; i<max; ++i)
		fs << i;

	fstream fs_s {"data_jack.txt"};
	for (int i=min; i<max; ++i)
		fs_s << rand() % max;
	fs_s.seekg(0);
	for (int i; fs_s >> i;)
		cout << i << '\n';

	double* jack_data = new double[size];
	for (int i=0; fs_s; ++i)
		fs_s >> jack_data[i];

	vector<double>* jill_data = new vector<double>;
	for (int i=min; i<max; ++i)
		jill_data->push_back(i);

	vector<double>& v = *jill_data;
	random_shuffle(&v[0], &v[0]+v.size());

	//check
	for (int i=0; i<size; ++i)
		cout << setw(2) << jack_data[i] << ' ';
	cout << endl;
	
	for (double s : v)
		cout << setw(2) << s << ' ';
	cout << endl;


	double* jack_high = high(jack_data, jack_data+size);

	double* jill_high = high(&v[0], &v[0]+v.size());

	if (jill_high)
		cout << "Jill's max: " << *jill_high << '\n';
	if (jack_high)
		cout << "Jack's max: " << *jack_high << '\n';

}
catch (exception& e) {
	cerr << "exception: " << e.what() << '\n';
}
catch (...) {
	cerr << "exception\n";
}
