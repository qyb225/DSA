#include <iostream>
#include <deque>
using namespace std;

template<class T>
void myPrint(T &);

int main() {
    deque<int> a;
    deque<int>::iterator j, k;
    for (int i = 0; i < 10; ++i)
        a.push_back(i + 1);
    a.push_front(0);
    myPrint(a);
    a.erase(a.begin());
    myPrint(a);
    j = a.begin() + 1;
    k = a.end() - 3;
    a.erase(j, k);
    myPrint(a);

    return 0;
}

template<class T>
void myPrint(T& a) {
    typename T::iterator i;
    for (i = a.begin(); i != a.end(); ++i)
        cout << *i << " ";
    cout << endl;
}