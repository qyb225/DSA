#include <iostream>
#include <string>
using namespace std;

int main() {
    string str = "abcdef";
    string str1 = "QYBB";
    
    cout << str.insert(1, str1) << endl; 
    // 输出 "aQYBBbcdef"
    cout << str.insert(5, str1, 0, 3) << endl;
    // 输出 "aQYBBQYBbcdef"
    
    return 0;
}