#include <iostream>
#include "my_vector.h"
#include "my_vector.cpp"
using namespace std;

int main() {
    int a[20] = {1, 1, 2, 2, 2, 3, 8 ,4, 5, 5 ,6, 8, 8, 8, 9, 237, 9, 9, 10, 1};
    my_vector<int> vec1(a, 0, 20);
    vec1.show();
    vec1.sort();
    vec1.show();
    cout << vec1.search(3) << endl;
    return 0;
}
