//1. 泛型基类A
class A<T> {
    protected T name;
    public A(T e) {
        name = e;
    }
    public void func() {
        System.out.println(name);
    }
}

//2. 泛型派生类B
class B<T> extends A<T> {
    protected int age;
    public B(int a, T n) {
        super(n); //调用父类构造函数
        age = a;
    }
    public void func() {
        System.out.println(name + " " + age);
    }
}

public class basicInfo {
    public static void main(String args[]) { //static方法只能直接调用static方法
        A<String> t = new B<String>(20, "Fideo"); //多态机制 声明前后都要写模板
        t.func();
        basicInfo.staticFunc(); //类似 Math.random() 等静态函数
    }
    public static void staticFunc() {
        System.out.println("static");
    }
}