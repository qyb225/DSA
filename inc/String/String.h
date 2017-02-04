#ifndef STRING_H
#define STRING_H
#include <iostream>
#include <cstring>
using namespace std;

char* Strcpy(char*, const char*);
char* Strcat(char*, const char*);
int matchKMP(const char*, const char*);  //KMP匹配算法
void buildNext(const char*, int*, int);  //构造next[]表

class String {
private:
    int _rank;
    int _capacity;
    char* _elem;
    void copyForm(char*, int, int);
    void expand(int);
public:
    String(int c = 8) { _elem = new char[c]; _rank = 0; _capacity = c; _elem[0] = '\0'; }
    String(char* s) : _elem(NULL) { copyForm(s, 0, strlen(s)); }
    String(char* s, int lo, int hi) : _elem(NULL) { copyForm(s, lo, hi); }
    String(const String&);
    ~String() { if (_elem) delete[] _elem; }
    int size() const { return _rank; }
    char& charAt(int i) { if (i < _rank) return _elem[i]; }
    char& operator[] (int i) { if (i < _rank) return _elem[i]; }
    String substr(int i, int k) { return String(_elem, i, i + k); }
    String substr(int i) { return String(_elem, i, _rank); }
    String prefix(int k) { return String(_elem, 0, k); }               //[0, k)
    String suffix(int k) { return String(_elem, _rank - k, _rank); }   //[n - k, n)
    String& concat(const String&);
    String& erase(int, int);
    String& erase(int i) { _rank = i; _elem[_rank] = '\0'; return *this; }
    bool operator== (const String&);
    String& operator= (const String&);
    String operator+ (const String&);
    String operator+ (const char*);
    String& operator+= (const String& temp) { return concat(temp); }
    String& operator+= (const char*);
    int indexOf(String& temp) { return matchKMP(temp._elem, _elem); } //字符串索引匹配KMP
    int indexOf(const char* p) { return matchKMP(p, _elem); }
    friend ostream& operator<< (ostream&, const String&);
};

char* Strcpy(char* s1, const char* s2) {
    char* ret = s1;
    while ((*s1++ = *s2++) != '\0');
    return ret;
}

char* Strcat(char* s1, const char* s2) {
    char* tmp = s1;
    while (*s1) s1++;
    while ((*s1++ = *s2++) != '\0');
    return tmp;
}

int matchKMP(const char* p, const char* t) {
    int m = strlen(p), j = 0;
    int n = strlen(t), i = 0;
    int* next = new int[m];
    buildNext(p, next, m);
    while (j < m && i < n) {
        if (j < 0 || t[i] == p[j]) {
            ++i;
            ++j;
        }
        else {
            j = next[j];
        }
    }
    delete[] next;
    return (i - j) <= (n - m) ? (i - j) : -1;
}

void buildNext(const char* p, int* next, int m) {
    int j = 0;
    int t = next[0] = -1;
    while (j < m - 1) {
        if (t < 0 || p[j] == p[t]) {
            next[++j] = ++t;
        }
        else
            t = next[t];
    }
}

String::String(const String& temp) {
    _rank = temp._rank;
    _capacity = temp._capacity;
    _elem = new char[_capacity];
    Strcpy(_elem, temp._elem);
}

void String::copyForm(char* s, int lo, int hi) {
    if (_elem) delete[] _elem;
    _capacity = 2 * (hi - lo) + 1;
    _rank = 0;
    _elem = new char[_capacity];
    while (lo < hi)
        _elem[_rank++] = s[lo++];
    _elem[_rank] = '\0';
}

String& String::operator= (const String& temp) {
    if (_elem) delete[] _elem;
    _rank = temp._rank;
    _capacity = temp._capacity;
    _elem = new char[_capacity];
    Strcpy(_elem, temp._elem);
    return *this;
}

void String::expand(int n) {
    if (_rank + n < _capacity) return;
    char* pass = _elem;
    while (_capacity <= _rank + n)
        _capacity = _capacity * 2 + 1;
    _elem = new char[_capacity];
    Strcpy(_elem, pass);
    if (pass) delete[] pass;
}

String& String::concat(const String& temp) {
    expand(temp.size());
    int i = 0;
    while (i < temp.size()) {
        _elem[_rank++] = temp._elem[i++];
    }
    _elem[_rank] = '\0';
    return *this;
}

String& String::erase(int i, int n) {
    if (i + n < _rank) {
        int lo = i + n;
        while (lo <= _rank)
            _elem[i++] = _elem[lo++];
        _rank -= n;
        return *this;
    }
    else
        return erase(i);
}

bool String::operator== (const String& temp) {
    if (_rank != temp._rank) return false;
    for (int i = 0; i < _rank; ++i) {
        if (_elem[i] != temp._elem[i])
            return false;
    }
    return true;
}

String String::operator+ (const String& temp) {
    String ans(2 * (_rank + temp._rank) + 1);
    for (int i = 0; i < _rank; ++i)
        ans._elem[i] = _elem[i];
    ans._rank = _rank;
    for (int i = 0; i < temp._rank; ++i)
        ans._elem[ans._rank++] = temp._elem[i];
    ans._elem[ans._rank] = '\0';
    return ans;
}

String String::operator+ (const char* s) {
    String ans(2 * (_rank + strlen(s)) + 1);
    Strcpy(ans._elem, _elem);
    Strcat(ans._elem, s);
    ans._rank = strlen(ans._elem);
    return ans;
}

String& String::operator+= (const char* s) {
    int n = strlen(s);
    expand(n);
    _rank += n;
    Strcat(_elem, s);
    return *this;
}

ostream& operator<<(ostream& os, const String& s) {
    os << s._elem;
    return os;
}

#endif