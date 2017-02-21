public class Queue<T> extends List<T> {
    public void enqueue(T e) {
        insertAsLast(e);
    }
    public T dequeue() {
        return remove(header.succ);
    }
    public T front() {
        return header.succ.data;
    }
}