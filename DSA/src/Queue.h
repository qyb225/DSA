#ifndef QUEUE_H
#define QUEUE_H
#include "List.h"

template <class T>
class Queue : public List<T> {
public: //size(), empty();
    void enqueue(const T& e) { insertAsLast(e); }
    T dequeue() { return remove(first()); }
    T& front() { return first() -> data; }
};

#endif