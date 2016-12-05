#include "Stack.h"

template <class T>
void Stack<T>::expand() {
    if (_rank < _capacity)
        return;
    _capacity *= 2;
    T* temp = new T[_capacity];
    for (int i = 0; i < _rank; ++i)
        temp[i] = _elem[i];
    delete [] _elem;
    _elem = temp;
}

template <class T>
Stack<T>::Stack(Stack<T>& temp) {
    _rank = temp._rank;
    _capacity = temp._capacity;
    _elem = new T[_capacity];
    for (int i = 0; i < _rank; ++i)
        _elem[i] = temp._elem[i];
}

template <class T>
Stack<T>& Stack<T>::operator=(Stack<T>& temp) {
    if (_elem)
        delete _elem;
    _rank = temp._rank;
    _capacity = temp._capacity;
    _elem = new T[_capacity];
    for (int i = 0; i < _rank; ++i)
        _elem[i] = temp._elem[i];
    return *this;
}

template <class T>
bool Stack<T>::empty() {
    return _rank == 0;
}

template <class T>
void Stack<T>::push(T e) {
    expand();
    _elem[_rank++] = e;
}

template <class T>
int Stack<T>::size() {
    return _rank;
}

template <class T>
T Stack<T>::pop() {
    if (!empty()) return _elem[--_rank];
}

template <class T>
T& Stack<T>::top() {
    return _elem[_rank - 1];
}