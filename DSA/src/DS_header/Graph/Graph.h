#ifndef GRAPH_H
#define GRAPH_H
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

#endif