#include <iostream>
#include <set>
using namespace std;

template<class T>
class myLess {
public:
    bool operator()(const T &, const T &);
};
template<class Iter>
void print_multiset(Iter, Iter);

template<class T>
void myPrint(T &);

int main() {
    typedef multiset<int, myLess<int> > MSET1;
    typedef multiset<int> MSET2;
    // MSET1, MSET2 is different.
    MSET1 a;
    MSET2 b;
    MSET1::iterator it;
    for (int i = 0; i < 10; ++i) {
        a.insert(i + 1);
        b.insert(i + 1);
    }
    // Can repeatly.
    a.insert(3);
    b.insert(5);

    cout << "a: ";
    print_multiset(a.begin(), a.end());
    cout << "b: ";
    print_multiset(b.begin(), b.end());

    a.erase(3); // Delete all '3' in multiset.
    myPrint(a);

    cout << b.count(5) << endl;

    pair<MSET1::iterator, MSET1::iterator> p = a.equal_range(6); // creating type "pair";

    cout << *(p.first) << " " << *(p.second) << endl;
    it = a.lower_bound(6);
    cout << "lower: " << *it << endl;
    it = a.upper_bound(6);
    cout << "upper: " << *it << endl;
    a.erase(a.lower_bound(6), a.find(1)); // Delete [first, last), a.find(1) won't be deleted;
    myPrint(a);

    return 0;
}

template<class T>
bool myLess<T>::operator()(const T& s1, const T& s2) {
    return s1 > s2;
}

template<class Iter>
void print_multiset(Iter i, Iter j) {
    for (; i != j; ++i)
        cout << *i << " ";
    cout << endl;
}

template<class T>
void myPrint(T& a) {
    typename T::iterator i;
    for (i = a.begin(); i != a.end(); ++i)
        cout << *i << " ";
    cout << endl;
}