# 继承和多态

---

在面向对象的程序设计中，一个很重要的改变便是加入了继承和多态，下文将介绍在 C++ 语言中如何使用这种机制。

---

## 一、 继承

###1. 继承和派生的概念：

在定义一个新的类B时，如果该类与某个已有的类A相似 **(指的是B拥有A的全部特点)**，那么就可以把A作为一个基类，而把B作为基类的一个**派生类**(也称子类)。

* 派生类是通过对基类进行修改和扩充得到的。在派生类中，可以扩充新的成员变量和成员函数。
* 派生类一经定义后，可以独立使用，不依赖于基类。

**Examples**

> 基类：学生类

> 继承基类的派生类：本科生类、研究生类……

**Notes：**

如上例，本科生，研究生都属于学生，他们相似但又不完全相同。如果每一个不同的学生都写一个不同的类，则代码量庞大，如果以学生类为基类，派生出本科生、研究生类，这些派生类都包含了学生类的所有特点，与此同时还会有自己的特点。这便是继承的思想。

---

###2. 派生类的写法：

**具体形式：** **class 派生类名: public 基类名 { };**

例如：

> **class student {};** // 基类

> **class undergraduate_student: public student {};** // 派生类

---

###3. protected 关键字

之前我们已经知道了 **public**, **private** 关键字。还有一个关键字名为 **protected**，这三个关键字的**访问范围**如下：

> **① private成员：**

> * 基类的成员函数
* 基类的友员函数

> **② public成员：**

>* 基类的成员函数
* 基类的友员函数
* 派生类的成员函数
* 派生类的友员函数
* 其他的函数

> **③ protected成员：**

> * 基类的成员函数
* 基类的友员函数
* 派生类的成员函数可以访问**当前对象**的基类的保护成员

**Notice**：在这里特意用了 “当前对象” 一词，如果**不是**派生类成员函数中的**当前对象**，即 this 指针指向的对象，那么就**不能够**访问基类的 **protected** 成员，也就是即使在派生类的成员函数中，如果新定义一个派生类的对象，则该对象不能访问到基类的protected成员。

---

**Example:**

```cpp
//The class of Father
class Father {
private:
    int nPrivate; //私有成员
public: 
    int nPublic; //公有成员
protected: 
    int nProtected; // 保护成员
};

//The class of Son
class Son : public Father {
public:
    void AccessFather ();
};

void Son::AccessFather () {
    nPublic = 1; // ok;
    nPrivate = 1; // wrong
    nProtected = 1; // OK, 访问从基类继承的protected成员
    Son f;
    f.nProtected = 1; //wrong, f不是当前对象
}
```

---

###4. 派生类的构造函数和析构函数

**构造函数：**
派生类的对象，是包含了基类对象的，因此在对象初始化的时候，需要先执行基类的构造函数，再执行派生类自己的构造函数。

**具体形式：** **派生类名(形式参数表): 基类名(基类构造函数实际参数表){ }**

例如：
```cpp
//基类：虫虫类
class bug {
private:
    int feet;
    int color;
public:
    bug(int f, int c): feet(f), color(c) {} //基类构造函数
};

//派生类：飞翔的虫虫类
class fly_bug: public bug {
private:
    int wings;
public:
    fly_bug(int, int, int);
};

//派生类(飞翔的虫虫)构造函数：
fly_bug::fly_bug(int f, int c, int w): bug(f, c) {
    wings = w;
}

//错误的派生类构造函数：
fly_bug::fly_bug(int f, int c, int w) {
    feet = f;  //不能访问 private 成员
    color = c; //还是不能访问
    wings = w;
}
```

**析构函数：**
派生类的析构函数被执行时, 执行完派生类的析构函数后, 自动调用基类的析构函数。

**Tips：**析构函数的调用顺序与构造函数的调用顺序相反。

---
