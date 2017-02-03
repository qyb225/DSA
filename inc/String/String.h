#ifndef STRING_H
#define STRING_H
#include <iostream>
#include <cstring>
using namespace std;

class String {
private:
    int _rank;
    int _capacity;
    char* _elem;
    void copyForm(char*, int, int);
    void expand(int);
public:
    String(int c = 8) { _elem = new char[c]; _rank = 0; _capacity = c; _elem[0] = '\0'; }
    String(char* s) { copyForm(s, 0, strlen(s)); }
    String(char* s, int lo, int hi) { copyForm(s, lo, hi); }
    String(const String&);
    ~String() { if (_elem) delete[] _elem; }
    int size() const { return _rank; }
    char& charAt(int i) { if (i < _rank) return _elem[i]; }
    char& operator[] (int i) { if (i < _rank) return _elem[i]; }
    String substr(int i, int k) { return String(_elem, i, i + k); }
    String prefix(int k) { return String(_elem, 0, k); }               //[0, k)
    String suffix(int k) { return String(_elem, _rank - k, _rank); }   //[n - k, n)
    String& concat(const String&);
    bool operator== (const String&);
    String& operator= (const String&);
    String operator+ (const String&);
    String operator+ (const char*);
    String& operator+= (const String& temp) { return concat(temp); }
    String& operator+= (const char*);
    int indexOf(String&); //字符串索引匹配
    friend ostream& operator<< (ostream&, const String&);
};

char* Strcpy(char*, const char*);
char* Strcat(char*, const char*);

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