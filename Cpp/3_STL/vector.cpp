#include <iostream>
#include <vector>
using namespace std;

template<typename T>
void print_vec(vector<T> &);

int main() {
	vector<int> a;
	vector<double> b(3);
	vector<int> c(5, 6);
	vector<int>::iterator iter_b, iter_e;
	print_vec(b);
	print_vec(c);
// 1. The func that common.
	for (int i = 0; i < 10; ++i)
		a.push_back(i);
	print_vec(a);

	int val1 = a.front();
	int val2 = a.back();
	iter_b = a.begin();
	iter_e = a.begin() + 3;
	a.erase(iter_b, iter_e);
	print_vec(a);
	iter_b = a.begin();
	a.erase(iter_b);
	print_vec(a);
	a.pop_back();
	print_vec(a);
	


	return 0;
}

template<typename T>
void print_vec(vector<T> &v) {
	typename vector<T>::iterator i; // Don't need to write "typename" in VS.
	for (i = v.begin(); i != v.end(); ++i)
		cout << *i << " ";
	cout << endl;
}
