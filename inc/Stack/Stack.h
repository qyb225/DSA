#ifndef STACK_H
#define STACK_H
#include "../Vector/Vector.h"

template <class T>
class Stack : public Vector<T> {
public:
    Stack(int size = 8) : Vector(size) {}
    void push(const T& e) { push_back(e); }
    T& top() { return (*this)[size() - 1]; }
    T pop() { return pop_back(); }
    bool empty() { return 0 == size(); }
};

#endif