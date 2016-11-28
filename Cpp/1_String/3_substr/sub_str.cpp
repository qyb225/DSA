#include <iostream>
#include <string>
using namespace std;

int main() {
    string str = "abcdef";
    
    cout << str.substr(2,2) << endl; // 输出 "cd"
    cout << str.substr(2) << endl; // 输出 "cdef"
    
    return 0;
}