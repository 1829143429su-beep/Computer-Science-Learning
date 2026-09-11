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
```c
strcpy(s.name, "Tom");
```
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

```
#### p->age 等价于什么？
(*p).age  //注意这里必须有括号；因为 . 的优先级问题会导致含义不同。
```text
s.age     → 结构体变量
(*p).age  → 结构体指针解引用后访问
p->age    → 结构体指针访问成员
```

### 易错
#### 1.如果以后你想让其他函数也使用 struct Student，应该把定义放到函数外：
```c
struct Student
{
    char name[20];
    int age;
    double score;
};

void create_st()
{
    struct Student s;

    ...
}
```
#### 2.double
scanf 读取 double → %lf
printf 输出 double → %f（此处建议写：%.1f保留一位小数）

#### 3.区别
students[0] = { "Tom",20,90.5 }; //在 C 语言里不能用于给已经创建好的结构体变量重新赋值。

struct Student s = {"Tom", 20, 90.5}; //属于定义变量时初始化，可以。
```c
定义变量时初始化	struct Student s = {"Tom", 20, 90.5}; ✅
数组定义时初始化	struct Student a[3] = { ... }; ✅
创建后给字符串成员 strcpy(s.name, "Tom"); ✅
创建后给普通成员	s.age = 20; ✅
创建后整体写 {} 赋值	s = {"Tom",20,90.5}; ❌
```
#### 4.scanf
里面不能写提示文字
```c
scanf("%s", students[i].name); //为什么没有 &
因为：students[i].name//本身就是字符数组，在这里会转换成首元素地址

scanf("%d", &students[i].age);
因为 age 是一个普通的 int 变量，所以需要&
```
这里有一个需要注意的地方：你在格式字符串里写了逗号 ,  

这意味着你输入时必须严格按照：Tom,20,90.5 的格式输入。

```c
struct Student* p;
scanf("%d", p->age);     // ❌ p->age 是数据
scanf("%d", &p->age);    // ✅ &p->age 是地址
```

注意
```text
因为 %s 不会在逗号处停止，它会一直读到空白字符为止。
所以输入：T,19,90.5时，%s 会把整个 T,19,90.5 都读进 name。
于是：
name = "T,19,90.5"
age  = 没有成功赋值
score = 没有成功赋值

1.建议现阶段使用空格分隔；
2.直接在 scanf 中匹配逗号:
scanf("%[^,],%d,%lf",
    students[i].name,
    &students[i].age,
    &students[i].score);
```

#### 4.区分s、&s[0]、&s
s	    数组名，传函数时通常变成第一个元素地址

&s[0]	第一个学生的地址（第二个学生通过p+i即可）

&s	    整个数组的地址
```c
void input_students(struct Student* p, int size)

struct Student s[size];//是结构体数组；
input_students(s, size);     // ✅
input_students(&s[0], size); // ✅
input_students(&s, size);    // ❌
```
```c
struct Student s = { "Jack", 20, 90.0 }; //你现在这个 s 是一个学生
&s就是：这个学生 s 的地址
```
### 练习
#### 1.结构体初始化：
```c
#include <stdio.h>
#include <string.h>

struct Student
{
    char name[20];
    int age;
    double score;
};

int main()
{
    struct Student s = {"Tom", 20, 90.5}; //初始化

    printf("姓名：%s\n", s.name);
    printf("年龄：%d\n", s.age);
    printf("分数：%.1f\n", s.score);

    return 0;
}
```
#### 2.结构体数组：
struct Student students[3]; //创建数组后赋值或者直接初始化
```text
① 给三个学生赋值
Tom   20   90.5
Jack  21   85.0
Lucy  19   95.5
注意 name 是字符数组，所以不能：students[0].name = "Tom";   // ❌
要使用：strcpy(students[0].name, "Tom");
② 用 for 循环输出三个学生
```
#### 3.结构体数组和 scanf，让用户自己输入 3 个学生的信息

#### 4.输入 3 个学生的信息，然后找出分数最高的学生。
找学生！！！ 关注下标

#### 5.把结构体指针传给函数，在函数里修改学生信息
```c
void change_student(struct Student* p) //指针作为参数
{
    p->age = 21;
    p->score = 95.5;
}
int main()
{
    struct Student s = {"Tom", 20, 90.5};
    change_student(&s)；//括号内写 变量地址；通过传地址改变值
    printf("分数：%.1f\n", s.score);
    return 0;
}
```
#### 6.结构体数组 + 指针 + 函数
你自己写一个函数：
```c
int find_max_student(struct Student* p, int size)
```
```text
要求：
p 指向学生数组
size 表示学生数量
找出分数最高的学生
返回这个学生在数组中的下标
main 中输出他的姓名、年龄、分数
```
```text
目前最高分是 students[max_index]
那么每次就应该比较：
当前学生 students[i]
        ↓
        和
        ↓
目前最高分学生 students[max_index]
```
#### 7.批量修改信息
要求：每个学生加5分

#### 8.修改指定学生信息
要求：把指定下标学生的分数增加 5 分。

(p + index)->score

#### 9.查找指定学生的信息
int find_student(struct Student* p, int size, char* name)

要求：根据姓名查找学生，找到就返回该学生的下标，找不到返回 -1。

易错：
```text
1.比较两个字符串
strcmp(a, b) == 0

2.char name='T'; //只能保存单个字符，不能保存字符串；
  char name[]="Tom"或者{'T','o','m','\0'};

3.const char* name
可以暂时理解成：
指向要查找的字符串的指针，而且函数不会修改这个字符串。
```

#### 10.查找分数最高的学生并修改他的分数

#### 11.结构体排序
输入 3 个学生的信息，按照分数从高到低排序并输出。

```text
1.temp 类型错了
int* temp; // ❌
但是你要交换的是两个：struct Student
应该是：
struct Student temp;

2.不能交换 p+i 本身，要交换它们指向的学生
你现在写：
temp = p + i + 1;
p + i + 1 = p + i;
p + i = temp;
这里的问题是：p + i只是一个地址计算结果，不能这样直接赋值。

你真正想交换的是：
第 i 个学生 <-> 第 i+1 个学生
也就是：*(p + i)和*(p + i + 1)
所以交换应该是：
struct Student temp;
temp = *(p + i);
*(p + i) = *(p + i + 1);
*(p + i + 1) = temp;

3.你的排序循环不完整
你现在：
for (int i = 0; i < size; i++) //只进行了一轮比较。

冒泡排序需要多轮：
for (int i = 0; i < size - 1; i++)
{
    for (int j = 0; j < size - 1 - i; j++)
    {
        // 比较相邻学生
    }
}
```










