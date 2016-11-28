#ifndef MY_VECTOR_H
#define MY_VECTOR_H
template <class T>
class my_vector {
private:
    int _rank;
    int _capacity;
    T* _elem;
protected:
    void copyForm(T* t, int lo, int hi); //Copy the array to vector.
    void expand(); //increase _capacity.
    void bubble_sort();
    void merge_sort(int, int); //Complish merge sort algorithm
    void merge(int, int, int); //Complish merge sort algorithm
public:
    my_vector(int c = 8) {_elem = new T[c]; _rank = 0; _capacity = c;}
    my_vector(T* t, int lo, int hi) {copyForm(t, lo, hi);}
    my_vector<T>& operator= (const my_vector<T> &);
    ~my_vector() {if(_elem) delete [] _elem;}
    void show(); //Display the member in vector in one line.
    void push_back(T); //Add a member.
    int insert(int, T); //Add a member in front of i.
    int size() const {return _rank;}
    int remove(int, int); //Remove vector[i, j). A loop: _elem[i++] = _elem[j++]
    int remove(int); //Remove vector[i].
    int find(T, int, int); //disordered
    int find(T);
    int search(T, int, int); //ordered
    int search(T); // 1. e exist, return the last one. 2. e isn't exist, return one smaller than e.
    T& operator[] (int r) const;
    int deduplicate(); //disordered
    //void traverse(VST &); //function object. operator();
    int disordered(); //return the number of disordered pair.
    int uniquify(); //ordered
    void sort();
};

#endif