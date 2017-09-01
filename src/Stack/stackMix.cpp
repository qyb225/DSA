#include "Stack.h"
#include <iostream>
#include <string>
using namespace std;

template <class T>
bool if_stack_mix(T * a, T * b, int n);

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