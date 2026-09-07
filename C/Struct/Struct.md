## 结构体
### 定义：
结构体就是把属于同一个对象的不同类型的数据放在一起。
### 学习：
```text
struct Student
{
    char name[20];
    int age;
    double score;
};

然后：
struct Student s;

继续：
struct Student* p = &s;
```

### 步骤：
#### 1.定义一个结构体：
```c
struct Student
{
    char name[20];
    int age;
    double score;
};  //注意结尾的分号；
/*这是在定义一种新的数据结构。
可以理解成：
我现在告诉 C 语言，有一种东西叫 struct Student，它里面有姓名、年龄和成绩。*/
```
#### 2.创建结构体变量：
```c
struct Student s;  //这才是真正创建了一个学生变量 s。
```
可以理解成：

struct Student    //一种“模板”

struct Student s;   //按照模板创建一个具体学生 s

#### 3.给成员赋值：
```c
s.age = 20;
s.score = 85.5;
```
但是 name 是字符数组，不能直接写：

s.name = "Tom";  // ❌

需要使用：

strcpy(s.name, "Tom");

#### 4.结构体指针：
struct Student s;

我们有一个结构体变量,可以取得它的地址：

struct Student*p=&s;

### 重点：
s.age 和 p->age 之间的关系。

#### 1）  s.age中的 . 是什么 
.叫做成员访问运算符，意思是访问结构体变量s中的age成员

s.age = 20; //把 s 里面的 age 修改为 20。

s.score = 90;  //修改 s 的成绩。

#### 2)  p->age 是什么
```text
struct Student* p = &s;

所以：
p
 ↓
s
┌──────────────┐
│ name         │
│ age          │
│ score        │
└──────────────┘
如果：
s.age = 20;
那么通过指针也可以访问 age：
p->age = 20；

二者效果一样
| 情况       | 写法     |
| 结构体变量 | `s.age`  |
| 结构体指针 | `p->age` |

```
#### p->age 等价于什么？


```
```

```
```
```
