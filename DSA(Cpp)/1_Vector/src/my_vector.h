#ifndef MY_VECTOR_H
#define MY_VECTOR_H
template <class T>
class my_vector {
private:
    int _rank;
    int _capacity;
    T* _elem;
protected:
    void copyForm(T* t, int lo, int hi);
    void bubble_sort();
    void merge_sort();
public:
    my_vector(int c = 8) {_elem = new T[c]; _rank = 0; _capacity = c;}
    my_vector(T* t, int lo, int hi) {copyForm(t, lo, hi);}
    my_vector<T>& operator= (const my_vector<T> &);
    void expand();
    ~my_vector() {if(_elem) delete [] _elem;}
    void show();
    void push_back(T);
    int insert(int, T);
    int size() const {return _rank;}
    int remove(int, int);
    int remove(int);
    int find(T, int, int);
    int find(T);
    int search(T, int, int);
    int search(T); // 1. e exist, return last one. 2. e isn't exist, return one smaller than e.
    T& operator[] (int r) const;
    int deduplicate();
    //void traverse(VST &); //函数对象
    int disordered(); //disordered
    int uniquify(); //ordered
    void sort();
};

#endif