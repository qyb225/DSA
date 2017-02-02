#ifndef PQ_COMPLHEAP_H
#define PQ_COMPLHEAP_H
#include "PQueue.h"
#include "../Vector/Vector.h"

template <class T>
class PQ_ComplHeap: public PQueue<T>, public Vector<T> {
protected:
    int percolateDown(int, int); //下滤
    int percolateUp(int); //上滤
    void heapify(int); //Floyd建堆算法
public:
    PQ_ComplHeap(): Vector() {}
    PQ_ComplHeap(T* a, int n) { copyForm(a, 0, n); heapify(n); }
    virtual void insert(const T&);
    virtual T& getMax() { return _elem[0]; }
    virtual T delMax();
};

template <class T>
void heap_sort(T*, int);

template <class T>
void PQ_ComplHeap<T>::insert(const T& e) {
    push_back(e);
    percolateUp(_rank - 1);
}

template <class T>
T PQ_ComplHeap<T>::delMax() {
    T max = _elem[0];
    swap_data(_elem[0], _elem[_rank - 1]);
    --_rank;
    percolateDown(0, _rank);
    return max;
}

template <class T>
void PQ_ComplHeap<T>::heapify(int n) {
    for (int i = (n / 2) - 1; i >= 0; --i)
        percolateDown(i, n);
}

template <class T>
int PQ_ComplHeap<T>::percolateUp(int i) {
    while (i > 0) {
        int j = (i - 1) / 2;
        if (_elem[j] < _elem[i]) {
            swap_data(_elem[j], _elem[i]);
            i = j;
        }
        else break;
    }
    return i;
}

template <class T>
int PQ_ComplHeap<T>::percolateDown(int i, int n) {
    while (2 * i + 2 < n) {
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        if (_elem[l] < _elem[r]) {
            if (_elem[i] < _elem[r]) {
                swap_data(_elem[i], _elem[r]);
                i = r;
            }
            else break;
        }
        else {
            if (_elem[i] < _elem[l]) {
                swap_data(_elem[i], _elem[l]);
                i = l;
            }
            else break;
        }
    }
    if (2 * i + 1 < n && _elem[i] < _elem[2 * i + 1]) {
        swap_data(_elem[i], _elem[2 * i + 1]);
        i = 2 * i + 1;
    }
    return i;
}

template <class T>
void Vector<T>::heap_sort() {
    PQ_ComplHeap<T> heap(_elem, _rank);
    int hi = _rank;
    while (!heap.empty())
        _elem[--hi] = heap.delMax();
}

template <class T>
void heap_sort(T* a, int n) {
    PQ_ComplHeap<T> heap(a, n);
    while (!heap.empty())
        a[--n] = heap.delMax();
}

#endif