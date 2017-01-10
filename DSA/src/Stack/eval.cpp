#include "../../inc/Stack/Stack.h"
#include <iostream>
#include <string>
using namespace std;

char optr_cmp(char a, char b);
bool is_digit(char a);
double calculate_express(char* express);
double calc(double a, double b, char op);

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