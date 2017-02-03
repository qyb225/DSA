#ifndef STRING_H
#define STRING_H
class String {
private:
    int _rank;
    int _capacity;
    char* _elem;
    void copyForm(char*, int, int);
    void expand();
public:
    String(int c = 0) { _elem = new char[c]; _rank = 0; _capacity = c; }
    String(char* s) { copyForm(s, 0, strlen(s)); }
    String(char* s, int lo, int hi) { copyForm(s, lo, hi); }
    String(const String&);
    int size() const { return _rank; }
    char& charAt(int i) { return _elem[i]; }
    char& operator[] (int i) { return _elem[i]; }
    String substr(int i, int k) { return String(_elem, i, i + k); }
    String prefix(int k) { return String(_elem, 0, k); }               //[0, k)
    String suffix(int k) { return String(_elem, _rank - k, _rank); }   //[n - k, n)
    String& concat(const String&);
    bool operator== (const String&);
    String operator+ (const String&);
    String operator+ (const char*);
    String& operator+= (const String& temp) { return concat(temp); }
    String& operator+= (const char*);
    int indexOf(String&); //字符串索引匹配
};
#endif