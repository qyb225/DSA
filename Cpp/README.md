# DSA

---

##Vector, list, Stack, Queue

**1. Vector**

```cpp
template <class T>
class Vector {
protected:
    int _rank;
    int _capacity;
    T* _elem;
    void expand(); //increase _capacity.
    int pivot(int, int);
    void merge(int, int, int);
    void bubble_sort();
    void merge_sort(int, int);
    void quick_sort(int, int);
public:
    ~Vector() {if(_elem) delete [] _elem;}
    int remove(int, int); //Remove vector[i, j). A loop: _elem[i++] = _elem[j++]
    T remove(int); //Remove vector[i].
    int search(const T&, int, int); //ordered
    int search(const T&); // 1. e exist, return the last one. 2. e isn't exist, return one smaller than e.
    int uniquify(); //ordered
    void sort();
};

template <class T>
void Vector<T>::expand() {
    if (_rank < _capacity)
       return;
    _capacity = _capacity * 2 + 1;
    T* n_elem = new T[_capacity];
    for (int i = 0; i < _rank; ++i)
       n_elem[i] = _elem[i];
    delete [] _elem;
    _elem = n_elem;
}

template <class T>
int Vector<T>::search(const T& e, int lo, int hi) {
    int mi;
    while (lo < hi) {
       mi = (lo + hi) / 2; 
       if (e < _elem[mi])
         hi = mi;
       else
         lo = mi + 1;
    }
    return lo - 1;
}

template <class T>
void Vector<T>::merge_sort(int lo, int hi) {
    if (hi - lo < 2)
        return;
    int mi = (lo + hi) / 2;
    merge_sort(lo, mi);
    merge_sort(mi, hi);
    merge(lo, mi, hi);
    return;
}

template <class T>
void Vector<T>::merge(int lo, int mi, int hi) {
    int l = lo, h = hi;
    int mi1 = mi, mi2 = mi;
    T* order = new T[hi - lo];
    int count = 0;
    while (mi1 > lo && hi > mi2) {
        if (_elem[lo] < _elem[mi2])
            order[count++] = _elem[lo++];
        else
            order[count++] = _elem[mi2++];
    }
    while (mi1 > lo)
        order[count++] = _elem[lo++];
    while (hi > mi2)
        order[count++] = _elem[mi2++];
    count = 0;
    while (l < hi)
        _elem[l++] = order[count++];
    delete [] order;
    return;
}

template <class T>
void Vector<T>::quick_sort(int lo, int hi) {
    if (hi - lo < 2) return;
    int piv = pivot(lo, hi - 1);
    int i = lo, j = piv - 1;
    while (i <= j) {
        while (_elem[i] < _elem[piv]) ++i;
        while (_elem[j] >= _elem[piv]) --j;
        if (i < j) swap_data(_elem[i], _elem[j]);
    }
    swap_data(_elem[i], _elem[piv]);
    quick_sort(i + 1, hi);
    quick_sort(lo, i);
}

template <class T>
int Vector<T>::pivot(int lo, int hi) {
    int mi = (lo + hi) >> 1;
    if (_elem[mi] < _elem[lo]) swap_data(_elem[lo], _elem[mi]);
    if (_elem[mi] < _elem[hi]) swap_data(_elem[mi], _elem[hi]);
    return hi;
}
```

**2. queue**
```cpp
#include <iostream>
using namespace std;
template <class T>
struct listNode {
    T data;
    listNode<T>* pred;
    listNode<T>* succ;
    listNode(const T& d): data(d), pred(NULL), succ(NULL) {}
    void insertAsPred(listNode<T>*);
};

template <class T>
class queue {
private:
    int rank;
    listNode<T>* header;
    listNode<T>* trailer;
public:
    queue();
    ~queue() { clear(); }
    void clear();
    bool empty() { return rank == 0; }
    int size() { return rank; }
    void enqueue(const T&);
    T dequeue();
    T& front() { return header->succ->data; }
};

template <class T>
void queue<T>::enqueue(const T& d) {
    trailer->insertAsPred(new listNode<T>(d));
    ++rank;
}

template <class T>
T queue<T>::dequeue() {
    listNode<T>* p = header->succ;
    header->succ = p->succ;
    p->succ->pred = header;
    T d = p->data;
    delete p;
    --rank;
    return d;
}

template <class T>
queue<T>::queue() {
    rank = 0;
    header = new listNode<T>(T());
    trailer = new listNode<T>(T());
    header->succ = trailer;
    trailer->pred = header;
}

template <class T>
void queue<T>::clear() {
    listNode<T>* bawk = header;
    listNode<T>* forw = NULL;
    while (bawk) {
        forw = bawk->succ;
        delete bawk;
        bawk = forw;
    }
}

template <class T>
void listNode<T>::insertAsPred(listNode<T>* p) {
    p->succ = this;
    p->pred = pred;
    pred->succ = p;
    pred = p;
}
```

## BinTree, BST

**1. BinTree**

```cpp
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
    BinNode<T>* _root_p;
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
    ~BinTree() { if (_size > 0) remove(_root_p); }
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
    _root_p = new BinNode<T>(T());
    _root = new BinNode<T>(e);
    _root_p->lChild = _root;
    _root->parent = _root_p;
    _size = 1;
}

template <class T>
BinTree<T>::BinTree(const BinTree<T>& temp) {
    _size = temp._size;
    _root_p = copyNode(temp._root_p);
    _root = _root_p->lChild;
}

template <class T>
BinTree<T>::BinTree(BinNode<T>* r): _size(0), _root(NULL) {
    if (!(r->parent)) {
        _size = r->size();
        _root = r;
        _root_p = new BinNode<T>(T());
        _root_p->lChild = _root;
        _root->parent = _root_p;
    }
}

template <class T>
void BinTree<T>::creatRoot(const T& e) {
    if (!empty()) remove(_root_p);
    _root = new BinNode<T>(e);
    _size = 1;
    if (!_root_p)_root_p = new BinNode<T>(T());
    _root_p->lChild = _root;
    _root->parent = _root_p;
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

```

**2. BST**

```cpp
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
        if (_hot->lChild == target) _hot->lChild = target->lChild;
        else _hot->rChild = target->lChild;
        target->lChild->parent = _hot;
        delete target;
    }
    else if (target->rChild) {
        if (_hot->lChild == target) _hot->lChild = target->rChild;
        else _hot->rChild = target->rChild;
        target->rChild->parent = _hot;
        delete target;
    }
    else {
        if (_hot->rChild == target) _hot->rChild = NULL;
        else _hot->lChild = NULL;
        delete target;
    }
    --_size;
    _root = _root_p->lChild;
    return _hot;
}

template <class T>
bool BST<T>::remove(const T& e) {
    BinNode<T>* target = search(e);
    updateHeightAbove(_hot);
    return removeAt(target);
}
```

##Graph

**1. GraphMatrix**

```cpp
#include "../Vector/Vector.h"
#include "../Stack/Stack.h"
#include "../Queue/Queue.h"

typedef enum { UNDISCOVERED, DISCOVERED, VISITED } VStatus;
typedef enum { UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD } EStatus;


//1.1 Vertex
template <class Tv>
struct Vertex {
    Tv data;
    int inDegree, outDegree;
    VStatus status;
    int dTime, fTime;
    int parent;
    int priority;
    Vertex(const Tv& d):
        data(d), inDegree(0), outDegree(0), status(UNDISCOVERED),
        dTime(-1), fTime(-1), parent(-1), priority(INT_MAX) {}
};

//1.2 Edge
template <class Te>
struct Edge{
    Te data;
    int weight;
    EStatus status;
    Edge(const Te& d, int w):
        data(d), weight(w), status(UNDETERMINED) {}
};

//2. Graph
template <class Tv, class Te>
class Graph {
private:
    void reset();
    void BFS(int, int&); //(连通域)广搜算法
    void DFS(int, int&); //(连通域)深搜算法
  //Unfinished
    void BCC(int, int&, Stack<int>&); //(连通域)基于DFS的双连通分量分解算法
    bool Tsort(int, int&, Stack<Tv>*); //(连通域)基于DFS的拓扑排序算法
    template <class PU> void PFS(int, PU); //(连通域)优先级搜索算法
protected:
    int _n, _e; //Vertex, Edge.
public:
//  Vertex:
    int n() { return _n; }
    virtual int insert(const Tv&) = 0;
    virtual Tv remove(int) = 0; //Delete Vertex and Edge connected.
    virtual Tv& vertex(int) = 0;
    virtual int inDegree(int) = 0; //inDegree of a vertex.
    virtual int outDegree(int) = 0;
    virtual int firstNbr(int) = 0; //First neighbor of a vertex.
    virtual int nextNbr(int, int) = 0; //Next(j next) neighbor of a vertex.
    virtual VStatus& status(int) = 0;
    virtual int& dTime(int) = 0;
    virtual int& fTime(int) = 0;
    virtual int& parent(int) = 0;
    virtual int& priority(int) = 0; //顶点v在遍历树中的优先级
//  Edge:
    int e() { return _e; }
    virtual bool exists(int, int) = 0;
    virtual void insert(const Te&, int, int, int) = 0; //Insert an Edge(data, weight) between vertex i and j.
    virtual Te remove(int, int) = 0;
    virtual EStatus& status(int, int) = 0;
    virtual Te& edge(int, int) = 0;
    virtual int& weight(int, int) = 0;
//  Algorithm
    void bfs(int);
    void dfs(int);
  //Unfinished
    void bcc(int);
    Stack<Tv>* tSort(int);
    void prim(int); //最小支撑树Prim算法
    void dijkstra(int); //最短路径Dijkstra算法
    template <class PU> void pfs(int, PU); //优先级搜索框架
};

//3. GraphMatrix
template <class Tv, class Te>
class GraphMatrix: public Graph<Tv, Te> {
private:
    Vector<Vertex<Tv>> V;
    Vector<Vector<Edge<Te>*>> E;
public:
    GraphMatrix() { _n = _e = 0; }
    ~GraphMatrix();
//  Vertex
    virtual Tv& vertex(int i) { return V[i].data; }
    virtual int inDegree(int i) { return V[i].inDegree; }
    virtual int outDegree(int i) { return V[i].outDegree; }
    virtual VStatus& status(int i) { return V[i].status; }
    virtual int& dTime(int i) { return V[i].dTime; }
    virtual int& fTime(int i) { return V[i].fTime; }
    virtual int& parent(int i) { return V[i].parent; }
    virtual int& priority(int i) { return V[i].priority; }
    virtual int firstNbr(int);
    virtual int nextNbr(int, int);
    virtual int insert(const Tv&);
    virtual Tv remove(int);
//  Edge
    virtual bool exists(int, int);
    virtual EStatus& status(int, int);
    virtual Te& edge(int, int);
    virtual int& weight(int, int);
    virtual void insert(const Te&, int, int, int);
    virtual Te remove(int, int);
};

//1. Graph
template <class Tv, class Te>
void Graph<Tv, Te>::reset() {
    for (int i = 0; i < _n; ++i) {
        status(i) = UNDISCOVERED;
        dTime(i) = fTime(i) = parent(i) = -1;
        priority(i) = INT_MAX;
        for (int j = 0; j < n; ++j)
            if (exists(i, j)) status(i, j) = UNDETERMINED;
    }
}

template <class Tv, class Te>
void Graph<Tv, Te>::BFS(int v, int& _clock) {
    Queue<int> q;
    q.enqueue(v);
    status(v) = DISCOVERED;
    while (!q.empty()) {
        int v = q.dequeue();
        dTime(v) = ++_clock;
        /*Do something...*/
        for (int u = firstNbr(v); u > -1; u = nextNbr(v, u)) {
            if (UNDISCOVERED == status(u)) {
                status(u) = DISCOVERED;
                q.enqueue(u);
                status(v, u) = TREE;
                parent(u) = v;
            } else
                status(v, u) = CROSS;
        }
        status(v) = VISITED;
    }
}

template <class Tv, class Te>
void Graph<Tv, Te>::bfs(int v) {
    reset();
    int s = v;
    int _clock = 0;
    do {
        if (UNDISCOVERED == status(s))
            BFS(s, _clock);
        s = (s + 1) % _n;
    } while (v != s);
}

template <class Tv, class Te>
void Graph<Tv, Te>::DFS(int v, int& _clock) {
    dTime(v) = ++_clock;
    status(v) = DISCOVERED;
    for (int u = firstNbr(v); u > -1; u = nextNbr(v, u)) {
        if (UNDISCOVERED == status(u)) {
            status(v, u) = TREE;
            parent(u) = v;
            DFS(u, _clock);
        } else if (DISCOVERED == status(u))
            status(v, u) = BACKWARD;
        else
            status(v, u) = (dTime(v) < dTime(u))? FORWARD: CROSS;
    }
    /*Do something...*/
    status(v) = VISITED;
    fTime = ++_clock;
}

template <class Tv, class Te>
void Graph<Tv, Te>::dfs(int v) {
    reset();
    int _clock = 0;
    int s = v;
    do {
        if (UNDISCOVERED == status(s))
            DFS(s, _clock);
        s = (s + 1) % _n;
    } while (s != v);
}

//2. GraphMatrix
template <class Tv, class Te>
GraphMatrix<Tv, Te>::~GraphMatrix() {
    for (int i = 0; i < _n; ++i) {
        for (int j = 0; j < _n; ++j)
            delete E[i][j];
    }
}

//2.1 Vertex
template <class Tv, class Te>
int GraphMatrix<Tv, Te>::nextNbr(int i, int j) {
    while (--j >= 0) {
        if (exists(i, j)) return j;
    }
    return -1;
}

template <class Tv, class Te>
int GraphMatrix<Tv, Te>::firstNbr(int i) {
    return nextNbr(i, _n);
}

template <class Tv, class Te>
int GraphMatrix<Tv, Te>::insert(const Tv& d) {
    for (int i = 0; i < n; ++i)
        E[i].push_back(NULL);
    ++_n;
    E.push_back(Vector<Edge<Te>*>(_n, NULL));
    V.push_back(Vertex<Tv>(d));
}

template <class Tv, class Te>
Tv GraphMatrix<Tv, Te>::remove(int i) {
    for (int j = 0; j < _n; ++j) {
        if (exists(i, j)) {
            delete E[i][j];
            V[j].inDegree -= 1;
        }
    }
    E.remove(i);
    --_n;
    for (int j = 0; j < _n; ++j) {
        if (exists(j, i)) {
            delete E[j][i];
            E[j].remove(i);
            V[j].outDegree -= 1;
        } 
    }
    Tv tmp = vertex(i);
    V.remove(i);
    return tmp;
}


//2.2 Edge
template <class Tv, class Te>
bool GraphMatrix<Tv, Te>::exists(int i, int j) {
    return ((i < _n) && (i > -1)) && ((j < _n) && (j > -1))
           && E[i][j] != NULL;
}

template <class Tv, class Te>
Tv& GraphMatrix<Tv, Te>::edge(int i, int j) {
    if (exists(i, j)) return E[i][j]->data;
}

template <class Tv, class Te>
EStatus& GraphMatrix<Tv, Te>::status(int i, int j) {
    if (exists(i, j)) return E[i][j]->status;
}

template <class Tv, class Te>
int& GraphMatrix<Tv, Te>::weight(int i, int j) {
    if (exists(i, j)) return E[i][j]->weight;
}

template <class Tv, class Te>
void GraphMatrix<Tv, Te>::insert(const Te& d, int w, int i, int j) {
    if (exists(i, j)) return;
    E[i][j] = new Edge<Te>(d, w);
    V[i].outDegree += 1;
    V[j].inDegree += 1;
    _e++;
}

template <class Tv, class Te>
Te GraphMatrix<Tv, Te>::remove(int i, int j) {
    if (exists(i, j)) {
        Te tmp = edge(i, j);
        delete E[i][j];
        V[i].outDegree -= 1;
        V[j].inDegree -= 1;
        --_e;
        return tmp;
    }
}
```

##Heap

```cpp
#include "PQueue.h"
#include "../Vector/Vector.h"

template <class T>
class PQ_ComplHeap: public PQueue<T>, public Vector<T> {
protected:
    int percolateDown(int, int); //下滤
    int percolateUp(int); //上滤
    void heapify(int); //Floyd建堆算法
public:
    PQ_ComplHeap(): Vector() {}
    PQ_ComplHeap(T* a, int n) { copyForm(a, 0, n); heapify(n); }
    virtual void insert(const T&);
    virtual T& getMax() { return _elem[0]; }
    virtual T delMax();
};

template <class T>
void heap_sort(T*, int);

template <class T>
void PQ_ComplHeap<T>::insert(const T& e) {
    push_back(e);
    percolateUp(_rank - 1);
}

template <class T>
T PQ_ComplHeap<T>::delMax() {
    T max = _elem[0];
    swap_data(_elem[0], _elem[_rank - 1]);
    --_rank;
    percolateDown(0, _rank);
    return max;
}

template <class T>
void PQ_ComplHeap<T>::heapify(int n) {
    for (int i = (n / 2) - 1; i >= 0; --i)
        percolateDown(i, n);
}

template <class T>
int PQ_ComplHeap<T>::percolateUp(int i) {
    while (i > 0) {
        int j = (i - 1) / 2;
        if (_elem[j] < _elem[i]) {
            swap_data(_elem[j], _elem[i]);
            i = j;
        }
        else break;
    }
    return i;
}

template <class T>
int PQ_ComplHeap<T>::percolateDown(int i, int n) {
    while (2 * i + 2 < n) {
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        if (_elem[l] < _elem[r]) {
            if (_elem[i] < _elem[r]) {
                swap_data(_elem[i], _elem[r]);
                i = r;
            }
            else break;
        }
        else {
            if (_elem[i] < _elem[l]) {
                swap_data(_elem[i], _elem[l]);
                i = l;
            }
            else break;
        }
    }
    if (2 * i + 1 < n && _elem[i] < _elem[2 * i + 1]) {
        swap_data(_elem[i], _elem[2 * i + 1]);
        i = 2 * i + 1;
    }
    return i;
}

template <class T>
void Vector<T>::heap_sort() {
    PQ_ComplHeap<T> heap(_elem, _rank);
    int hi = _rank;
    while (!heap.empty())
        _elem[--hi] = heap.delMax();
}

template <class T>
void heap_sort(T* a, int n) {
    PQ_ComplHeap<T> heap(a, n);
    while (!heap.empty())
        a[--n] = heap.delMax();
}
```

##List
```cpp

#include <iostream>
template <class T>
struct listNode {
    T data;
    listNode<T>* pred;
    listNode<T>* succ;
    listNode() {}
    listNode(const T& e, listNode<T>* p = NULL, listNode<T>* s = NULL)
    : data(e), pred(p), succ(s) {}
    void insertAsPred(listNode<T>*);
    void insertAsSucc(listNode<T>*);
};

template <class T>
class List {
private:
    int _size;
    listNode<T>* header;  //Invisible, rank[-1]
    listNode<T>* trailer; //Invisible, rank[_size]
protected:
    void init(); //Creat header and trailer.
    void del();  //Delete all list nodes include header and trailer.
    void selectionSort(listNode<T>*, int); //Sort(first(), _size);
    void insertionSort(listNode<T>*, int); //Sort(first(), _size);
    listNode<T>* selectMax(listNode<T>*, int);
    void swapData(listNode<T>*, listNode<T>*);
    void transNode(listNode<T>*, listNode<T>*);
public:
    List() {init();}
    List(List<T>&); //Copy constructor.
    List<T>& operator=(List<T>&);
    ~List() {del();}
    void show(); //Display all nodes.
    listNode<T>* first() const {if (_size <= 0) return NULL; return header->succ;} //First visible node.
    listNode<T>* last() const {if (_size <= 0) return NULL; return trailer->pred;} //Last visible node.
    T& operator[](int); //Low efficiency. Call by L[i].
    int size() const {return _size;}
    bool empty() const {return _size <= 0;}
    T insertAsFirst(const T&); //Insert as the first visible node in the list.
    T insertAsLast(const T&); //Insert as the last visible node in the list.
    T remove(int); //Delete the rank[i] node.
    T remove(listNode<T>*); //Delete a special node.
    int deduplicate(); //Uniquify *disordered* list.
    int uniquify(); //Uniquify *ordered* list.
    int disordered(); //The number of disordered pair.
    listNode<T>* find(const T&, int, listNode<T>*); //Find data e in n predectors in front of a special node.
    listNode<T>* find(const T&); //*Disordered* Find data e in all list.
    listNode<T>* search(const T&, int, listNode<T>*); //*Ordered* Find the last one which <= target in a interval.
    listNode<T>* search(const T&); //*Ordered* Find the last one which <= target in the whole list.
    listNode<T>* insertPred(const T&, listNode<T>*); //Insert a node in front of a special node.
    listNode<T>* insertSucc(const T&, listNode<T>*); //Insert a node behind a special node.
    void sort(); //**Selection sort.**
};

template <class T>
void List<T>::init() {
    header = new listNode<T>;
    trailer = new listNode<T>;
    header->succ = trailer;
    header->pred = NULL;
    trailer->pred = header;
    trailer->succ = NULL;
    _size = 0;
}

template <class T>
List<T>::List(List<T>& temp) {
    init();
    if (temp.empty())
        return;
    listNode<T>* p = temp.first();
    while (p != temp.trailer) {
        insertAsLast(p->data);
        p = p->succ;
    }
}

template <class T>
List<T>& List<T>::operator=(List<T>& temp) {
    if (!empty()) {
        del();
        init();
    }
    if (temp.empty())
        return *this;
    listNode<T>* p = temp.first();
    while (p != temp.trailer) {
        insertAsLast(p->data);
        p = p->succ;
    }
    return *this;
}

template <class T>
T& List<T>::operator[](int i) {
    listNode<T> * val = header;
    while (i >= 0 && val != NULL) {
        val = val->succ;
        --i;
    }
    return val->data;
}

template <class T>
T List<T>::insertAsFirst(const T& val) {
    listNode<T> * in = new listNode<T>(val);
    header->insertAsSucc(in);
    ++_size;
    return val;
}

template <class T>
T List<T>::insertAsLast(const T& val) {
    listNode<T> * in = new listNode<T>(val);
    trailer->insertAsPred(in);
    ++_size;
    return val;
}

template <class T>
void List<T>::del() {
    listNode<T>* _beh = header;
    listNode<T>* _fro = header->succ;
    while (_fro != NULL) {
        delete _beh;
        _beh = _fro;
        _fro = _fro->succ;
    }
    delete _beh;
}

template <class T>
void List<T>::show() {
    if (empty())
        return;
    listNode<T>* i = first();
    while (i != trailer) {
        std::cout << i->data << " ";
        i = i->succ;
    }
    std::cout << std::endl;
}

template <class T>
listNode<T>* List<T>::find(const T& e, int n, listNode<T>* p) {
    while (n > 0) {
        p = p->pred;
        if (p->data == e)
            return p;
        --n;
    }
    return NULL;
}

template <class T>
listNode<T>* List<T>::find(const T& e) {
    return find(e, _size, trailer);
}

template <class T>
listNode<T>* List<T>::insertPred(const T& e, listNode<T>* p) {
    listNode<T>* val = new listNode<T>(e);
    p->insertAsPred(val);
    ++_size;
    return val;
}

template <class T>
listNode<T>* List<T>::insertSucc(const T& e, listNode<T>* p) {
    listNode<T>* val = new listNode<T>(e);
    p->insertAsSucc(val);
    ++_size;
    return val;
}

template <class T>
T List<T>::remove(int i) {
    listNode<T>* p = first();
    while (i > 0 && p != last()) {
        p = p->succ;
        --i;
    }
    if (0 == i) {
        T temp = p->data;
        p->pred->succ = p->succ;
        p->succ->pred = p->pred;
        delete p;
        --_size;
        return temp;
    }   
}

template <class T>
T List<T>::remove(listNode<T>* p) {
    if (p != header && p != trailer) {
        T temp = p->data;
        p->pred->succ = p->succ;
        p->succ->pred = p->pred;
        delete p;
        --_size;
        return temp;
    }
}

template <class T>
int List<T>::deduplicate() {
    listNode<T>* p = last();
    listNode<T>* judge = NULL; 
    int n = _size - 1;
    while (n > 0) {
        judge = find(p->data, n, p);
        if (judge) {
            remove(judge);
            --n;
        }
        else {
            p = p->pred;
            --n;
        }
    }
    return _size;
}

template <class T>
int List<T>::disordered() {
    int count = 0;
    listNode<T>* p = first();
    while (p != last()) {
        if (p->succ->data < p->data)
            ++count;
        p = p->succ;
    }
    return count;
}

template <class T> 
int List<T>::uniquify() {
    if (_size < 2) return _size;
    listNode<T>* p = first();
    listNode<T>* q = p->succ;
    while (p != last()) {
        if(p->data == q->data) {
            remove(q);
            q = p->succ;
        }
        else {
            p = q;
            q = p->succ;
        }
    }
    return _size;
}

template <class T>
listNode<T>* List<T>::search(const T& e, int n, listNode<T>* p) {
    while (n > 0) {
        p = p->pred;
        if (p->data <= e)
            return p;
        --n;
    }
    return p->pred;
}

template <class T>
listNode<T>* List<T>::search(const T& e) {
    return search(e, _size, trailer);
}

template <class T>
void List<T>::selectionSort(listNode<T>* p, int n) {
    listNode<T>* head = p->pred;
    listNode<T>* trail = p;
    for (int i = 0; i < n; ++i)
        trail = trail->succ;
    while (n > 1) {
        swapData(selectMax(head, n), trail->pred);
        trail = trail->pred;
        --n;
    }
}

template <class T>
listNode<T>* List<T>::selectMax(listNode<T>* p, int n) {
    T max = p->succ->data;
    listNode<T>* temp = p->succ;
    while (n > 0) {
        p = p->succ;
        if (max < p->data) {
            temp = p;
            max = p->data;
        }
        --n;
    }
    return temp;
}

template <class T>
void List<T>::swapData(listNode<T>* a, listNode<T>* b) {
    T swap = a->data;
    a->data = b->data;
    b->data = swap;
}

template <class T>
void List<T>::insertionSort(listNode<T>* p, int n) {
    if (n < 2) return;
    listNode<T>* now = p->succ;
    listNode<T>* pos = NULL;
    for (int i = 1; i < n; ++i) {
        pos = search(now->data, i, now);
        listNode<T>* del = now;
        now = now->succ;
        transNode(del, pos);
    }
}

template <class T>
void List<T>::transNode(listNode<T>* n, listNode<T>* pos) {
    n->succ->pred = n->pred;
    n->pred->succ = n->succ;
    n->pred = pos;
    n->succ = pos->succ;
    n->succ->pred = n;
    pos->succ = n;
}

template <class T>
void List<T>::sort() {
    //selectionSort(first(), _size);
    insertionSort(first(), _size);
}

//listNode
template <class T>
void listNode<T>::insertAsPred(listNode<T>* e) {
    e->pred = pred;
    e->succ = this;
    pred->succ = e;
    pred = e;
}

template <class T>
void listNode<T>::insertAsSucc(listNode<T>* e) {
    e->succ = succ;
    e->pred = this;
    succ->pred = e;
    succ = e;
}
```