# Learning

---

1. Cpp��C++�﷨��
2. DSA��Data Structure & Algorithm ���ݽṹ���㷨

---

##Tips: �ڴ�й©���Debug������

```cpp
#define CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
/*
Memory leaks test in VS.
If memory doesn't release finally, will output warn like:

Detected memory leaks!
normal block at 0x00341A38, 40 bytes long.
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