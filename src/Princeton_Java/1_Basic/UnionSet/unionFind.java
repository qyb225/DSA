//并查集问题带权算法
public class unionFind {
    private int[] _root;
    private int[] _size;

    public unionFind(int n) {
        _root = new int[n];
        _size = new int[n];
        for (int i = 0; i < n; ++i) {
            _root[i] = i;
            _size[i] = 1;
        }
    }

    private int root(int i) {
        while (i != _root[i]) {
            _root[i] = _root[_root[i]]; //路径压缩
            i = _root[i];
        }
        return i;
    }

    public void union(int p, int q) { //连接两个Vertex
        int root_p = root(p);
        int root_q = root(q);
        if (_size[root_p] < _size[root_q]) {
            _root[root_p] = root_q;
            _size[root_q] += _size[root_p];
        }
        else {
            _root[root_q] = root_p;
            _size[root_p] += _size[root_q];
        }
    }

    public boolean connected(int p, int q) { //判断路径存在与否
        return root(p) == root(q);
    }
}