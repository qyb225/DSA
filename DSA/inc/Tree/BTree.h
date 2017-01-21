#ifndef BTREE_H
#define BTREE_H
#include "../Vector/Vector.h"

template <class T>
struct BTNode {
    BTNode<T>* parent;
    Vector<T> key;
    Vector<BTNode<T>*> child;
    BTNode() { parent = NULL; child.push_back(NULL); }
    BTNode(const T& e, BTNode<T>* lc = NULL, BTNode<T>* rc = NULL) {
        key.push_back(e);
        child.push_back(lc);
        child.push_back(rc);
        if (lc) lc->parent = this;
        if (rc) rc->parent = this;
    }
};

template <class T>
class BTree {
protected:
    int _size;  //规模
    int _order; //阶次
    BTNode<T>* _root;
    BTNode<T>* _hot; //search()访问最后非空节点位置
    void solveOverflow(BTNode<T>*);  //因插入而上溢的 分裂 处理
    void solveUnderflow(BTNode<T>*); //因删除而下溢的 合并 处理
};

#endif