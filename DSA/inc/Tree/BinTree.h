#ifndef BINTREE_H
#define BINTREE_H
#include "../Stack/Stack.h"
#include "../Queue/Queue.h"
template <class T>
struct BinNode {
    BinNode<T>* parent, *lChild, *rChild;
    int height, __size;
    T data;
    void insertAsLC(BinNode<T>*);
    void insertAsRC(BinNode<T>*);
    BinNode<T>* succ();
    int size();
    BinNode()
        : parent(NULL), lChild(NULL), rChild(NULL), height(0), __size(1) {}
    BinNode(const T& d, BinNode<T>* p = NULL)
        : data(d), parent(p), lChild(NULL), rChild(NULL), height(0), __size(1) {}
    BinNode(const T& d, int h, int s)
        : data(d), height(h), __size(s), parent(NULL), lChild(NULL), rChild(NULL) {}
    template <class VST> void traveLevel(VST &);
    template <class VST> void travePre_1(VST &);
    template <class VST> void travePre_2(VST &);
    template <class VST> void traveIn(VST &);
    template <class VST> void travePost(VST &);
};

template <class T>
class BinTree {
protected:
    int _size;
    BinNode<T>* _root;
    virtual int updateHeight(BinNode<T>*);
    void updateHeightAbove(BinNode<T>*);
    BinNode<T>* copyNode(const BinNode<T>*);
public:
    BinTree() { _size = 0; _root = NULL; }
    BinTree(const T &);
    BinTree(BinNode<T>*);
    BinTree(const BinTree<T>&);
    void creatRoot(const T&);
    int size() const { return _size; }
    bool empty() { return _size == 0; }
    BinNode<T>* root() { return _root; }
    int height() { return _root->height; }
    BinTree<T>& secede(BinNode<T>*);
    BinTree<T>& secede(BinNode<T>*, BinTree<T>&);
    BinNode<T>* insertAsLC(const T&, BinNode<T>*);
    BinNode<T>* insertAsRC(const T&, BinNode<T>*);
    BinNode<T>* attachAsLC(BinNode<T>*, BinNode<T>*); //insert a node(subtree) as left child.
    BinNode<T>* attachAsRC(BinNode<T>*, BinNode<T>*);
    BinNode<T>* find(T, BinNode<T>*); //Find a node in a subtree by TravePre.
    BinNode<T>* find(T);
    int remove(BinNode<T>*);
    template <class VST> void travePre(VST & visit) { _root->travePre_1(visit); }
    template <class VST> void traveIn(VST & visit) { _root->traveIn(visit); }
    template <class VST> void travePost(VST & visit) { _root->travePost(visit); }
    template <class VST> void traveLevel(VST & visit) { _root->traveLevel(visit); }
    ~BinTree() { if (_size > 0) remove(_root); }
};

template <class T, class VST>
void visitAlongLeftBranch(BinNode<T>*, Stack<BinNode<T>*>&, VST&);
template <class T>
void goAlongLeftBranch(BinNode<T>*, Stack<BinNode<T>*>&);
int max(int, int);

//1. BinNode
template <class T>
int BinNode<T>::size() {
    __size = 1;
    if (lChild) __size += lChild->size();
    if (rChild) __size += rChild->size();
    return __size;
}

template <class T>
void BinNode<T>::insertAsLC(BinNode<T>* l) {
    lChild = l;
    l->parent = this;
    __size += l->__size;
}

template <class T>
void BinNode<T>::insertAsRC(BinNode<T>* r) {
    rChild = r;
    r->parent = this;
    __size += r->__size;
}

template <class T>
BinNode<T>* BinNode<T>::succ() {
    BinNode<T>* p = this;
    if (rChild) {
        p = rChild;
        while (p->lChild) {
            p = p->lChild;
        }
        return p;
    }
    else {
        while (p->parent->rChild == p) {
            p = p->parent;
        }
        return p->parent;
    }
    return NULL;
}

//1.1 travelPre
template <class T>
template <class VST>
void BinNode<T>::travePre_1(VST& visit) {
    Stack<BinNode<T>*> s;
    BinNode<T>* x = this;
    s.push(x);
    while (!s.empty()) {
        x = s.pop();
        visit(x->data);
        if (x->rChild) s.push(x->rChild);
        if (x->lChild) s.push(x->lChild);
    }
}

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

//1.2 travelIn
template <class T>
template <class VST>
void BinNode<T>::traveIn(VST& visit) {
    Stack<BinNode<T>*> s;
    BinNode<T>* x = this;
    goAlongLeftBranch(x, s);
    while (!s.empty()) {
        x = s.pop();
        visit(x->data);
        x = x->rChild;
        goAlongLeftBranch(x, s);
    }
}

//1.3 travelPost
template <class T>
template <class VST>
void BinNode<T>::travePost(VST& visit) {
    if (lChild) lChild->travePost(visit);
    if (rChild) rChild->travePost(visit);
    visit(x->data);
}

//1.4 travelLevel
template <class T>
template <class VST>
void BinNode<T>::traveLevel(VST& visit) {
    Queue<BinNode<T>*> q;
    BinNode<T>* x = this;
    q.enqueue(x);
    while (!q.empty()) {
        x = q.dequeue();
        visit(x->data);
        if (x->lChild) q.enqueue(x->lChild);
        if (x->rChild) q.enqueue(x->rChild);
    }
}

//2. BinTree
template <class T>
BinTree<T>::BinTree(const T& e) {
    _root = new BinNode<T>(e);
    _size = 1;
}

template <class T>
BinTree<T>::BinTree(const BinTree<T>& temp) {
    _size = temp._size;
    _root = copyNode(temp._root);
}

template <class T>
BinTree<T>::BinTree(BinNode<T>* r): _size(0), _root(NULL) {
    if (!(r->parent)) {
        _size = r->size();
        _root = r;
    }
}

template <class T>
void BinTree<T>::creatRoot(const T& e) {
    if (!empty()) remove(_root);
    _root = new BinNode<T>(e);
    _size = 1;
}

template <class T>
int BinTree<T>::updateHeight(BinNode<T>* x) {
    int lHeight, rHeight;
    if (x->lChild)
        lHeight = x->lChild->height;
    else
        lHeight = 0;
    if (x->rChild)
        rHeight = x->rChild->height;
    else
        rHeight = 0;

    x->height = 1 + max(lHeight, rHeight);
    return x->height;
}

template <class T>
void BinTree<T>::updateHeightAbove(BinNode<T>* x) {
    while (x) {
        updateHeight(x);
        x = x->parent;
    }
}

template <class T>
BinNode<T>* BinTree<T>::insertAsLC(const T& e, BinNode<T>* x) {
    BinNode<T>* n = new BinNode<T>(e);
    x->insertAsLC(n);
    ++_size;
    updateHeightAbove(x);
    return n;
}

template <class T>
BinNode<T>* BinTree<T>::insertAsRC(const T& e, BinNode<T>* x) {
    BinNode<T>* n = new BinNode<T>(e);
    x->insertAsRC(n);
    ++_size;
    updateHeightAbove(x);
    return n;
}

template <class T>
int BinTree<T>::remove(BinNode<T>* x) {
    if (!x) return 0;
    int temp = 1;
    if (x->lChild) temp += remove(x->lChild);
    if (x->rChild) temp += remove(x->rChild);
    delete x;
    x = NULL;
    --_size;
    return temp;
}

template <class T>
BinNode<T>* BinTree<T>::find(T e, BinNode<T>* x) {
    Stack<BinNode<T>*> s;
    s.push(x);
    while (!s.empty()) {
        x = s.pop();
        if (e == x->data) return x;
        if (x->rChild) s.push(x->rChild);
        if (x->lChild) s.push(x->lChild);
    }
}

template <class T>
BinNode<T>* BinTree<T>::find(T e) {
    return find(e, _root);
}

template <class T>
BinNode<T>* BinTree<T>::copyNode(const BinNode<T>* x) {
    BinNode<T>* r = new BinNode<T>(x->data, x->height, x->__size);
    if (x->lChild) {
        r->lChild = copyNode(x->lChild);
        r->lChild->parent = r;
    }
    if (x->rChild) {
        r->rChild = copyNode(x->rChild);
        r->rChild->parent = r;
    }
    r->size();
    return r;
}

template <class T>
BinNode<T>* BinTree<T>::attachAsLC(BinNode<T>* e, BinNode<T>* x) {
    if (x->lChild) remove(x->lChild);
    e->size();
    x->insertAsLC(copyNode(e));
    updateHeightAbove(x);
    _size += x->__size - 1;
    return x->lChild;
}

template <class T>
BinNode<T>* BinTree<T>::attachAsRC(BinNode<T>* e, BinNode<T>* x) {
    if (x->rChild) remove(x->rChild);
    e->size();
    x->insertAsRC(copyNode(e));
    updateHeightAbove(x);
    _size += x->__size - 1;
    return x->rChild;
}

template <class T>
BinTree<T>& BinTree<T>::secede(BinNode<T>* x) {
    if (x->parent && x->parent->lChild == x)
        x->parent->lChild = NULL;
    else if (x->parent && x->parent->rChild == x)
        x->parent->rChild = NULL;
    updateHeightAbove(x->parent);
    x->parent = NULL;
    remove(_root);
    _size = x->size();
    _root = x;
    return *this;
}

template <class T>
BinTree<T>& BinTree<T>::secede(BinNode<T>* x, BinTree<T>& t) {
    if (x->parent && x->parent->lChild == x)
        x->parent->lChild = NULL;
    else if (x->parent && x->parent->rChild == x)
        x->parent->rChild = NULL;
    updateHeightAbove(x->parent);
    x->parent = NULL;
    remove(t._root);
    t._size = x->size();
    t._root = x;
    return t;
}

//3.Others
int max(int a, int b) {
    if (a > b) return a;
    else return b;
}

template <class T, class VST>
void visitAlongLeftBranch(BinNode<T>* x, Stack<BinNode<T>*>& s, VST& visit) {
    while (x) {
        visit(x->data);
        if (x->rChild) s.push(x->rChild);
        x = x->lChild;
    }
}

template <class T>
void goAlongLeftBranch(BinNode<T>* x, Stack<BinNode<T>*>& s) {
    while (x) {
        s.push(x);
        x = x->lChild;
    }
}

#endif