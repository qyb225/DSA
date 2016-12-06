#ifndef STACK_H
#define STACK_H
#include "Vector.h"

template <class T>
class Stack : public Vector<T> {
public:
    Stack(int size = 8) : Vector(size) {}
    void push(T e) { push_back(e); }
    T& top() { return (*this)[size() - 1]; }
    T pop() { return remove(size() - 1); }
    bool empty() { return 0 == size(); }
};

#endif