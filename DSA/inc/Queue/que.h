//Queue without inherit

#ifndef QUE_H
#define QUE_H
#include <iostream>
using namespace std;
template <class T>
struct listNode {
    T data;
    listNode<T>* pred;
    listNode<T>* succ;
    listNode(const T& d): data(d), pred(NULL), succ(NULL) {}
    void insertAsPred(listNode<T>*);
};

template <class T>
class queue {
private:
    int rank;
    listNode<T>* header;
    listNode<T>* trailer;
public:
    queue();
    ~queue() { clear(); }
    void clear();
    bool empty() { return rank == 0; }
    int size() { return rank; }
    void enqueue(const T&);
    T dequeue();
    T& front() { return header->succ->data; }
};

template <class T>
void queue<T>::enqueue(const T& d) {
    trailer->insertAsPred(new listNode<T>(d));
    ++rank;
}

template <class T>
T queue<T>::dequeue() {
    listNode<T>* p = header->succ;
    header->succ = p->succ;
    p->succ->pred = header;
    T d = p->data;
    delete p;
    --rank;
    return d;
}

template <class T>
queue<T>::queue() {
    rank = 0;
    header = new listNode<T>(T());
    trailer = new listNode<T>(T());
    header->succ = trailer;
    trailer->pred = header;
}

template <class T>
void queue<T>::clear() {
    listNode<T>* bawk = header;
    listNode<T>* forw = NULL;
    while (bawk) {
        forw = bawk->succ;
        delete bawk;
        bawk = forw;
    }
}

template <class T>
void listNode<T>::insertAsPred(listNode<T>* p) {
    p->succ = this;
    p->pred = pred;
    pred->succ = p;
    pred = p;
}

#endif