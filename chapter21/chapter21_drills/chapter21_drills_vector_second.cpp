/*
	Chapter 21, drills with map

	19.11.2018 19:42 - 21:10
*/

#include "std_lib_facilities.h"

template<typename C>
void print(const C& c)
{
	for (const auto& v : c) cout << v << '\n';
}

template<typename In, typename In2, typename T>
T difference_sum(In first, In last, In2 first2, T init)
{
	while (first!=last) {
		init = init + *first - *first2;
		++first;
		++first2;
	}
	return init;
}

int main()
try
{
	//1
	ifstream ifs{"double_values.txt"};
	istream_iterator<double> ii{ifs};
	istream_iterator<double> eos;		//end of stream

	vector<double> vd{ii, eos};

	//2
	cout << "\t***vector<double>***\n";
	print(vd);

	//3
	vector<int> vi(vd.size());
	copy(vd.begin(), vd.end(), vi.begin());

	//4
	cout << "\t***vector<double> and vector<int>***\n";
	for (size_t i=0; i<vd.size(); ++i)
		cout << vd[i] << '\t' << vi[i] << '\n';

	//5
	double d_sum = accumulate(vd.begin(), vd.end(), 0.0);
	cout << "\nsum of all elements of vector<double>: " << d_sum << '\n';

	//6
	int i_sum = accumulate(vi.begin(), vi.end(), 0);
	cout << "difference sum of d_sum and i_sum: " << d_sum - i_sum << '\n';
	cout << "difference sum of d_sum and i_sum: "
		<< difference_sum(vd.begin(), vd.end(), vi.begin(), 0.0) << '\n';

	//7
	reverse(vd.begin(), vd.end());
	cout << "\n\t***vector<double> after reverse()***\n";
	print(vd);

	//8
	double vd_average = d_sum/vd.size();
	cout << "\naverage value of all elements of vector<double>: " << vd_average << '\n';

	//9
	vector<double> vd2(vd.size());
	copy_if(vd.begin(), vd.end(), vd2.begin(), [&](double d) { return d < vd_average; });
	cout << "\t***vector<double> vd2***\n";
	print(vd2);

	//10
	sort(vd.begin(), vd.end());
	cout << "\t***vector<double> after sort***\n";
	print(vd);

}
catch (exception& e) {
	cerr << "exception: " << e.what() << '\n';
}
catch (...) {
	cerr << "exception\n";
}
