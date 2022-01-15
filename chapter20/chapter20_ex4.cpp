/*
	Chapter 20, ex4

	06.10.2018 16:30
*/

#include "std_lib_facilities.h"

template<typename Iter>
Iter high(Iter first, Iter last)
{
	Iter high = first;
	for (Iter p = first; p!=last; ++p)
		if (*high < *p) high = p;
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
//	for (int i=min; i<max; ++i)
//		jill_data->push_back(i);

	vector<double>& v = *jill_data;
//	random_shuffle(&v[0], &v[0]+v.size());

	//check
	for (int i=0; i<size; ++i)
		cout << setw(2) << jack_data[i] << ' ';
	cout << endl;
	
	for (double s : v)
		cout << setw(2) << s << ' ';
	cout << endl;


	auto jack_high = high(jack_data, jack_data+size);
	auto jill_high = high(v.begin(), v.end());		//test for error

	if (jill_high != v.end())
		cout << "Jill's max: " << *jill_high << '\n';
	if (jack_high != jack_data+size)
		cout << "Jack's max: " << *jack_high << '\n';

}
catch (exception& e) {
	cerr << "exception: " << e.what() << '\n';
}
catch (...) {
	cerr << "exception\n";
}
