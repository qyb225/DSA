#include "Stack.h"

bool paren(string exp); //Brace matching(only "()").


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