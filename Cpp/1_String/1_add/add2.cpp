# include <iostream>
# include <string>
using namespace std;

int main() {
    string str1 = "abc", str2 = "def";
    
    cout << str1.append(str2) << endl; // 输出 "abcdef"
    cout << str2.append(str1, 0, 3) << endl; // 输出 "defabc"
    
    return 0;
}