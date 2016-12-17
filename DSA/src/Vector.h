#ifndef VECTOR_H
#define VECTOR_H
#include <iostream>
template <class T>
class Vector {
private:
    int _rank;
    int _capacity;
    T* _elem;
protected:
    void copyForm(T* t, int lo, int hi); //Copy the array to vector.
    void expand(); //increase _capacity.
    void bubble_sort();
    void merge_sort(int, int); //Complish merge sort algorithm
    void merge(int, int, int); //Complish merge sort algorithm
public:
    Vector(int c = 8) {_elem = new T[c]; _rank = 0; _capacity = c;}
    Vector(T* t, int lo, int hi) {copyForm(t, lo, hi);}
    Vector(Vector<T>&);
    Vector<T>& operator= (const Vector<T>&);
    ~Vector() {if(_elem) delete [] _elem;}
    void show(); //Display the member in vector in one line.
    void push_back(const T&); //Add a member.
    int insert(int, const T&); //Add a member in front of i.
    int size() const {return _rank;}
    int remove(int, int); //Remove vector[i, j). A loop: _elem[i++] = _elem[j++]
    T remove(int); //Remove vector[i].
    int find(const T&, int, int); //disordered
    int find(const T&);
    int search(const T&, int, int); //ordered
    int search(const T&); // 1. e exist, return the last one. 2. e isn't exist, return one smaller than e.
    T& operator[] (int r) const;
    int deduplicate(); //disordered
    //void traverse(VST &); //function object. operator();
    int disordered(); //return the number of disordered pair.
    int uniquify(); //ordered
    void sort();
};

template <class T>
void Vector<T>::copyForm(T* t, int lo, int hi) {
    _capacity = 2 * (hi - lo);
    _elem = new T[_capacity];
    _rank = 0;
    while (lo < hi)
        _elem[_rank++] = t[lo++];
}

template <class T>
void Vector<T>::show() {
    for (int i = 0; i < _rank; ++i)
        std::cout << _elem[i] << " ";
    std::cout << std::endl;
}

template <class T>
Vector<T>& Vector<T>::operator= (const Vector<T> & temp) {
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
Vector<T>::Vector(Vector<T>& temp) {
    _capacity = temp._capacity;
    _rank = 0;
    _elem = new T[_capacity];
    while (_rank < temp._rank) {
       _elem[_rank] = temp._elem[_rank];
       ++_rank;
    }
}

template <class T>
void Vector<T>::expand() {
    if (_rank < _capacity)
       return;
    _capacity = _capacity * 2 + 1;
    T* n_elem = new T[_capacity];
    for (int i = 0; i < _rank; ++i)
       n_elem[i] = _elem[i];
    delete [] _elem;
    _elem = n_elem;
}

template <class T>
void Vector<T>::push_back(const T& add) {
    expand();
    _elem[_rank++] = add;
    return;
}

template <class T>
T& Vector<T>::operator[] (int r) const {
    return *(_elem + r);
}

template <class T>
int Vector<T>::insert(int r, const T& in) {
    expand();
    for (int i = _rank; i > r; --i)
       _elem[i] = _elem[i - 1];
    ++_rank;
    _elem[r] = in;
    return r;
}

template <class T>
int Vector<T>::remove(int lo, int hi) {
    while (hi < _rank) {
       _elem[lo++] = _elem[hi++];
    }
    _rank = _rank - (hi - lo);
    return hi - lo;
}

template <class T>
T Vector<T>::remove(int r) {
    T e = _elem[r];
    remove(r, r + 1);
    return e;
}

template <class T>
int Vector<T>::find(const T& e, int lo, int hi) {
    int i;
    for (i = hi - 1; i >= lo; --i) {
       if (e ==_elem[i])
         return i;
    }
    if (i == lo - 1)
       return -1;
}

template <class T>
int Vector<T>::find(const T& e) {
    return find(e, 0, _rank);
}

template <class T>
int Vector<T>::deduplicate() { //disordered
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
void Vector<T>::traverse(VST & func) {
    for (int i = 0; i < _rank; ++i)
       func(_elem[i]);
}*/

template <class T>
int Vector<T>::disordered() {
    int count = 0;
    for (int i = 1; i < _rank; ++i) {
       if (_elem[i - 1] > _elem[i])
         ++count;
    }
    return count;
}

template <class T>
int Vector<T>::uniquify() { //ordered
    int i = 0, j = 0;
    while (++j < _rank) {
       if (_elem[i] != _elem[j])
         _elem[++i] = _elem[j];
    }
    _rank = ++i;
    return j - i;
}

template <class T>
int Vector<T>::search(const T& e, int lo, int hi) {
    int mi;
    while (lo < hi) {
       mi = (lo + hi) / 2; 
       if (e < _elem[mi])
         hi = mi;
       else
         lo = mi + 1;
    }
    return lo - 1;
}

template <class T>
int Vector<T>::search(const T& e) {
    return search(e, 0, _rank);
}

template <class T>
void Vector<T>::sort() {
    merge_sort(0, _rank);
}

template <class T>
void Vector<T>::bubble_sort() {
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

template <class T>
void Vector<T>::merge_sort(int lo, int hi) {
    if (hi - lo < 2)
        return;
    int mi = (lo + hi) / 2;
    merge_sort(lo, mi);
    merge_sort(mi, hi);
    merge(lo, mi, hi);
    return;
}

template <class T>
void Vector<T>::merge(int lo, int mi, int hi) {
    int l = lo, h = hi;
    int mi1 = mi, mi2 = mi;
    T* order = new T[hi - lo];
    int count = 0;
    while (mi1 > lo && hi > mi2) {
        if (_elem[lo] < _elem[mi2])
            order[count++] = _elem[lo++];
        else
            order[count++] = _elem[mi2++];
    }
    while (mi1 > lo)
        order[count++] = _elem[lo++];
    while (hi > mi2)
        order[count++] = _elem[mi2++];
    count = 0;
    while (l < hi)
        _elem[l++] = order[count++];
    delete [] order;
    return;
}

#endif