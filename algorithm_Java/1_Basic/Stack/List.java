class ListNode<T> {
    protected T data;
    protected ListNode<T> succ;
    protected ListNode<T> pred;
    protected ListNode() {
        succ = null;
        pred = null;
    }
    protected ListNode(T e) {
        data = e;
        succ = null;
        pred = null;
    }
    protected ListNode<T> insertAsPred(ListNode<T> p) {
        if (pred != null) pred.succ = p;
        p.pred = pred;
        p.succ = this;
        pred = p;
        return p;
    }
    protected ListNode<T> insertAsSucc(ListNode<T> s) {
        if (succ != null) succ.pred = s;
        s.succ = succ;
        s.pred = this;
        succ = s;
        return s;
    }
}

public class List<T> {
    protected ListNode<T> header;
    protected ListNode<T> trailer;
    protected int _size;
    public List() {
        header = new ListNode<T>();
        trailer = new ListNode<T>();
        header.succ = trailer;
        trailer.pred = header;
        _size = 0;
    }
    public int size() {
        return _size;
    }
    public ListNode<T> insertAsFirst(T e) {
        ListNode<T> n = new ListNode<T>(e);
        ++_size;
        return header.insertAsSucc(n);
    }
    public ListNode<T> insertAsLast(T e) {
        ListNode<T> n = new ListNode<T>(e);
        ++_size;
        return trailer.insertAsPred(n);
    }
    public T remove(ListNode<T> del) {
        T temp = del.data;
        del.pred.succ = del.succ;
        del.succ.pred = del.pred;
        del = null;
        --_size;
        return temp;
    }
    public boolean empty() {
        return _size < 1;
    }
}
