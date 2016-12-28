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
    virtual BinNode<T>*& search(const T&);
    virtual BinNode<T>* insert(const T&);
    virtual bool remove(const T&) { return true; }
};

template <class T>
BinNode<T>*& BST<T>::search(const T& e) {
    return searchIn(e, _root, _hot = NULL);
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

#endif