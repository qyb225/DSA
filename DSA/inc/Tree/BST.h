#ifndef BST_H
#define BST_H
#include "BinTree.h"

template <class T>
class BST: public BinTree<T> {
protected:
    BinNode<T>* _hot; //命中结点的父亲
    BinNode<T>* connect34(BinNode<T>*, BinNode<T>*, BinNode<T>*,
        BinNode<T>*, BinNode<T>*, BinNode<T>*, BinNode<T>*); //3+4重构
    BinNode<T>* rotateAt_1(BinNode<T>*); //zig/zag旋转调整
    BinNode<T>* rotateAt_2(BinNode<T>*); //3+4重构旋转调整
    BinNode<T>* zig(BinNode<T>*); //顺时针单旋
    BinNode<T>* zag(BinNode<T>*); //逆时针单旋
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
    if (!target) return NULL;
    BinNode<T>* suc = NULL;
    if (target->lChild && target->rChild) {
        BinNode<T>* p = target;
        p = p->rChild;
        while (p->lChild) p = p->lChild;
        target->data = p->data;
        suc = p->rChild;
        _hot = p->parent;
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
        suc = target->lChild;
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
        suc = target->rChild;
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
        suc = NULL;
        if (target == _root) _root = NULL;
        else if (_hot->rChild == target) _hot->rChild = NULL;
        else _hot->lChild = NULL;
        delete target;
    }
    --_size;
    if (suc) _hot = suc->parent;
    return suc;
}

template <class T>
bool BST<T>::remove(const T& e) {
    BinNode<T>* target = search(e);
    updateHeightAbove(_hot);
    return removeAt(target);
}

template <class T>
BinNode<T>* BST<T>::rotateAt_1(BinNode<T>* v) {
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
BinNode<T>* BST<T>::zig(BinNode<T>* v) {
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
BinNode<T>* BST<T>::zag(BinNode<T>* v) {
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
BinNode<T>* BST<T>::connect34(BinNode<T>* a, BinNode<T>* b, BinNode<T>* c,
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
BinNode<T>* BST<T>::rotateAt_2(BinNode<T>* v) {
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