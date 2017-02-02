#ifndef RBTREE_H
#define RBTREE_H
#include "BST.h"

template <class T>
class RBTree : public BST<T> {
protected:
    void solveDoubleRed(BinNode<T>*);   //双红修正
    void solveDoubleBlack(BinNode<T>*); //双黑修正
    int updateHeight(BinNode<T>*);      //黑高度
    bool isBlack(BinNode<T>* x) { return !x || x->color == RB_BLACK; } //外部节点全部为黑色
    BinNode<T>* rotateAt(BinNode<T>*);  //3+4重构旋转
    BinNode<T>* removeAt(BinNode<T>*);  //删除
public:
    BinNode<T>* insert(const T&);
    bool remove(const T&);
};

template <class T>
BinNode<T>* RBTree<T>::insert(const T& e) {
    if (empty()) return creatRoot(e);
    BinNode<T>* x = search(e);
    if (x) return NULL;
    if (e < _hot->data) x = insertAsLC(e, _hot);
    else x = insertAsRC(e, _hot);
    x->height = -1; //新红色节点黑高度为-1
    solveDoubleRed(x);
    return x;
}

template <class T>
bool RBTree<T>::remove(const T& e) {
    BinNode<T>* target = search(e);
    return removeAt(target);
}

template <class T>
BinNode<T>* RBTree<T>::removeAt(BinNode<T>* target) {
    if (!target) return NULL;
    BinNode<T>* suc = NULL;
    if (target->lChild && target->rChild) {
        BinNode<T>* p = target->rChild;
        while (p->lChild) p = p->lChild;
        target->data = p->data;
        suc = p->rChild;
        _hot = p->parent;
        if (_hot->rChild == p) {
            _hot->rChild = suc;
            if (suc) suc->parent = _hot;
        }
        else {
            _hot->lChild = suc;
            if (suc) suc->parent = _hot;
        }
        if (isBlack(p) != isBlack(suc)) {
            if (suc) suc->color = RB_BLACK;
        }
        else if (isBlack(suc)) {
            solveDoubleBlack(suc);
        }
        delete p;
    }
    else if (target->lChild) {
        suc = target->lChild;
        if (target == _root) {
            _root = target->lChild;
            target->lChild->parent = NULL;
            _root->color = RB_BLACK;
        }
        else if (_hot->lChild == target) _hot->lChild = target->lChild;
        else _hot->rChild = target->lChild;
        target->lChild->parent = _hot;
        if (isBlack(target) != isBlack(suc)) {
            if (suc) suc->color = RB_BLACK;
        }
        else if (isBlack(suc)) {
            solveDoubleBlack(suc);
        }
        delete target;
    }
    else if (target->rChild) {
        suc = target->rChild;
        if (target == _root) {
            _root = target->rChild;
            target->rChild->parent = NULL;
            _root->color = RB_BLACK;
        }
        else if (_hot->lChild == target) _hot->lChild = target->rChild;
        else _hot->rChild = target->rChild;
        target->rChild->parent = _hot;
        if (isBlack(target) != isBlack(suc)) {
            if (suc) suc->color = RB_BLACK;
        }
        else if (isBlack(suc)) {
            solveDoubleBlack(suc);
        }
        delete target;
    }
    else {
        suc = NULL;
        if (target == _root) _root = NULL;
        else if (_hot->rChild == target) _hot->rChild = NULL;
        else _hot->lChild = NULL;
        if (isBlack(target))
            solveDoubleBlack(NULL);
        delete target;
    }
    --_size;
    if (suc) _hot = suc->parent;
    return suc;
}

template <class T>
void RBTree<T>::solveDoubleBlack(BinNode<T>* r) {
    BinNode<T>* p = _hot;
    if (!_hot) return;
    BinNode<T>* s = (r == p->lChild) ? p->rChild : p->lChild;
    if (isBlack(s) && s && !isBlack(s->lChild)) {
        BinNode<T>* t = s->lChild;
        s->color = p->color;
        t->color = p->color = RB_BLACK;
        rotateAt(t);
    }
    else if (isBlack(s) && s && !isBlack(s->rChild)) {
        BinNode<T>* t = s->rChild;
        s->color = p->color;
        t->color = p->color = RB_BLACK;
        rotateAt(t);
    }
    else if (s && isBlack(s) && isBlack(s->lChild) && isBlack(s->rChild) && !isBlack(p)) {
        s->color = RB_RED;
        p->color = RB_BLACK;
        updateHeight(s);
        updateHeight(p);
    }
    else if (s && isBlack(s) && isBlack(s->lChild) && isBlack(s->rChild) && isBlack(p)) {
        s->color = RB_RED;
        _hot = p->parent;
        updateHeight(s);
        updateHeight(p);
        if (p != _root) solveDoubleBlack(p);
    }
    else if (!isBlack(s) && isBlack(p) && isBlack(s->lChild) && isBlack(s->rChild)) {
        s->color = RB_BLACK;
        p->color = RB_RED;
        if (s == p->lChild) zig(p);
        else zag(p);
        _hot = p;
        updateHeight(p);
        updateHeight(s);
        solveDoubleBlack(r);
    }
}

template <class T>
void RBTree<T>::solveDoubleRed(BinNode<T>* x) {
    BinNode<T>* p = x->parent;
    BinNode<T>* g = NULL;
    BinNode<T>* u = NULL;
    while (!isBlack(p)) {
        g = p->parent;
        u = (g->lChild == p) ? g->rChild : g->lChild;
        if (isBlack(u)) {
            BinNode<T>* n = rotateAt(x);
            n->color = RB_BLACK;
            n->lChild->color = RB_RED;
            n->rChild->color = RB_RED;
            break;
        }
        else {
            p->color = u->color = RB_BLACK;
            updateHeight(p);
            updateHeight(u);
            if (g != _root) g->color = RB_RED;
            else {
                g->color = RB_BLACK;
                updateHeight(g);
                break;
            }
        }
        x = g;
        p = x->parent;
    }
}

template <class T>
int RBTree<T>::updateHeight(BinNode<T>* x) {
    x->height = max(stature(x->lChild), stature(x->rChild));
    if (isBlack(x))
        x->height += 1;
    return x->height;
}

template <class T>
BinNode<T>* RBTree<T>::rotateAt(BinNode<T>* x) {
    BinNode<T>* p = x->parent;
    BinNode<T>* g = p->parent;
    BinNode<T>* ans = NULL;
    if (x->data < p->data) {
        if (p->data < g->data) {
            if (g == _root) {
                ans = connect34(x, p, g, x->lChild, x->rChild, p->rChild, g->rChild);
                _root = ans;
                _root->parent = NULL;
            }
            else {
                if (g->parent->lChild == g) {
                    BinNode<T>* gpar = g->parent;
                    ans = connect34(x, p, g, x->lChild, x->rChild, p->rChild, g->rChild);
                    gpar->lChild = ans;
                    ans->parent = gpar;
                }
                else {
                    BinNode<T>* gpar = g->parent;
                    ans = connect34(x, p, g, x->lChild, x->rChild, p->rChild, g->rChild);
                    gpar->rChild = ans;
                    ans->parent = gpar;
                }
            }
        }
        else {
            if (g == _root) {
                ans = connect34(g, x, p, g->lChild, x->lChild, x->rChild, p->rChild);
                _root = ans;
                _root->parent = NULL;
            }
            else {
                if (g->parent->lChild == g) {
                    BinNode<T>* gpar = g->parent;
                    ans = connect34(g, x, p, g->lChild, x->lChild, x->rChild, p->rChild);
                    gpar->lChild = ans;
                    ans->parent = gpar;
                }
                else {
                    BinNode<T>* gpar = g->parent;
                    ans = connect34(g, x, p, g->lChild, x->lChild, x->rChild, p->rChild);
                    gpar->rChild = ans;
                    ans->parent = gpar;
                }
            }
        }
    }
    else {
        if (p->data < g->data) {
            if (g == _root) {
                ans = connect34(p, x, g, p->lChild, x->lChild, x->rChild, g->rChild);
                _root = ans;
                _root->parent = NULL;
            }
            else {
                if (g->parent->lChild == g) {
                    BinNode<T>* gpar = g->parent;
                    ans = connect34(p, x, g, p->lChild, x->lChild, x->rChild, g->rChild);
                    gpar->lChild = ans;
                    ans->parent = gpar;
                }
                else {
                    BinNode<T>* gpar = g->parent;
                    ans = connect34(p, x, g, p->lChild, x->lChild, x->rChild, g->rChild);
                    gpar->rChild = ans;
                    ans->parent = gpar;
                }
            }
        }
        else {
            if (g == _root) {
                ans = connect34(g, p, x, g->lChild, p->lChild, x->lChild, x->rChild);
                _root = ans;
                _root->parent = NULL;
            }
            else {
                if (g->parent->lChild == g) {
                    BinNode<T>* gpar = g->parent;
                    ans = connect34(g, p, x, g->lChild, p->lChild, x->lChild, x->rChild);
                    gpar->lChild = ans;
                    ans->parent = gpar;
                }
                else {
                    BinNode<T>* gpar = g->parent;
                    ans = connect34(g, p, x, g->lChild, p->lChild, x->lChild, x->rChild);
                    gpar->rChild = ans;
                    ans->parent = gpar;
                }
            }
        }
    }
    return ans;
}

#endif