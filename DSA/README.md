# 数据结构与算法
---

##1. Vector


PS，基础数据结构为T

##API介绍及实现思路：

1. 构造函数：
① **Vector(n);**
指定大小构造，不进行元素初始化。
② **Vector(T* t, int lo, int hi);**
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

##2. list


##API介绍及实现思路：

1. **List();**
2. **first() and last();**
返回首/末元素。
3. **size();**
4. **empty();**
5. **T insertAsFirst/Last(T);**
在首/末插入节点T
6. **remove(i) / remove(node_pointer)** 
删除某节点（Rank i 或 地址）
7. **int deduplicate();**
【无序】链表去重。
8. **int uniquify();**
【有序】链表去重。
9. **find(e, n, node_pointer); or find(e);**
无序链表查找特定节点前 n 个节点值为 e 的节点。或所有链表中最后一个值为 e 的节点地址。
10. **search(e, n, node_pointer) or search(e);**
查找不大于 e 的最后一个节点。
11. **insertPred(e, p); or insertSucc(e, p)**
在 p 节点前插入值为 e 的节点。

---

##3. Stack


##API介绍及实现思路：

1. **Stack();**
2. **bool empty();**
栈是否为空。
3. **void push(T e);**
元素 e 压栈。
4. **T pop();**
弹出顶部元素。
5. **T& top();**
返回顶部元素引用。
6. **int size();**
栈内元素。

---

