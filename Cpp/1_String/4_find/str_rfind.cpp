#include <iostream>
#include <string>
using namespace std;

int main() {
    string str = "abcabc";
    string str1 = "abc";
    
    cout << str.rfind(str1) << endl; // 输出 3
    cout << str.rfind(str1, 2) << endl; // 输出 0
    
    return 0;
}