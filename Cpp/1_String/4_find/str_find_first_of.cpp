#include <iostream>
#include <string>
using namespace std;

int main() {
    string str = "hello world!";
    string str1 = "abcde";
    
    cout << str.find_first_of(str1) << endl; // 输出 1
    cout << str.find_first_not_of(str1) << endl; // 输出 0
    
    return 0;
}