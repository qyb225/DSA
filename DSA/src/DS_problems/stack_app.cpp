#include <iostream>
#include <string>
#include <cstdlib>
#include "../DS_header/Stack/Stack.h"
using namespace std;

bool paren(string exp) {
    Stack<char> s;
    for (int i = 0; i < exp.size(); ++i) {
        if (exp[i] == '(')
            s.push(exp[i]);
        else if (!s.empty())
            s.pop();
        else
            return false;
    }
    return s.empty();
}

string conversion(int num, int base) {
    char digit[17] = "0123456789BCDEF";
    Stack<char> num_conv;
    string ans = "";
    while (num > 0) {
        num_conv.push(digit[num % base]);
        num /= base;
    }
    while (!num_conv.empty())
        ans += num_conv.pop();
    return ans;
}

double calc(double a, double b, char op) {
    if ('*' == op)
        return a * b;
    else if ('/' == op)
        return a / b;
    else if ('+' == op)
        return a + b;
    else if ('-' == op)
        return a - b;
}

char optr_cmp(char a, char b) {
    int a_num, b_num;
    if (b == '(') return '<';
    else if ((a == '(' && b != ')') || (a == '\0' && b != '\0')) return '<';
    else if ((a == '(' && b == ')') || (a == '\0' && b == '\0')) return '=';
    else if (b == '\0') return '>';
    else if (a == '\0') return '<';
    else if (b == ')') return '>';
    else {
        if (a == '+') a_num = 0;
        else if (a == '-') a_num = 1;
        else if (a == '/') a_num = 2;
        else if (a == '*') a_num = 3;
        if (b == '+') b_num = 0;
        else if (b == '-') b_num = 1;
        else if (b == '/') b_num = 2;
        else if (b == '*') b_num = 3;
        if (a_num < b_num) return '<';
        else return '>';
    }
}

bool is_digit(char a) {
    return a >= '0' && a <= '9';
}

double calculate_express(char* express) {
    Stack<double> num;
    Stack<char> optr;
    optr.push('\0');
    while (!optr.empty()) {
        if (*express == ' ')
            ++express;
        else if (is_digit(*express)) {
            double _num = atof(express);
            while ((*express >= '0' && *express <= '9') || (*express == '.'))
                ++express;
            num.push(_num);
        }
        else {
            if ((optr_cmp(optr.top(), *express)) == '<') {
                optr.push(*express);
                ++express;
            }
            else if ((optr_cmp(optr.top(), *express)) == '=') {
                optr.pop();
                ++express;
            }
            else {
                double a = num.pop();
                double b = num.pop();
                char op = optr.pop();
                num.push(calc(b, a, op));
            }
        }
    }
    return num.top();
}

template <class T>
bool if_stack_mix(T * a, T * b, int n) { //if b is a zhx of a;
    Stack<T> S, A, B;
    int i = 0, j = 0;
    S.push(a[i]);
    while (i < n && j < n) {
        if (S.top() == b[j]) ++j;
        else {
            ++i;
            if (i < n) S.push(a[i]);
        }
    }
    if (j < n) return false;
    return true;
}