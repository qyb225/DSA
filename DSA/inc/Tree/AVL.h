#ifndef AVL_H
#define AVL_H
#include "BST.h"

template <class T>
class AVL : public BST<T> {
protected:
    bool Balanced(BinNode<T>* x) { return stature(x->lChild) == stature(x->rChild); } //理想平衡
    int BalFac(BinNode<T>* x) { return stature(x->lChild) - stature(x->rChild); } //平衡因子
    bool AVLBalanced(BinNode<T>* x) { return BalFac(x) > -2 && BalFac(x) < 2; } //AVL平衡条件
    BinNode<T>* connect34(BinNode<T>*, BinNode<T>*, BinNode<T>*,
        BinNode<T>*, BinNode<T>*, BinNode<T>*, BinNode<T>*); //3+4重构
    BinNode<T>* rotateAt_1(BinNode<T>*); //zig/zag旋转调整
    BinNode<T>* rotateAt_2(BinNode<T>*); //3+4重构旋转调整
    BinNode<T>* zig(BinNode<T>*); //顺时针单旋
    BinNode<T>* zag(BinNode<T>*); //逆时针单旋
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

template <class T>
BinNode<T>* AVL<T>::rotateAt_1(BinNode<T>* v) {
    if (stature(v->lChild) > stature(v->rChild)) {
        BinNode<T>* p = v->lChild;
        if (stature(p->lChild) < stature(p->rChild)) zag(p);
        return zig(v);
    }
    else {
        BinNode<T>* p = v->rChild;
        if (stature(p->lChild) > stature(p->rChild)) zig(p);
        return zag(v);
    }
}

template <class T>
BinNode<T>* AVL<T>::zig(BinNode<T>* v) {
    BinNode<T>* p = v->lChild;
    v->lChild = p->rChild;
    if (p->rChild) p->rChild->parent = v;
    p->rChild = v;
    if (!v->parent) {
        p->parent = NULL;
        v->parent = p;
        _root = p;
    }
    else if (v->parent->lChild == v) {
        v->parent->lChild = p;
        p->parent = v->parent;
        v->parent = p;
    }
    else {
        v->parent->rChild = p;
        p->parent = v->parent;
        v->parent = p;
    }
    return p->parent;
}

template <class T>
BinNode<T>* AVL<T>::zag(BinNode<T>* v) {
    BinNode<T>* p = v->rChild;
    v->rChild = p->lChild;
    if (p->lChild) p->lChild->parent = v;
    p->lChild = v;
    if (!v->parent) {
        p->parent = NULL;
        v->parent = p;
        _root = p;
    }
    else if (v->parent->lChild == v) {
        v->parent->lChild = p;
        p->parent = v->parent;
        v->parent = p;
    }
    else {
        v->parent->rChild = p;
        p->parent = v->parent;
        v->parent = p;
    }
    return p->parent;
}

template <class T>
BinNode<T>* AVL<T>::connect34(BinNode<T>* a, BinNode<T>* b, BinNode<T>* c,
    BinNode<T>* T0, BinNode<T>* T1, BinNode<T>* T2, BinNode<T>* T3) {
    a->lChild = T0;
    if (T0) T0->parent = a;
    a->rChild = T1;
    if (T1) T1->parent = a;
    updateHeight(a);

    c->lChild = T2;
    if (T2) T2->parent = c;
    c->rChild = T3;
    if (T3) T3->parent = c;
    updateHeight(c);

    b->lChild = a;
    a->parent = b;
    b->rChild = c;
    c->parent = b;
    updateHeight(b);
    return b;
}

template <class T>
BinNode<T>* AVL<T>::rotateAt_2(BinNode<T>* v) {
    int choose = 0;
    BinNode<T>* r = v->parent;
    if (stature(v->lChild) > stature(v->rChild)) {
        BinNode<T>* p = v->lChild;
        if (stature(p->lChild) > stature(p->rChild)) {
            BinNode<T>* g = p->lChild;
            p->parent = r;
            if (r && r->lChild == v) r->lChild = p;
            else if (r && r->rChild == v) r->rChild = p;
            else _root = p;
            return connect34(g, p, v, g->lChild, g->rChild, p->rChild, v->rChild);
        }
        else {
            BinNode<T>* g = p->rChild;
            if (!g) {
                updateHeight(p);
                updateHeight(v);
                return NULL;
            }
            g->parent = r;
            if (r && r->lChild == v) r->lChild = g;
            else if (r && r->rChild == v) r->rChild = g;
            else _root = g;
            return connect34(p, g, v, p->lChild, g->lChild, g->rChild, v->rChild);
        }
    }
    else {
        BinNode<T>* p = v->rChild;
        if (stature(p->lChild) > stature(p->rChild)) {
            BinNode<T>* g = p->lChild;
            g->parent = r;
            if (r && r->lChild == v) r->lChild = g;
            else if (r && r->rChild == v) r->rChild = g;
            else _root = g;
            return connect34(v, g, p, v->lChild, g->lChild, g->rChild, p->rChild);
        }
        else {
            BinNode<T>* g = p->rChild;
            if (!g) {
                updateHeight(p);
                updateHeight(v);
                return NULL;
            }
            p->parent = r;
            if (r && r->lChild == v) r->lChild = p;
            else if (r && r->rChild == v) r->rChild = p;
            else _root = p;
            return connect34(v, p, g, v->lChild, p->lChild, g->lChild, g->rChild);
        }
    }
}

#endif