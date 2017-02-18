# Data Structure & Algorithm

---

> **inc** - header

> **src** - source (include Tsinghua oj. Programming Assignment)

* Vector
* List
* Stack
* Queue
* Entry
* String
* Tree: BinTree, BST, AVL-Tree, Splay-Tree, B-Tree, RB-Tree
* Graph
* Dictionary: Hash
* Heap: Priority Queue

---

##Tips1: 内存泄漏检测方法(VS)：

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

##Tips2: C++11 lambda表达式代替函数对象：
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
两者功能类似

**E.g.**
```cpp
//对于BinTree的中序遍历：
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

**1. lambda表达式调用：**
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

**2. 传统函数对象调用：**
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
##Tips2: 随机洗牌函数测试BST：

```cpp
#include "BST.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <crtdbg.h>
#define CRTDBG_MAP_ALLOC
using namespace std;

template <class T>
auto visit = [](const T& e) { cout << e << " "; };
void func();
int main() {
    func();
    _CrtDumpMemoryLeaks();

    return 0;
}

void func() {
    BST<int> t;
    
//  Creat random number.
    int a[100], b[100];
    srand((unsigned)time(NULL));
    for (int i = 0; i < 100; ++i) a[i] = i;
    for (int i = 99; i >= 1; --i) swap(a[i], a[rand() % i]);
    for (int i = 0; i < 100; ++i) b[i] = i;
    for (int i = 99; i >= 1; --i) swap(b[i], b[rand() % i]);
    
//  Creat Binary Search Tree.
    t.insert(100); //In order to check root removing.
    for (int i = 0; i < 100; ++i) t.insert(a[i]);
    t.traveIn(visit<int>); //Check
    cout << endl;
    
// Remove and Check.    
    for (int i = 0; i < 100; ++i) {
        t.remove(b[i]);
        if (b[i] % 10 == 0) {
            cout << "Delete " << b[i] << endl;
            t.traveIn(visit<int>);
            cout << endl;
        }
    }
    t.remove(100);
    t.traveIn(visit<int>);
    cout << endl;
}
```