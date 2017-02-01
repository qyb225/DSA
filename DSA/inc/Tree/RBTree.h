#ifndef RBTREE_H
#define RBTREE_H
#include "BST.h"

// typedef enum { RB_BLACK, RB_RED} RB_Color;
// template <class T>
// struct BinNode {
// ...
//     RB_Color color; //默认RB_RED
// ...
// };

template <class T>
class RBTree: public BST<T> {
protected:
    void solveDoubleRed(BinNode<T>*);   //双红修正
    //void solveDoubleBlack(BinNode<T>*); //双黑修正
    int updateHeight(BinNode<T>*);      //黑高度
    bool isBlack(BinNode<T>* x) { return !x || x->color == RB_BLACK; } //外部节点全部为黑色
    BinNode<T>* rotateAt(BinNode<T>*);
public:
    BinNode<T>* insert(const T&);
    //bool remove(const T&);
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
void RBTree<T>::solveDoubleRed(BinNode<T>* x) {
    BinNode<T>* p = x->parent;
    BinNode<T>* g = NULL;
    BinNode<T>* u = NULL;
    while (!isBlack(p)) {
        g = p->parent;
        u = (g->lChild == p)? g->rChild : g->lChild;
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