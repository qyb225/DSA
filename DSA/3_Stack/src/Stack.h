#ifndef STACK_H
#define STACK_H
template <class T>
class Stack {
private:
    int _rank;
    int _capacity;
    T* _elem;
protected:
    void expand();
public:
    Stack() {_rank = 0; _capacity = 8; _elem = new T[_capacity];}
    Stack(Stack<T>&);
    Stack<T>& operator=(Stack<T>&);
    ~Stack() {delete [] _elem;}
    bool empty();
    void push(T);
    int size();
    T& top();
    T pop();
};

#endif