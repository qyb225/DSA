#include <iostream>
#include <list>

using namespace std;

template<class T>
bool my_cmp(const T & s1, const T & s2);
template<class T>
void print_list(list<T> & l);

template<class T>
class my_less {
public:
	bool operator()(const T &s1, const T &s2);
};

int main() {
    list<int> lst1, lst2;
    list<int>::iterator i;
    lst1.push_back(1);
    lst1.push_back(2);
    lst1.push_back(1);
    lst1.push_back(2);
    lst2.push_back(20);
    lst2.push_back(10);
    lst2.push_back(30);
    lst1.unique();
    print_list(lst1);
    lst1.sort();
    i = lst1.begin();
    ++i;
    lst1.splice(i, lst2, lst2.begin(), lst2.end());
    lst1.push_front(0);
    lst1.sort(my_less<int>()); //!!!!
    print_list(lst1);
    lst1.sort(my_cmp<int>);
    print_list(lst1);
    lst1.erase(lst1.begin());
    print_list(lst1);
    lst1.remove(1);
    print_list(lst1);
  
    return 0;
}

template<class T>
bool my_cmp(const T & s1, const T & s2) {
    return s2 < s1;
}
template<class T> //!!!!
bool my_less<T>::operator()(const T &s1, const T &s2) {
	return s1 % 10 < s2 % 10;
}
template<class T>
void print_list(list<T> & l) {
	typename list<T>::iterator i;
	for (i = l.begin(); i != l.end(); ++i)
		cout << *i << " ";
	cout << endl;
}