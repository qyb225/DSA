#include <iostream>
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
myList<T>::myList(myList<T>& temp) {
    init();
    if (temp.empty())
        return;
    listNode<T>* p = temp.first();
    while (p != temp.trailer) {
        insertAsLast(p -> data);
        p = p -> succ;
    }
}

template <class T>
myList<T>& myList<T>::operator=(myList<T>& temp) {
    if (!empty()) {
        del();
        init();
    }
    if (temp.empty())
        return *this;
    listNode<T>* p = temp.first();
    while (p != temp.trailer) {
        insertAsLast(p -> data);
        p = p -> succ;
    }
    return *this;
}

template <class T>
T& myList<T>::operator[](int i) {
    listNode<T> * val = header;
    while (i >= 0 && val != NULL) {
        val = val -> succ;
        --i;
    }
    return val -> data;
}

template <class T>
T myList<T>::insertAsFirst(T val) {
    listNode<T> * in = new listNode<T>(val);
    header -> insertAsSucc(in);
    ++_size;
    return val;
}

template <class T>
T myList<T>::insertAsLast(T val) {
    listNode<T> * in = new listNode<T>(val);
    trailer -> insertAsPred(in);
    ++_size;
    return val;
}

template <class T>
void myList<T>::del() {
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
    if (empty())
        return;
    listNode<T>* i = first();
    while (i != trailer) {
        std::cout << i -> data << " ";
        i = i -> succ;
    }
    std::cout << std::endl;
}

template <class T>
listNode<T>* myList<T>::find(T e, int n, listNode<T>* p) {
    while (n > 0) {
        p = p -> pred;
        if (p -> data == e)
            return p;
        --n;
    }
    return NULL;
}

template <class T>
listNode<T>* myList<T>::find(T e) {
    return find(e, _size, trailer);
}

template <class T>
listNode<T>* myList<T>::insertPred(T e, listNode<T>* p) {
    listNode<T>* val = new listNode<T>(e);
    p -> insertAsPred(val);
    ++_size;
    return val;
}

template <class T>
listNode<T>* myList<T>::insertSucc(T e, listNode<T>* p) {
    listNode<T>* val = new listNode<T>(e);
    p -> insertAsSucc(val);
    ++_size;
    return val;
}

template <class T>
T myList<T>::remove(int i) {
    listNode<T>* p = first();
    while (i > 0 && p != last()) {
        p = p -> succ;
        --i;
    }
    if (0 == i) {
        T temp = p -> data;
        p -> pred -> succ = p -> succ;
        p -> succ -> pred = p -> pred;
        delete p;
        --_size;
        return temp;
    }   
}

template <class T>
T myList<T>::remove(listNode<T>* p) {
    if (p != header && p != trailer) {
        T temp = p -> data;
        p -> pred -> succ = p -> succ;
        p -> succ -> pred = p -> pred;
        delete p;
        --_size;
        return temp;
    }
}

template <class T>
int myList<T>::deduplicate() {
    listNode<T>* p = last();
    listNode<T>* judge = NULL; 
    int n = _size - 1;
    while (n > 0) {
        judge = find(p -> data, n, p);
        if (judge) {
            remove(judge);
            --n;
        }
        else {
            p = p -> pred;
            --n;
        }
    }
    return _size;
}

template <class T>
int myList<T>::disordered() {
    int count = 0;
    listNode<T>* p = first();
    while (p != last()) {
        if (p -> succ -> data < p -> data)
            ++count;
        p = p -> succ;
    }
    return count;
}

template <class T> 
int myList<T>::uniquify() {
    if (_size < 2) return _size;
    listNode<T>* p = first();
    listNode<T>* q = p -> succ;
    while (p != last()) {
        if(p -> data == q -> data) {
            remove(q);
            q = p -> succ;
        }
        else {
            p = q;
            q = p -> succ;
        }
    }
    return _size;
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
    succ -> pred = e;
    succ = e;
}