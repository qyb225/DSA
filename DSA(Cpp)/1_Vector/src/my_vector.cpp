#include "my_vector.h"
#include <iostream>

template <class T>
void my_vector<T>::copyForm(T* t, int lo, int hi) {
    _capacity = 2 * (hi - lo);
    _elem = new T[_capacity];
    _rank = 0;
    while (lo < hi)
        _elem[_rank++] = t[lo++];
}

template <class T>
void my_vector<T>::show() {
    for (int i = 0; i < _rank; ++i)
        std::cout << _elem[i] << " ";
    std::cout << std::endl;
}

template <class T>
my_vector<T>& my_vector<T>::operator= (const my_vector<T> & temp) {
    _capacity = temp._capacity;
    if (_elem != NULL)
        delete [] _elem;
    _rank = 0;
    _elem = new T[_capacity];
    while (_rank < temp._rank) {
        _elem[_rank] = temp._elem[_rank];
        ++_rank;
    }
    return *this;
}

template <class T>
void my_vector<T>::expand() {
    if (_rank < _capacity)
        return;
    _capacity *= 2;
    T* n_elem = new T[_capacity];
    for (int i = 0; i < _rank; ++i)
        n_elem[i] = _elem[i];
    delete [] _elem;
    _elem = n_elem;
}

template <class T>
void my_vector<T>::push_back(T add) {
    expand();
    _elem[_rank++] = add;
    return;
}

template <class T>
T& my_vector<T>::operator[] (int r) const {
    return *(_elem + r);
}

template <class T>
int my_vector<T>::insert(int r, T in) {
    expand();
    for (int i = _rank; i > r; --i)
        _elem[i] = _elem[i - 1];
    ++_rank;
    _elem[r] = in;
    return r;
}

template <class T>
int my_vector<T>::remove(int lo, int hi) {
    while (hi < _rank) {
        _elem[lo++] = _elem[hi++];
    }
    _rank = _rank - (hi - lo);
    return hi - lo;
}

template <class T>
int my_vector<T>::remove(int r) {
    T e = _elem[r];
    remove(r, r + 1);
    return e;
}

template <class T>
int my_vector<T>::find(T e, int lo, int hi) {
    int i;
    for (i = hi - 1; i >= lo; --i) {
        if (e ==_elem[i])
            return i;
    }
    if (i == lo - 1)
        return -1;
}

template <class T>
int my_vector<T>::find(T e) {
    return find(e, 0, _rank);
}

template <class T>
int my_vector<T>::deduplicate() { //disordered
    int i = 1;
    int old_size = _rank;
    while (i < _rank) {
        if (-1 == find(_elem[i], 0, i))
            ++i;
        else
            remove(i);
    }
    return old_size - _rank;
}
/*
template <class T, class VST>
void my_vector<T>::traverse(VST & func) {
    for (int i = 0; i < _rank; ++i)
        func(_elem[i]);
}*/

template <class T>
int my_vector<T>::disordered() {
    int count = 0;
    for (int i = 1; i < _rank; ++i) {
        if (_elem[i - 1] > _elem[i])
            ++count;
    }
    return count;
}

template <class T>
int my_vector<T>::uniquify() { //ordered
    int i = 0, j = 0;
    while (++j < _rank) {
        if (_elem[i] != _elem[j])
            _elem[++i] = _elem[j];
    }
    _rank = ++i;
    return j - i;
}

template <class T>
int my_vector<T>::search(T e, int lo, int hi) {
    int mi;
    while (lo < hi) {
        mi = (lo + hi) / 2; 
        //mi = (int)(lo + (hi - lo - 1) * ((float)e - _elem[lo]) / (_elem[hi - 1] - _elem[lo]));
        if (e < _elem[mi])
            hi = mi;
        else
            lo = mi + 1;
    }
    return lo - 1;
}

template <class T>
int my_vector<T>::search(T e) {
    return search(e, 0, _rank);
}

template <class T>
void my_vector<T>::sort() {
    bubble_sort();
}

template <class T>
void my_vector<T>::bubble_sort() {
    int n = _rank;
    int sorted = false;
    while (n >= 1 && !sorted) {
        sorted = true;
        for (int i = 1; i < n; ++i) {
            if (_elem[i] < _elem[i - 1]) {
                sorted = false;
                T swap = _elem[i];
                _elem[i] = _elem[i - 1];
                _elem[i - 1] = swap;
            }
        }
        --n;
    }
}