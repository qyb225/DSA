#include "my_list.h"

template <class T>
void myList<T>::init() {
    header = new listNode<T>;
    trailer = new listNode<T>;
    header -> succ = trailer;
    header -> pred = NULL;
    trailer -> pred = header;
    trailer -> succ = NULL;
    _size = 0;
}

template <class T>
T& myList<T>::operator[](int n) {
    listNode<T> * val = first();
    while (n > 0) {
        val = val -> succ;
        --n;
    }
    return val -> data;
}

template <class T>
T myList<T>::insertAsFirst(T val) {
    listNode<T> * in = new listNode<T>(val);
    if (_size <= 0)
        trailer -> insertAsPred(in);
    else
        first() -> insertAsPred(in);
    ++_size;
    return val;
}

template <class T>
T myList<T>::insertAsLast(T val) {
    listNode<T> * in = new listNode<T>(val);
    if (_size <= 0)
        trailer -> insertAsPred(in);
    else
        last() -> insertAsSucc(in);
    ++_size;
    return val;
}

template <class T>
myList<T>::~myList() {
    listNode<T>* _beh = header;
    listNode<T>* _fro = header -> succ;
    while (_fro != NULL) {
        delete _beh;
        _beh = _fro;
        _fro = _fro -> succ;
    }
    delete _beh;
}

template <class T>
void myList<T>::show() {
    listNode<T>* i = first();
    while (i != trailer) {
        std::cout << i -> data << " ";
        i = i -> succ;
    }
    std::cout << std::endl;
}

//listNode
template <class T>
void listNode<T>::insertAsPred(listNode<T>* e) {
    e -> pred = pred;
    e -> succ = this;
    pred -> succ = e;
    pred = e;
}

template <class T>
void listNode<T>::insertAsSucc(listNode<T>* e) {
    e -> succ = succ;
    e -> pred = this;
    succ = e;
    succ -> pred = e;
}