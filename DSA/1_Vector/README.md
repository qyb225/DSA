#1. Vector

---

PS，基础数据结构为T

##API介绍及实现思路：

1. 构造函数：

* **Vector(n);**
指定大小构造，不进行元素初始化。
* **Vector(T* t, int lo, int hi);**
指定T数组的一段区间构造，此时vector最大小为原区间2倍。

2. **void expand();**
若此时 vector 已经装满，则进行扩容。
3. **"=", "[ ]"** 仍然可以使用。
4. **void push_back(T num);**
在尾部添加元素num，根据情况扩大vector.
5. **int insert(int i, T num);**
在原下标 i 之前添加元素 num，使vector现在下标i对应 num 元素。先后移，再插入。
6. **int remove(int i);**
删除下标 i 对应的元素。实现左移即可。
7. **int remove(int i, int j);**
删除下标[i, j)对应的元素。实现需要直接跨越空间复制，不能一个一个调用remove(int i)
8. **int find(T target);**
在vector中从后向前检索 target，未找到则返回 -1.
9. **int deduplicate();**
在无序 vector 中剔除重复元素，循环，查找，删除。
10. **void sort();**
排序，采用Bubble sort 和 Merge sort 两种算法。
11. **int search(T target);**
适用于**有序向量**，采用二分查找算法，如果 target **存在**，返回**最后一个**target的下标；如果 target **不存在**，返回**比 target 小**的最近元素。
12. **int uniquify();**
适用于**有序向量**，一遍循环，与前一个不同则直接往后复制即可。

---
