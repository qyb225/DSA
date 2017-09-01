#include "Stack.h"
#include <iostream>
#include <string>
using namespace std;

string change(string);
bool cmp(char a, char b); //小于则true;

string change(string a) {
    string ans;
    int i = 0;
    Stack<char> s;
    while (i < a.size()) {
        if (a[i] >= '0' && a[i] <= '9') ans += a[i]; //是否是数字
        else { //是运算符
            if (a[i] == ')') {
                while (s.top() != '(') {
                    ans += s.top();
                    s.pop();
                }
                s.pop();
            }
            else if (s.empty()) s.push(a[i]); //栈空则压栈
            else {
                while (!s.empty() && !cmp(s.top(), a[i])) { //前者运算优先级大于等于后者
                    ans += s.top();
                    s.pop();
                }
                s.push(a[i]);
            }
        }
        ++i;
    }
    while (!s.empty()) {
        ans += s.top();
        s.pop();
    }
    return ans;
}

bool cmp(char a, char b) {
    int _a, _b;
    if (a == '(') _a = 0;
    if (b == '(') _b = 10;
    if (a == '+' || a == '-') _a = 1;
    if (b == '+' || b == '-') _b = 1;
    if (a == '*' || a == '/') _a = 2;
    if (b == '*' || b == '/') _b = 2;
    return _a - _b < 0;
}