
#String 类：

下面介绍一些String类中定义的方法。以下所有出现的str或者str1，str2...都为string类定义的对象。

---

##一、字符串的连接：

**1.** 在 string 类中，运算符 '+' 被重载，在两个字符串之间使用 '+' 结果将返回将两个字符串首尾相接的字符串。

**E.g.** 

```cpp
# include <iostream>
# include <string>
using namespace std;

int main() {
    string str1 = "abc", str2 = "def";
    
    cout << str1 + str2 << endl; // 输出 "abcdef"
    
    return 0;
}
```

---

**2.** 使用 append 方法

**方法调用：** 

**① str1.append(str2)** 

说明：将 s2 连接到 s1 的尾部。

**② st1.append(st2, i, n)** 

说明：将 s2 从下标 i 开始的 n 个字符加入到s1的尾部。

**E.g.** 

```cpp
# include <iostream>
# include <string>
using namespace std;

int main() {
    string str1 = "abc", str2 = "def";
    
    cout << str1.append(str2) << endl; // 输出 "abcdef"
    cout << str2.append(str1, 0, 3) << endl; // 输出 "defabc"
    
    return 0;
}
```

---

##二、字符串长度

使用 length 或 size 方法

**方法调用：**

**① str.length()**

说明：返回字符串 str 的长度。

**② str.size()**

说明：返回字符串 str 的长度。

**E.g.**

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string str = "abcdef";
    
    cout << str.length() << endl; // 输出 6
    cout << str.size() << endl; // 输出6
    
    return 0;
}
```

---

##三、字符串提取子串

使用 substr 方法

介绍：该方法原型为：**basic_string substr( size_t index, size_t num = npos);** 其中的 **size_t** 是定义在 string 类中的一个新的数据类型，是一个无符号整数，而 **string::npos** 则是 size_t 类型的一个常数，是一个 string 的"结束粒子"，标志着字符串的结束。

**方法调用：** 

**str.substr(index, num);** 

说明：第一个参数 index 是你希望获得的子串开始的下标，第二个参数 num 是你希望截取的子串的长度，如果不填第二个参数，则会返回从下标开始一直到字符串结束的子串。

**E.g.**

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string str = "abcdef";
    
    cout << str.substr(2,2) << endl; // 输出 "cd"
    cout << str.substr(2) << endl; // 输出 "cdef"
    
    return 0;
}
```

---

##四、字符串中查找子串

**1.** 使用 find 方法

该方法原型为：**size_t find (const string & s, size_t pos = 0);**

**方法调用：**

**① str.find(str1);** 

说明：str1 在str中首次出现的位置。

**② str.find(str1, index)** 

说明：str1 从str的下标index开始首次出现的位置。


**E.g.**

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string str = "abcabc";
    string str1 = "abc";
    
    cout << str.find(str1) << endl; // 输出 0
    cout << str.find(str1, 1) << endl; // 输出 3
    
    return 0;
}

```

---

**2.** 使用 rfind 方法

介绍：该方法与 find 方法的区别是 find 方法是从头开始查找，而 rfind 方法是从尾部开始查找指定字符串第一次出现的位置。

**方法调用：**

**① str.rfind(str1)** 

说明：从尾部开始**向前**查找str1最后一次出现的位置。

**② str.rfind(str1, i)** 

说明：从 i 开始**向前**查找str1最后一次在str中出现的位置。

**E.g.**

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string str = "abcabc";
    string str1 = "abc";
    
    cout << str.rfind(str1) << endl; // 输出 3
    cout << str.rfind(str1, 2) << endl; // 输出 0
    
    return 0;
}
```

---

**3.** 使用 find_first_of 方法

**方法调用：**

**str.find_first_of(str1)**

说明：向后查找str1中任意一个字符在str中第一次出现的位置。

---

**4.** 使用 find_first_not_of 方法

**方法调用：**

**str.find_first_not_of(str1)**

说明：向后查找不在str1中的任意字符在str中第一次出现的位置。

**E.g.**

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string str = "hello world!";
    string str1 = "abcde";
    
    cout << str.find_first_of(str1) << endl; // 输出 1
    cout << str.find_first_not_of(str1) << endl; // 输出 0
    
    return 0;
}
```

---

**5.** 使用 find_last_of 方法

**方法调用：**

**str.find_last_of(str1)**

说明：寻找 str1 中任何一个字符最后一次在 str 中出现的位置。

---

**6.** 使用 find_last_not_of 方法

**方法调用：**

**str.find_last_not_of(str1)**

说明：寻找任何一个不在 str1 中的字符最后一次在 str 中出现的位置。

**E.g.**

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string str = "hello world!";
    string str1 = "abcde";
    
    cout << str.find_last_of(str1) << endl; // 输出 10
    cout << str.find_last_not_of(str1) << endl; // 输出 11
    
    return 0;
}
```

---

##五、字符串特定字符删除

采用了 erase 方法

介绍：该方法原型为：**string & erase ( size_t pos = 0, size_t n = npos );**

**方法调用：**

**str.erase(i, n)**

说明：删除字符串从下标 i 开始的 n 个字符。

**E.g.**

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string str = "abcdef";
    
    cout << str.erase(0, 1) << endl; // 输出 "bcdef"
    cout << str.erase(2) << endl; // 输出 "bc"
    cout << str.erase() << endl; // 输出空字符串 ""
    
    return 0;
}

```

---

##六、字符串替换

使用 replace 方法

**方法调用：**

**① str.replace(i, n, str1)**

说明：将 str 中从下标 i 开始的 n 个字符替换成 str1 。

**② str.replace(i, n, str1, i1, n1)**

说明：将 str 中从下标 i 开始的 n 个字符替换成 str1 中从下标 i1 开始的 n1 个字符。

**E.g.**

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string str = "abcdef";
    
    cout << str.replace(0, 2, "haha") << endl; // 输出 "hahcdef"
    cout << str.replace(0, 4, "haha", 1, 2) << endl; // 输出 "ahcdef"
    
    return 0;
}

```

---

##七、字符串插入

使用 insert 方法

**方法调用：**

**① str.insert(i, str1)**

说明：在 str 下标 i 的位置处插入 str1.

**② str.insert(i, str1, i1, n)**

说明：在 str 下标 i 的位置处插入 str1 从 下标 i1 开始的 n 个字符.

**E.g.**

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string str = "abcdef";
    string str1 = "QYBB";
    
    cout << str.insert(1, str1) << endl; // 输出 "aQYBBbcdef"
    cout << str.insert(5, str1, 0, 3) << endl; // 输出 "aQYBBQYBbcdef"
    
    return 0;
}

```

---


