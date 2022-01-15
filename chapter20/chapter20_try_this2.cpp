/*
	Chapter 20, try this

	19.09.2018 23:31
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

	double* jack_data = new double[size];
	for (int i=min, j=0; i<max; ++i, ++j)
		jack_data[j] = i;
	random_shuffle(jack_data, jack_data+size);

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

	double* jill_high = high(&v[0], &v[0]);		//test for error

	if (jill_high)
		cout << "Jill's max: " << *jill_high << '\n';
	if (jack_high)
		cout << "\nJack's max: " << *jack_high << '\n';

}
catch (exception& e) {
	cerr << "exception: " << e.what() << '\n';
}
catch (...) {
	cerr << "exception\n";
}
