#include <iostream>
#include <string>
using namespace std;

int main() {
    string str = "abcdef";
    
    cout << str.erase(0, 1) << endl; // 输出 "bcdef"
    cout << str.erase(2) << endl; // 输出 "bc"
    cout << str.erase() << endl; // 输出空字符串 ""
    
    return 0;
}