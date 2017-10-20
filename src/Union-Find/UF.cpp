class UF {
private:
    int *id;        //parent
    int *size;      //tree size
    int num;        //number of connected components.
    int root(int p);
public:
    UF(int n);
    bool connected(int p, int q);
    void unions(int p, int q);
    int getNum() const { return num; }
    ~UF();
};

UF::UF(int n): num(n) {
    id = new int[n];
    size = new int[n];
    for (int i = 0; i < n; ++i) {
        id[i] = i;
        size[i] = 1;
    }
}

UF::~UF() {
    delete[] id;
    delete[] size;
}

void UF::unions(int p, int q) {
    int pRoot = root(p);
    int qRoot = root(q);
    if (pRoot == qRoot) {
        return;
    }
    --num;
    if (size[pRoot] < size[qRoot]) {
        id[pRoot] = qRoot;
        size[qRoot] += size[pRoot];
    } else {
        id[qRoot] = pRoot;
        size[pRoot] += size[qRoot];
    }
}

int UF::root(int p) {
    while (p != id[p]) {
        id[p] = id[id[p]];
        p = id[p];
    }
    return p;
}

bool UF::connected(int p, int q) {
    return root(p) == root(q);
}