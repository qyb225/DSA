class ListNode {
    protected int data;
    protected ListNode succ;
    protected ListNode pred;
    protected ListNode() {
        data = 0;
        succ = null;
        pred = null;
    }
    protected ListNode(int e) {
        data = e;
        succ = null;
        pred = null;
    }
    protected ListNode insertAsPred(ListNode p) {
        if (pred != null) pred.succ = p;
        p.pred = pred;
        p.succ = this;
        pred = p;
        return p;
    }
    protected ListNode insertAsSucc(ListNode s) {
        if (succ != null) succ.pred = s;
        s.succ = succ;
        s.pred = this;
        succ = s;
        return s;
    }
}

public class List {
    protected ListNode header;
    protected ListNode trailer;
    protected int _size;

    protected ListNode selectMax(int n) {
        ListNode first = header.succ;
        ListNode ans = first;
        int max = first.data;
        for (int i = 0; i < n; ++i, first = first.succ) {
            if (max < first.data) {
                max = first.data;
                ans = first;
            }
        }
        return ans;
    }

    protected void swapNode(ListNode a, ListNode b) {
        int swap = a.data;
        a.data = b.data;
        b.data = swap;
    }

    public List() {
        header = new ListNode();
        trailer = new ListNode();
        header.succ = trailer;
        trailer.pred = header;
        _size = 0;
    }

    public int size() {
        return _size;
    }

    public ListNode insertAsFirst(int e) {
        ListNode n = new ListNode(e);
        ++_size;
        return header.insertAsSucc(n);
    }

    public ListNode insertAsLast(int e) {
        ListNode n = new ListNode(e);
        ++_size;
        return trailer.insertAsPred(n);
    }

    public ListNode insertAsPred(int e, ListNode t) {
        ListNode n = new ListNode(e);
        ++_size;
        return t.insertAsPred(n);
    }

    public ListNode insertAsSucc(int e, ListNode t) {
        ListNode n = new ListNode(e);
        ++_size;
        return t.insertAsSucc(n);
    }

    public int remove(ListNode del) {
        int temp = del.data;
        del.pred.succ = del.succ;
        del.succ.pred = del.pred;
        del = null;
        --_size;
        return temp;
    }

    public boolean empty() {
        return _size < 1;
    }

    public void show() {
        ListNode first = header.succ;
        while (first != trailer) {
            System.out.print(first.data + " ");
            first = first.succ;
        }
        System.out.println();
    }

    public int indexOf(int i) {
        if (i < _size / 2) {
            ListNode first = header.succ;
            int j = 0;
            while (j++ < i)
                first = first.succ;
            return first.data;
        }
        else if (_size / 2 <= i && i < _size) {
            ListNode last = trailer.pred;
            int j = _size;
            while (--j > i) 
                last = last.pred;
            return last.data;
        }
        return 0;
    }

    public void sort() {
        ListNode last = trailer.pred;
        int n = _size;
        while (n > 1) {
            ListNode swap = selectMax(n);
            swapNode(swap, last);
            --n;
            last = last.pred;
        }
    }

    public static void main(String[] args) {
        List l = new List();
        for (int i = 9; i > -1; --i) {
            l.insertAsLast(i);
        }
        l.show();
        for (int i = 0; i < 10; ++i) {
            System.out.print(l.indexOf(i) + " ");
        }
        System.out.println();
        l.sort();
        l.show();
    }
}
