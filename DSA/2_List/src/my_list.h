#ifndef MY_LIST_H
#define MY_LIST_H
template <class T>
struct listNode {
    T data;
    listNode<T>* pred;
    listNode<T>* succ;
    listNode() {}
    listNode(T e, listNode<T>* p = NULL, listNode<T>* s = NULL)
    : data(e), pred(p), succ(s) {}
    void insertAsPred(listNode<T>*);
    void insertAsSucc(listNode<T>*);
};

template <class T>
class myList {
private:
    int _size;
    listNode<T>* header;  //Invisible, rank[-1]
    listNode<T>* trailer; //Invisible, rank[_size]
protected:
    void init();
public:
    myList() {init();}
    ~myList();
    void show();
    listNode<T>* first() const {if (_size <= 0) return NULL; return header -> succ;}
    listNode<T>* last() const {if (_size <= 0) return NULL; return trailer -> pred;}
    T& operator[](int); //Low efficiency.
    int size() const {return _size;}
    T insertAsFirst(T);
    T insertAsLast(T);
};


#endif