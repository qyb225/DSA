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
    BinNode<T>* searchIn(const T&, BinNode<T>*);
    BinNode<T>* removeAt(BinNode<T>*);
    BinNode<T>* hot() { return _hot; }
    virtual BinNode<T>* search(const T&);
    virtual BinNode<T>* insert(const T&);
    virtual bool remove(const T&);
};

template <class T>
BinNode<T>* BST<T>::searchIn(const T& e, BinNode<T>* p) {
    if (!p) return p;
    while (p) {
        _hot = p;
        if (e < p->data) p = p->lChild;
        else if (p->data < e) p = p->rChild;
        else {
            _hot = p->parent;
            return p;
        }
    }
    return p;
}

template <class T>
BinNode<T>* BST<T>::search(const T& e) { return searchIn(e, _root); }

template <class T>
BinNode<T>* BST<T>::insert(const T& e) {
    if (empty()) {
        creatRoot(e);
        _hot =NULL;
        return _root;
    }
    BinNode<T>* tmp = search(e);
    if (!tmp) {
        if (e < _hot->data) return insertAsLC(e, _hot);
        else return insertAsRC(e, _hot);
    }
    return tmp;
}

template <class T>
BinNode<T>* BST<T>::removeAt(BinNode<T>* target) {
    if (!target) return false;
    if (target->lChild && target->rChild) {
        BinNode<T>* p = target;
        p = p->rChild;
        while (p->lChild) p = p->lChild;
        target->data = p->data;
        if (target->rChild == p) {
            target->rChild = p->rChild;
            if (p->rChild) p->rChild->parent = target;
        }
        else {
            p->parent->lChild = p->rChild;
            if (p->rChild) p->rChild->parent = p->parent;
        }
        delete p;
    }
    else if (target->lChild) {
        if (target == _root) {
            _root = target->lChild;
            target->lChild->parent = NULL;
        }
        else if (_hot->lChild == target) _hot->lChild = target->lChild;
        else _hot->rChild = target->lChild;
        target->lChild->parent = _hot;
        delete target;
    }
    else if (target->rChild) {
        if (target == _root) {
            _root = target->rChild;
            target->rChild->parent = NULL;
        }
        else if (_hot->lChild == target) _hot->lChild = target->rChild;
        else _hot->rChild = target->rChild;
        target->rChild->parent = _hot;
        delete target;
    }
    else {
        if (target == _root) _root = NULL;
        else if (_hot->rChild == target) _hot->rChild = NULL;
        else _hot->lChild = NULL;
        delete target;
    }
    --_size;
    return _hot;
}

template <class T>
bool BST<T>::remove(const T& e) {
    BinNode<T>* target = search(e);
    updateHeightAbove(_hot);
    return removeAt(target);
}

#endif