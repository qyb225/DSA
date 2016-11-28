#include <iostream>
#include <string>
using namespace std;

int main() {
    string str = "abcdef";
    
    cout << str.replace(0, 2, "haha") << endl; // 输出 "hahcdef"
    cout << str.replace(0, 4, "haha", 1, 2) << endl; // 输出 "ahcdef"
    
    return 0;
}