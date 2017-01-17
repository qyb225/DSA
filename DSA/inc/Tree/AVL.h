#ifndef AVL_H
#define AVL_H
#include "BST.h"

template <class T>
class AVL: public BST<T> {
protected:
    bool Balanced(BinNode<T>* x) { return stature(x->lChild) == stature(x->rChild); } //理想平衡
    int BalFac(BinNode<T>* x) { return stature(x->lChild) - stature(x->rChild); } //平衡因子
    bool AVLBalanced(BinNode<T>* x) { return BalFac(x) > -2 && BalFac(x) < 2; } //AVL平衡条件
public:
    BinNode<T>* insert(const T&);
    bool remove(const T&);
};

#endif