#ifndef BTREE_H
#define BTREE_H
#include <iostream>
#include "Vector.h"
#include "Stack.h"

template <class T>
struct BTNode {
    BTNode<T>* parent;
    Vector<T> key;
    Vector<BTNode<T>*> child;
    BTNode() { parent = NULL; child.push_back(NULL); }
    BTNode(const Vector<T>& v, const Vector<BTNode<T>*>& c, BTNode<T>* p = NULL) : key(v), child(c), parent(p) {}
    BTNode(const T& e, BTNode<T>* lc = NULL, BTNode<T>* rc = NULL) {
        key.push_back(e);
        child.push_back(lc);
        child.push_back(rc);
        parent = NULL;
        if (lc) lc->parent = this;
        if (rc) rc->parent = this;
    }
};

template <class T>
class BTree {
protected:
    int _size;  //规模
    int _order; //阶次
    BTNode<T>* _root;
    BTNode<T>* _hot; //search()访问最后非空节点位置
    void solveOverflow(BTNode<T>*);   //因插入而上溢的分裂处理
    void solveUnderflow(BTNode<T>*);  //因删除而下溢的合并处理
public:
    BTree(int m) : _size(0), _order(m), _root(NULL), _hot(NULL) {} //|key| < m, ⌈m / 2⌉ <= |child| <= m
    int size() const { return _size; }
    int order() const { return _order; }
    BTNode<T>* search(const T&);
    bool insert(const T&);
    bool remove(const T&);
    ~BTree();
};

template <class T>
BTNode<T>* BTree<T>::search(const T& e) {
    BTNode<T>* v = _root;
    _hot = NULL;
    while (v) {
        int r = v->key.search(e);
        if (r > -1 && v->key[r] == e)
            return v;
        _hot = v;
        v = v->child[r + 1];
    }
    return NULL;
}

template <class T>
bool BTree<T>::insert(const T& e) {
    if (_size == 0) {
        ++_size;
        if (_root) delete _root;
        _root = new BTNode<T>(e);
        return true;
    }
    BTNode<T>* v = search(e);
    if (v) return false;
    int r = _hot->key.search(e);
    _hot->key.insert(r + 1, e);
    _hot->child.push_back(NULL); //外部节点全为NULL 直接push_back即可
    ++_size;
    solveOverflow(_hot);
    return true;
}

template <class T>
bool BTree<T>::remove(const T& e) {
    BTNode<T>* v = search(e);
    if (!v) return false;
    int r = v->key.search(e);
    if (v->child[0]) {
        BTNode<T>* u = v->child[r + 1];
        while (u->child[0]) u = u->child[0];
        v->key[r] = u->key[0];
        v = u;
        r = 0;
    }
    v->key.remove(r);
    v->child.pop_back(); //与插入算法对称 直接pop_back
    --_size;
    solveUnderflow(v);
    return true;
}

template <class T>
void BTree<T>::solveOverflow(BTNode<T>* v) {
    int s = _order / 2;
    while (v->key.size() >= _order) {
        BTNode<T>* p = v->parent;
        BTNode<T>* u = new BTNode<T>(v->key.split(s + 1), v->child.split(s + 1), p);
        if (u->child[0]) {
            for (int i = 0; i < u->child.size(); ++i)
                u->child[i]->parent = u;
        }
        T data = v->key.pop_back();
        if (p) {
            int r = p->key.search(data);
            p->key.insert(r + 1, data);
            p->child.insert(r + 2, u);
            v = p;
        }
        else {
            _root = new BTNode<T>(data, v, u);
            return;
        }
    }
}

template <class T>
void BTree<T>::solveUnderflow(BTNode<T>* v) {
    while ((_order + 1) / 2 > v->child.size()) {
        BTNode<T>* p = v->parent;
        if (!p) {
            if (!v->key.size() && v->child[0]) {
                _root = v->child[0]; _root->parent = NULL;
                v->child[0] = NULL; if (v) delete v;
            }
            return;
        }
        int r = 0;
        while (p->child[r] != v) r++;
        if (0 < r) {
            BTNode<T>* ls = p->child[r - 1];
            if ((_order + 1) / 2 < ls->child.size()) {
                v->key.insert(0, p->key[r - 1]);
                p->key[r - 1] = ls->key.remove(ls->key.size() - 1);
                v->child.insert(0, ls->child.remove(ls->child.size() - 1));
                if (v->child[0]) v->child[0]->parent = v;
                return;
            }
        }
        if (p->child.size() - 1 > r) {
            BTNode<T>* rs = p->child[r + 1];
            if ((_order + 1) / 2 < rs->child.size()) {
                v->key.insert(v->key.size(), p->key[r]);
                p->key[r] = rs->key.remove(0);
                v->child.insert(v->child.size(), rs->child.remove(0));
                if (v->child[v->child.size() - 1]) 
                    v->child[v->child.size() - 1]->parent = v;
                return;
            }
        }
        if (0 < r) {
            BTNode<T>* ls = p->child[r - 1];
            ls->key.insert(ls->key.size(), p->key.remove(r - 1)); p->child.remove(r);
            ls->child.insert(ls->child.size(), v->child.remove(0));
            if (ls->child[ls->child.size() - 1])
                ls->child[ls->child.size() - 1]->parent = ls;
            ls->key.merge(v->key);
            ls->child.merge(v->child);
            for (int i = 0; i < v->child.size(); ++i) {
                if (v->child[i]) v->child[i]->parent = ls;
            }
            if (v) delete v;
        }
        else {
            BTNode<T>* rs = p->child[r + 1];
            rs->key.insert(0, p->key.remove(r)); p->child.remove(r);
            rs->child.insert(0, v->child.remove(v->child.size() - 1));
            if (rs->child[0]) rs->child[0]->parent = rs;
            rs->key.merge(v->key);
            rs->child.merge(v->child);
            for (int i = 0; i < v->child.size(); ++i) {
                if (v->child[i]) v->child[i]->parent = rs;
            }
            if (v) delete v;
        }
        v = p;
    }
}

template <class T>
BTree<T>::~BTree() {
    Stack<BTNode<T>*> s;
    s.push(_root);
    while (!s.empty()) {
        BTNode<T>* v = s.pop();
        if (v->child[0]) {
            for (int i = 0; i < v->child.size(); ++i) {
                s.push(v->child[i]);
            }
        }
        delete v;
    }
}

#endif