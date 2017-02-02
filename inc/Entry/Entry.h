#ifndef ENTRY_H
#define ENTRY_H

template <class K, class V, class S = int>
struct Entry {
    K key;
    V value;
    S status;
    Entry(K k = K(), V v = v()): key(k), value(v) {}
    Entry(const Entry<K, V>& e): key(e.key), value(e.value) {}
    bool operator<(const Entry<K, V>& e) { return key < e.key; }
    bool operator>(const Entry<K, V>& e) { return key > e.key; }
    bool operator<=(const Entry<K, V>& e) { return key <= e.key; }
    bool operator>=(const Entry<K, V>& e) { return key >= e.key; }
    bool operator==(const Entry<K, V>& e) { return key == e.key; }
    bool operator!=(const Entry<K, V>& e) { return key != e.key; }
};

#endif