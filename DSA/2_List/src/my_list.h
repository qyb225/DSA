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
    void init(); //Creat header and trailer.
    void del();  //Delete all list nodes include header and trailer.
    void selectionSort(listNode<T>*, int); //Sort(first(), _size);
    void insertionSort(listNode<T>*, int); //Sort(first(), _size);
    listNode<T>* selectMax(listNode<T>*, int);
    void swapData(listNode<T>*, listNode<T>*);
    void transNode(listNode<T>*, listNode<T>*);
public:
    myList() {init();}
    myList(myList<T>&); //Copy constructor.
    myList<T>& operator=(myList<T>&);
    ~myList() {del();}
    void show(); //Display all nodes.
    listNode<T>* first() const {if (_size <= 0) return NULL; return header -> succ;} //First visible node.
    listNode<T>* last() const {if (_size <= 0) return NULL; return trailer -> pred;} //Last visible node.
    T& operator[](int); //Low efficiency. Call by L[i].
    int size() const {return _size;}
    bool empty() const {return _size <= 0;}
    T insertAsFirst(T); //Insert as the first visible node in the list.
    T insertAsLast(T); //Insert as the last visible node in the list.
    T remove(int); //Delete the rank[i] node.
    T remove(listNode<T>*); //Delete a special node.
    int deduplicate(); //Uniquify *disordered* list.
    int uniquify(); //Uniquify *ordered* list.
    int disordered(); //The number of disordered pair.
    listNode<T>* find(T, int, listNode<T>*); //Find data e in n predectors in front of a special node.
    listNode<T>* find(T); //*Disordered* Find data e in all list.
    listNode<T>* search(T, int, listNode<T>*); //*Ordered* Find the last one which <= target in a interval.
    listNode<T>* search(T); //*Ordered* Find the last one which <= target in the whole list.
    listNode<T>* insertPred(T, listNode<T>*); //Insert a node in front of a special node.
    listNode<T>* insertSucc(T, listNode<T>*); //Insert a node behind a special node.
    void sort(); //**Selection sort.**
};

#endif