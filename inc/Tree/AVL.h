#ifndef AVL_H
#define AVL_H
#include "BST.h"

template <class T>
class AVL : public BST<T> {
protected:
    bool Balanced(BinNode<T>* x) { return stature(x->lChild) == stature(x->rChild); } //理想平衡
    int BalFac(BinNode<T>* x) { return stature(x->lChild) - stature(x->rChild); } //平衡因子
    bool AVLBalanced(BinNode<T>* x) { return BalFac(x) > -2 && BalFac(x) < 2; } //AVL平衡条件
public:
    BinNode<T>* insert(const T&);
    bool remove(const T&);
};

template <class T>
BinNode<T>* AVL<T>::insert(const T& e) {
    if (empty()) {
        creatRoot(e);
        _hot = NULL;
        return _root;
    }
    BinNode<T>* n = new BinNode<T>(e);
    BinNode<T>* tmp = search(e);
    if (!tmp) {
        if (e < _hot->data) _hot->insertAsLC(n);
        else _hot->insertAsRC(n);
        ++_size;
    }
    BinNode<T>* x = n->parent;
    while (x) {
        if (!AVLBalanced(x)) {
            rotateAt_2(x);
            break;
        }
        else
            updateHeight(x);
        x = x->parent;
    }
    return n;
}

template <class T>
bool AVL<T>::remove(const T& e) {
    BinNode<T>* tmp = search(e);
    if (!tmp) return false;
    removeAt(tmp);
    BinNode<T>* x = _hot;
    updateHeightAbove(x);
    while (x) {
        if (!AVLBalanced(x))
            rotateAt_1(x);
        updateHeight(x);
        x = x->parent;
    }
    return true;
}

#endif