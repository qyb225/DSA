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
template <class T>
class visit {
public:
    void operator()(T e) { cout << e << " "; }
};

template <class T>
auto visit = [](T e) { cout << ++e << " "; };
```
���߹�������

**E.g.**
```cpp
//����BinTree�����������
class BinTree {
//...
public:
    template <class VST> void travePre(VST & visit);
//...
};
```

**1. lambda���ʽ���ã�**
```cpp
#include <iostream>

template <class T>
auto visit = [](T e) { cout << ++e << " "; };

int main() {
    BST<int> t; //Binary Search Tree.
    t.insert(5);
    t.insert(7);
    t.traveIn(visit<int>); //Difference
    return 0;
}
```

**2. ��ͳ����������ã�**
```cpp
#include <iostream>

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