#ifndef BST_H
#define BST_H
#include "BinTree.h"

template <class T>
class BST: public BinTree<T> {
protected:
    BinNode<T>* _hot; //命中结点的父亲
    BinNode<T>* connect34(BinNode<T>*, BinNode<T>*, BinNode<T>*,
        BinNode<T>*, BinNode<T>*, BinNode<T>*, BinNode<T>*); //3+4重构
    BinNode<T>* rotateAt(BinNode<T>*); //旋转调整
public:
    static BinNode<T>*& searchIn(const T&, BinNode<T>*&, BinNode<T>*&);
    static BinNode<T>* removeAt(BinNode<T>*& x, BinNode<T>*& hot);
    virtual BinNode<T>*& search(const T&);
    virtual BinNode<T>* insert(const T&);
    virtual bool remove(const T&);
};

template <class T>
void swapData(T& a, T&b);

template <class T>
BinNode<T>*& BST<T>::search(const T& e) {
    return searchIn(e, _root, _hot = NULL);
}

template <class T>
bool BST<T>::remove(const T& e) {
    BinNode<T>*& x = search(e);
    if (!x) return false;
    removeAt(x, _hot);
    --_size;
    updateHeightAbove(_hot);
    return true;
}

template <class T>
BinNode<T>* BST<T>::removeAt(BinNode<T>*& x, BinNode<T>*& hot) {
    BinNode<T>* w = x;
    BinNode<T>* suc = NULL;
    if (x->lChild && x->rChild) {
        w = w->succ();
        swapData(x->data, w->data);
        BinNode<T>* u = w->parent;
        if (x == u)
            u->rChild = suc = w->rChild;
        else
            u->lChild = suc = w->rChild;
    }
    else if (x->lChild) suc = x = x->lChild;
    else if (x->rChild) suc = x = x->rChild;
    else {
        if (x->parent->lChild == x) x->parent->lChild = NULL;
        else x->parent->rChild = NULL;
    }
    hot = w->parent;
    if (suc) suc->parent = hot;
    delete w;
    return suc;
}

template <class T>
BinNode<T>*& BST<T>::searchIn(const T& e, BinNode<T>*& r, BinNode<T>*& hot) {
    if (!r) return r;
    hot = r;
    if (e < r->data) searchIn(e, r->lChild, hot);
    else if (r->data < e) searchIn(e, r->rChild, hot);
    else return r;
}

template <class T>
BinNode<T>* BST<T>::insert(const T& e) {
    BinNode<T>*&p = search(e);
    if (!p) {
        p = new BinNode<T>(e, _hot);
        ++_size;
        updateHeightAbove(p);
    }
    return p;
}

template <class T>
void swapData(T& a, T&b) {
    T tmp = a;
    a = b;
    b = tmp;
}

#endif