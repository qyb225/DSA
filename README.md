# DSA_CPP

---

1. Cpp��C++�﷨��
2. DSA��Data Structure & Algorithm ���ݽṹ���㷨

---

##Tips1: �ڴ�й©��ⷽ��(VS)��

```cpp
#define CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
/*
Memory leaks test in VS.
If memory doesn't release finally, will output warn like:

Detected memory leaks!
Dumping objects ->
{144} normal block at 0x010DE460, 40 bytes long.
Data: <   > CD CD CD CD CD CD CD CD CD CD
*/

void func();
int main() {
    func();
    _CrtDumpMemoryLeaks();
    return 0;
}

void func() {
    int* p = new int[10];
    //delete[] p;
}
```

##Tips2: C++11 lambda���ʽ���溯������
```cpp
//1. Function object
template <class T>
class visit {
public:
    void operator()(T e) { cout << e << " "; }
};

//2. Lambda expression
template <class T>
auto visit = [](T e) { cout << ++e << " "; };
```
���߹�������

**E.g.**
```cpp
//����BinTree�����������
template<class T>
class BinTree {
//...
public:
    template <class VST> void travePre(VST & visit); //Need a function object.
//...
};

template<class T>
class BST: public BinTree<T> {
//...
};

```

**1. lambda���ʽ���ã�**
```cpp
#include <iostream>
#include "BST.h"

template <class T>
auto visit = [](T e) { std::cout << e << " "; };

int main() {
    BST<int> t; //Binary Search Tree.
    t.insert(5);
    t.insert(7);
    t.traveIn(visit<int>); //No brackets ()
    return 0;
}
```

**2. ��ͳ����������ã�**
```cpp
#include <iostream>
#include "BST.h"

template <class T>
class visit {
public:
    void operator()(T e) { std::cout << e << " "; }
};

int main() {
    BST<int> t; //Binary Search Tree.
    t.insert(5);
    t.insert(7);
    t.traveIn(visit<int>()); 
    return 0;
}

```