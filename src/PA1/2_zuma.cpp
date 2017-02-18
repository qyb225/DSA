#include <cstdio>
#include <iostream>

struct listNode {
    char data;
    listNode* pred;
    listNode* succ;
    listNode(const char& d) : data(d), pred(NULL), succ(NULL) {}
    void insertAsPred(listNode*);
    void insertAsSucc(listNode*);
};

class list_char {
private:
    int _rank;
    listNode* head;
    listNode* trail;
public:
    list_char();
    listNode* _head() { return head; }
    listNode* _trail() { return trail; }
    void insertAsLast(const char&);
    listNode* insert(int, const char&);
    listNode* remove(listNode*, int);
    void show();
    ~list_char();
};

int main() {
    list_char zuma;
    char input;
    scanf("%c", &input);
    while (input >= 'A' && input <= 'Z') {
        zuma.insertAsLast(input);
        scanf("%c", &input);
    }

    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        int j;
        char in;
        scanf("%d %c", &j, &in);

        listNode* t0 = zuma.insert(j, in);
        while (t0 != zuma._head() && t0 != zuma._trail()) {
            listNode* t1 = t0->succ;
            int count = 1;
            while (t0->data == t1->data) {
                ++count;
                t1 = t1->succ;
            }
            t1 = t0->pred;
            while (t0->data == t1->data) {
                ++count;
                t1 = t1->pred;
            }
            t1 = t1->succ;
            if (count > 2) {
                t0 = zuma.remove(t1, count);
            }
            else break;
        }
        zuma.show();
    }
}

list_char::list_char() {
    _rank = 0;
    head = new listNode('0');
    trail = new listNode('0');
    head->succ = trail;
    trail->pred = head;
}

void list_char::insertAsLast(const char& d) {
    listNode* n = new listNode(d);
    trail->insertAsPred(n);
    ++_rank;
}

void list_char::show() {
    listNode* f = head->succ;
    if (f == trail)
        printf("-");
    while (f != trail) {
        printf("%c", f->data);
        f = f->succ;
    }
    printf("\n");
}

listNode* list_char::remove(listNode* x, int n) {
    int i = 0;
    listNode* next = x;
    listNode* p = x->pred;
    while (i < n) {
        next = next->succ;
        delete next->pred;
        ++i;
    }
    next->pred = p;
    p->succ = next;
    _rank -= n;
    return p;
}

listNode* list_char::insert(int i, const char& d) {
    if (i < _rank / 2) {
        int j = 0;
        listNode* h = head;
        while (j < i) {
            h = h->succ;
            ++j;
        }
        listNode* n = new listNode(d);
        h->insertAsSucc(n);
        ++_rank;
        return n;
    }
    else {
        int j = _rank;
        listNode* t = trail;
        while (j > i) {
            t = t->pred;
            --j;
        }
        listNode* n = new listNode(d);
        t->insertAsPred(n);
        ++_rank;
        return n;
    }
}

list_char::~list_char() {
    listNode* _beh = head;
    listNode* _fro = head->succ;
    while (_fro != NULL) {
        delete _beh;
        _beh = _fro;
        _fro = _fro->succ;
    }
    delete _beh;
}

void listNode::insertAsPred(listNode* p) {
    pred->succ = p;
    p->pred = pred;
    p->succ = this;
    pred = p;
}
void listNode::insertAsSucc(listNode* s) {
    succ->pred = s;
    s->succ = succ;
    s->pred = this;
    succ = s;
}