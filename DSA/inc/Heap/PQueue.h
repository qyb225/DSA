#ifndef PQUEUE_H
#define PQUEUE_H
template <class T>
struct PQueue {
    virtual void insert(const T&) = 0;
    virtual T& getMax() = 0;
    virtual T delMax() = 0;
};


#endif