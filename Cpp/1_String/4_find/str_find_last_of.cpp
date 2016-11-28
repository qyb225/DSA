#include <iostream>
#include <string>
using namespace std;

int main() {
    string str = "hello world!";
    string str1 = "abcde";
    
    cout << str.find_last_of(str1) << endl; // 输出 10
    cout << str.find_last_not_of(str1) << endl; // 输出 11
    
    return 0;
}