#include <iostream>
#include <string>
using namespace std;

int main() {
    string str = "abcabc";
    string str1 = "abc";
    
    cout << str.find(str1) << endl; // 输出 0
    cout << str.find(str1, 1) << endl; // 输出 3
    
    return 0;
}