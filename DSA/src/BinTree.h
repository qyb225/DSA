#ifndef BINTREE_H
#define BINTREE_H
#define stature(p) ((p) ? p -> height : -1)
#include "Stack.h"
#include "Queue.h"
template <class T>
struct BinNode {
    BinNode<T>* parent, lChild, rChild;
    int height, size;
    T data;
    void insertAsLC(BinNode<T>*);
    void insertAsRC(BinNode<T>*);
    BinNode<T>* succ();
    int size();
    BinNode() { parent = NULL; lChild = NULL; rChild = NULL; height = 0; }
    BinNode(T& d, BinNode<T>* p = NULL, BinNode<T>* l = NULL, BinNode<T>* r = NULL)
    : data(T), parent(p), lChild(l), rChild(r) { height = 0; }
    template <class VST> void traveLevel(VST &);
    template <class VST> void travePre_1(VST &);
    template <class VST> void travePre_2(VST &);
    template <class VST> void traveIn(VST &);
    template <class VST> void travePost(VST &);
};

template <class T>
class BinTree {
private:
    int _size;
    BinNode<T>* _root;
protected:
    virtual int updateHeight(BinNode<T>*);
    void updateHeightAbove(BinNode<T>*);
public:
    int size() const { return _size; }
    bool empty() { return !_root; }
    BinNode<T>* root() { return _root; }
    BinNode<T>* insertAsLC(T& e, BinNode<T>* x);
    BinNode<T>* insertAsRC(T& e, BinNode<T>* x);
};

template <class T, class VST>
void visitAlongLeftBranch(BinNode<T>*, Stack<BinNode<T>*>, VST&);
int max(int, int);

//1. BinNode
template <class T>
int BinNode<T>::size() {
    size = 1;
    if (lChild) size += lChild -> size();
    if (rChild) size += rChild -> size();
    return size;
}

template <class T>
void BinNode<T>::insertAsLC(BinNode<T>* l) {
    lChild = l;
    l -> parent = this;
}

template <class T>
void BinNode<T>::insertAsRC(BinNode<T>* r) {
    rChild = r;
    r -> parent = this;
}

//E.g. 1
template <class T>
template <class VST>
void BinNode<T>::travePre_1(VST& visit) {
    Stack<BinNode<T>*> s;
    BinNode<T>* x = this;
    s.push(x);
    while (!s.empty()) {
        x = s.pop();
        visit(x -> data);
        if (x -> rChild) s.push(x -> rChild);
        if (x -> lChild) s.push(x -> lChild);
    }
}

//E.g. 2
template <class T>
template <class VST>
void BinNode<T>::travePre_2(VST& visit) {
    Stack<BinNode<T>*> s;
    BinNode<T>* x = this;
    s.push(x);
    while (!s.empty()) {
        x = s.pop();
        visitAlongLeftBranch(x, s, visit);
    }
}

//2. BinTree
template <class T>
int BinTree<T>::updateHeight(BinNode<T>* x) {
    x -> height = 1 + max(x -> lChild -> height, x -> rChild -> height);
    return x -> height;
}

template <class T>
void BinTree<T>::updateHeightAbove(BinNode<T>* x) {
    while (x) {
        updateHeight(x);
        x = x -> parent;
    }
}

template <class T>
BinNode<T>* BinTree<T>::insertAsLC(T& e, BinNode<T>* x) {
    BinNode<T>* n = new BinNode<T>(e);
    x -> insertAsLC(n);
    ++_size;
    return n;
}

template <class T>
BinNode<T>* BinTree<T>::insertAsRC(T& e, BinNode<T>* x) {
    BinNode<T>* n = new BinNode<T>(e);
    x -> insertAsRC(n);
    ++_size;
    updateHeightAbove(x);
    return n;
}

//3.Others
int max(int a, int b) {
    if (a > b) return a;
    else return b;
}

template <class T, class VST>
void visitAlongLeftBranch(BinNode<T>* x, Stack<BinNode<T>*> s, VST& visit) {
    while (x) {
        visit(x -> data);
        if(x -> rChild) s.push(x -> rChild);
        x = x -> lChild;
    }
}

#endif