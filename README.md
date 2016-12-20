# Learning

---

1. Cpp：C++语法。
2. DSA：Data Structure & Algorithm 数据结构与算法

---

##Tips: 内存泄漏检测方法(VS)：

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