public class Stack<T> extends List<T> {
    public Stack() {}
    public void push(T e) {
        insertAsLast(e);
    }
    public T pop() {
        return remove(trailer.pred);
    }
    public T top() {
        return trailer.pred.data;
    }
}