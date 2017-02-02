#ifndef SPLAY_H
#define SPLAY_H
#include "BST.h"

template <class T>
class Splay: public BST<T> {
protected:
    BinNode<T>* splay(BinNode<T>*); //节点伸展至树根
public:
    BinNode<T>* search(const T&);
    BinNode<T>* insert(const T&);
    bool remove(const T&);
};

template <class T>
BinNode<T>* Splay<T>::search(const T& e) {
    BinNode<T>* ans = searchIn(e, _root);
    return splay(ans? ans: _hot);
}

template <class T>
BinNode<T>* Splay<T>::insert(const T& e) {
    if (empty()) {
        creatRoot(e);
        _hot = NULL;
        return _root;
    }
    BinNode<T>* t = search(e);
    if (e == t->data) return t;
    BinNode<T>* lc = t->lChild;
    BinNode<T>* rc = t->rChild;
    BinNode<T>* r = new BinNode<T>(e);
    if (e > t->data) {
        r->insertAsLC(t);
        r->insertAsRC(rc);
        t->rChild = NULL;
    }
    else {
        r->insertAsRC(t);
        r->insertAsLC(lc);
        t->lChild = NULL;
    }
    ++_size;
    return _root = r;
}

template <class T>
bool Splay<T>::remove(const T& e) {
    BinNode<T>* t = search(e);
    if (e != t->data) return false;
    if (t->rChild) {
        BinNode<T>* x = t->rChild;
        while (x->lChild) x = x->lChild;
        t->data = x->data;
        if (x->parent->lChild == x)
            x->parent->insertAsLC(x->rChild);
        else if (x->parent->rChild == x)
            x->parent->insertAsRC(x->rChild);
        delete x;
    } else {
        _root = t->lChild;
        delete t;
    }
    if (_root) _root->parent = NULL;
    --_size;
    return true;
}

template <class T>
BinNode<T>* Splay<T>::splay(BinNode<T>* v) {
    if (!v) return NULL;
    BinNode<T>* p = NULL;
    BinNode<T>* g = NULL;
    while ((p = v->parent) && (g = p->parent)) {
        if (p->lChild == v) {
            if (g->lChild == p) {
                zig(g);
                zig(p);
            } else if (g->rChild == p) {
                zig(p);
                zag(g);
            }
        } else if (p->rChild == v) {
            if (g->lChild == p) {
                zag(p);
                zig(g);
            } else if (g->rChild == p) {
                zag(g);
                zag(p);
            }
        }
        updateHeight(g);
        updateHeight(p);
        updateHeight(v);
    }
    if (p = v->parent) {
        if (p->lChild == v)
            zig(p);
        else if (p->rChild == v)
            zag(p);
        updateHeight(p);
        updateHeight(v);
    }
    return _root = v;
}

#endif