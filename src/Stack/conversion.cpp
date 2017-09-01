#include "Stack.h"
#include <iostream>
#include <string>
using namespace std;

string conversion(int num, int base); //Conversion e.g. 31(10) -> 1F(16).

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