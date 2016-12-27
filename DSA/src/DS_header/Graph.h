#ifndef GRAPH_H
#define GRAPH_H
#include "Stack.h"
#include "Vector.h"

typedef enum { UNDISCOVERED, DISCOVERED, VISITED } VStatus;
typedef enum { UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD } EType;

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

template <class Te>
struct Edge{
    Te data;
    int weight;
    EStatus status;
    Edge(const Te& d, int w):
        data(d), weight(w), status(UNDETERMINED) {}
};

template <class Tv, class Te>
class Graph {
private:
    void reset();
    void BFS(int, int&); //(连通域)广搜算法
    void DFS(int, int&); //(连通域)深搜算法
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
    virtual EType& type(int, int) = 0;
    virtual Te& edge(int, int) = 0;
    virtual int& weight(int, int) = 0;
//  Algorithm
    void bfs(int);
    void dfs(int);
    void bcc(int);
    Stack<Tv>* tSort(int);
    void prim(int); //最小支撑树Prim算法
    void dijkstra(int); //最短路径Dijkstra算法
    template <class PU> void pfs(int, PU); //优先级搜索框架
};

template <class Tv, class Te>
class GraphMatrix: public Graph<Tv, Te> {
private:
    Vector<Vertex<Tv>> V;
    Vector<Vector<Edge<Te>*>> E;
};

#endif

//1. Graph
template <class Tv, class Te>
void Graph<Tv, Te>::reset() {
    for (int i = 0; i < _n; ++i) {
        status(i) = UNDISCOVERED;
        dTime(i) = fTime(i) = parent(i) = -1;
        priority(i) = INT_MAX;
        for (int j = 0; j < n; ++j)
            if (exist(i, j)) type(i, j) = UNDETERMINED;
    }
}

//2. GraphMatrix