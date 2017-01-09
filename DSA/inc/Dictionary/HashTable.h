#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "../Entry/Entry.h"
#include "Dictionary.h"
#include <iostream>
using namespace std;

typedef enum { EMPTY, FULL, DEL } EStatus;

template <class K, class V, class S = EStatus>
class HashTable: public Dictionary<K, V> {
protected:
    Entry<K, V, S>** ht; //词条指针
    int M;
    int N;
    int hash(K);
    void rehash();
    Entry<K, V, S>* find(K);
public:
    HashTable(int n); //大致规模
    ~HashTable();
    virtual int size() const { return N; }
    virtual bool put(K, V);
    virtual V* get(K);
    virtual bool remove(K);
};

template <class K, class V, class S>
int HashTable<K, V, S>::hash(K k) {
    int key = k;
    key = (key * (4 % M) + 7) % M;
    return key;
}

template <class K, class V, class S>
void HashTable<K, V, S>::rehash() {}

template <class K, class V, class S>
HashTable<K, V, S>::HashTable(int n) {
    while (n % 4 != 3 || (n / 4) % 3 == 0) ++n;
    ht = new Entry<K, V, S>*[n];
    for (int i = 0; i < n; ++i) ht[i] = NULL;
    M = n;
    N = 0;
}

template <class K, class V, class S>
HashTable<K, V, S>::~HashTable() {
    for (int i = 0; i < M; ++i) {
        if (ht[i]) delete ht[i];
    }
    delete ht;
}

template <class K, class V, class S>
bool HashTable<K, V, S>::put(K k, V v) {
    if (N >= M) return false;
    int key = hash(k);
    int count = 2;
    int n_key = key;
    while (ht[n_key]) {
        if (count % 2 == 0) n_key = (key + ((count / 2) * (count / 2))) % M;
        else {
            n_key = key - ((count / 2) * (count / 2));
            while (n_key < 0) n_key += M;
        }
        ++count;
    }
    if (!ht[n_key]) {
        ht[n_key] = new Entry<K, V, S>(k, v);
        ht[n_key]->status = FULL;
        return true;
        ++N;
    }
    else return false;
}

template <class K, class V, class S>
V* HashTable<K, V, S>::get(K k) {
    Entry<K, V, S>* ep = find(k);
    if (ep) return &(ep->value);
    return NULL;
}

template <class K, class V, class S>
bool HashTable<K, V, S>::remove(K k) {
    Entry<K, V, S>* ep = find(k);
    if (!ep) return false;
    ep->status = DEL;
    return true;
}

template <class K, class V, class S>
Entry<K, V, S>* HashTable<K, V, S>::find(K k) {
    int key = hash(k);
    int count = 2;
    int n_key = key;
    if (!ht[n_key]) return NULL;
    while (ht[n_key] && (ht[n_key]->status == DEL || ht[n_key]->key != k)) {
        if (count % 2 == 0) n_key = (key + ((count / 2) * (count / 2))) % M;
        else {
            n_key = key - ((count / 2) * (count / 2));
            while (n_key < 0) n_key += M;
        }
        ++count;
    }
    if (ht[n_key] && ht[n_key]->key == k) return ht[n_key];
    return NULL;
}


#endif