# 结构体 + 动态内存
### 学习：
开始组合：
```c
typedef struct
{
    char name[20];
    int age;
} Student;
```
然后：
```c
Student* p = malloc(sizeof(Student));
```
做一个小项目：学生管理系统
```text
实现：
1. 添加学生
2. 删除学生
3. 修改学生
4. 查找学生
5. 显示学生
6. 排序
7. 保存文件
8. 退出
```
### 步骤：
#### 第1步：结构体 + malloc
先理解：
```c
typedef struct
{
    char name[20];
    int age;
    double score;
} Student;

//typedef....Student;是给这个结构体起的别名，以后声明变量直接Student s;
//不需要再写 struct Student s;
```
然后：
```c
Student* p = malloc(sizeof(Student));
```
##### 练习1：使用 malloc 动态创建一个 Student，输入一个学生的信息（姓名、年龄、成绩），输出后 free。
```c
void create_student() {
	Student* p = malloc(sizeof(Student));
	if (p == NULL) {
		printf("动态内存创建失败");
		return;
	}

	printf("输入学生信息：");
	scanf("%s %d %lf", p->name, &p->age, &p->score);
	
	printf("学生姓名：%s,年龄：%d,分数：%.1f", p->name, p->age, p->score);
	free(p);
}
```

问题：
```text
1.现在你只创建了一个学生：
Student* p = malloc(sizeof(Student));
所以根本不需要 i。
直接操作 p：
scanf("%s %d %lf", p->name, &p->age, &p->score);

2.scanf 的 age 和 score 要传地址
p->name       → 不加 &
&p->age       → 加 &
&p->score     → 加 &

3.如果malloc 失败，应该停止
if (p == NULL) {
    printf("动态内存创建失败");
    return;
}

4.有一个小习惯可以养成：
free(p);
p = NULL;//释放后置 NULL 是个好习惯
```

#### 第 2 步：动态数组
从：
```c
Student* p = malloc(sizeof(Student));
```
变成：
```c
Student* p = malloc(sizeof(Student) * size);
```
理解：
```text
p
↓
┌────────┬────────┬────────┐
│Student │Student │Student │
│   0    │   1    │   2    │
└────────┴────────┴────────┘
```
##### 练习2：动态创建多个学生，数量由用户确定
```c
void create_students() {
	int size;
	printf("请输入学生数量：");
	scanf("%d", size);
	Student* p = malloc(sizeof(Student)*size);
	if (p == NULL) {
		printf("动态内存创建失败");
		return;
	}
	for (int i = 0; i < size; i++) {
		printf("输入第%d个学生的信息：",i+1);
		scanf("%s %d %lf", (p+i)->name, &(p+i)->age, &(p+i)->score);
	}

	for (int i = 0; i < size; i++) {
		printf("第%d个学生 姓名：%s,年龄：%d,分数：%.1f",i+1, (p + i)->name, (p + i)->age, (p + i)->score);
	}
	
	free(p);
	p = NULL;
}

```
#### 考虑：如何让 p 和学生数量 size 在函数结束后仍然存在？
问题：
```
free(p);之后，所有学生数据都没了。
练习这样写没问题，学生管理系统显然不能这样

让 p 在 create_students() 函数结束后，仍然能够被外面的程序使用。
```

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char name[20];
    int age;
    double score;
} Student;

// 创建多个学生
void create_students(Student* p, int size)
{
    Student* p = malloc(sizeof(Student) * size);
   //这个 p 是函数自己的局部变量，外面的 p 不会跟着改变。函数执行结束后，p 这个变量本身就不存在了。
}

// main
int main()
{
    int size;
    printf("请输入学生数量：");
    scanf("%d", &size);

    Student* p = NULL;//p 是一个指针，它存放的是 Student 的地址。
    create_students(&p, size);
    // 后面在这里继续使用 p

    return 0;
}
```

### 解决:二级指针
```c
Student* p;
Student** pp = &p;
```
先回忆一级指针
```c
int a = 10;  
int* p = &a; 
//p=&a  指针变量p存放a的地址
//*p=10 解引用得a的值
//&p    指针p的地址
```
什么是二级指针？
```c
int a = 10;
int* p = &a;
int** pp = &p;
//pp=&p  指针变量pp存放指针p的地址
//*pp=p=&a  pp解引用得p的值，也就是a的地址
//**pp=*p=a 
```
```text
如果我们想让函数真正修改：main中的 p
那函数就不能只拿到 p 的值。
它需要拿到：p 自己的地址
也就是：&p

p 是 int*，所以 &p 的类型就是：int**
```
二级指针让函数获得了修改 p 本身的能力。至于修改成什么，是函数里的代码决定的。
```c
void create_student(Student** pp)
{
    *pp = malloc(sizeof(Student)); //找到外面的 p，让 p 指向新申请的 Student 内存。
    //p = malloc(sizeof(Student));
//区别在于：create_student() 里面没有直接看到 main 的 p，借助二级指针pp修改 main 中的 p。
}

int main(){
    Student* p = NULL;  //p 是一个 Student* 类型的变量，但是目前它还没有指向任何学生。
    create_student(&p); //取指针p的地址，是Student**类型的
}
```

```c
void change(int** pp)
{
    *pp = NULL;
}
调用：
change(&p);//main中的 p = NULL
```
#### 练习2：二级指针
用途：
1.malloc：
```c
void create_student(Student** pp)
{
    *pp = malloc(sizeof(Student));
}
```
本质：
```text
NULL
 ↓
新申请的内存

也就是：

让函数给外面的 p 赋一个新的地址。
```
2.realloc:
```c
void resize(Student** pp)
{
    Student* temp = realloc(*pp, sizeof(Student)*new_size);

    if (temp != NULL)
    {
        *pp = temp;
    }
}
```
本质：
```text
旧地址
 ↓
realloc
 ↓
新地址

也就是：让函数更新外面的 p，使它指向扩容后的内存。
```

```c
void create_student(Student** pp) {
	*pp = malloc(sizeof(Student));
	if (*pp == NULL) {
		printf("申请失败");
	}
}
void result2() {
	Student* p = NULL;
	create_student(&p);
	printf("请输入该学生的信息：");
	scanf("%s %d %lf", p->name, &p->age, &p->score);
	free(p);
	p = NULL;
}
```
易错：
```text
1.函数参数已经有：Student** pp
所以函数里面再写：Student* pp  相当于：同一个作用域里，把 pp 又定义了一次。
这是错误的。

2.new_size 没有初始化
int new_size;
revise(&p, new_size);

这里 new_size 没有赋值。所以它里面是一个未定义的垃圾值，传给 realloc 会产生未定义行为。
如果只是为了继续做之前的 realloc 练习，
需要：int new_size = 4;
```
#### 第 3 步：添加学生
realloc() //实现“学生数量可以增加”。

为什么 realloc 扩容后，第 4 个学生的数据需要我们重新输入，而前 3 个不用重新输入？

realloc(*pp, sizeof(Student) * new_size);//调整这块动态内存的大小，并尽可能保留原来的数据。

realloc 不是“清空后重新申请”。

它的核心作用是：改变已有动态内存块的大小，同时保留原有数据（在成功扩容的情况下）。

##### 练习3：添加学生,每次加1人
为了保证只有 realloc 成功，学生数量 size 才真正增加，需要两个变量
```c
*size    = 3   ← 暂时不变
new_size = 4   ← 用来尝试扩容
如果成功，*size = new_size;
```

```c
void add_student(Student** pp,int* size) {
	int new_size = *size + 1;
	Student* temp = realloc(*pp, sizeof(Student) * new_size);
	if (temp != NULL) {
		*pp = temp;
		*size = new_size;
	}
	else
	{
		printf("扩容失败\n");
		return;
	}
	printf("请输入第%d个学生的信息：", *size);
	scanf("%s %d %lf", (*pp + *size - 1)->name, &(*pp + *size - 1)->age, &(*pp + *size - 1)->score);
}

add_student(&p, &size);
```
#### 第 4 步：删除学生
思考删除的本质
```text
0  Tom   80
1  Jack  90   ← 删除
2  Lucy  95
3  Bob   85

删除 Jack 后：
0  Tom   80
1  Lucy  95
2  Bob   85
你并不需要真的把内存中那个人“擦掉”。
本质上就是把后面的元素向前移动。

也就是：
p[2] → p[1]
p[3] → p[2]

然后：
size: 4 → 3
```

你需要一个变量记录要删除的下标 index
```
目前如果：index = -1;
或者：index >= *size;
就可能越界访问。
所以你下一步自己加一个下标合法性检查，放在 for 循环之前：
if (index < 0||index >= *size)
{
    printf("下标错误\n");
    return;
}
```

##### 根据姓名删除学生
```text
先根据姓名找到下标
再移除该下标的学生
```
#### 第 5 步：修改 / 查找 / 显示 / 排序

这些你其实已经会了，只是把：

struct Student s[3];

变成：

Student* students;

所以这部分是知识迁移。

##### 按姓名修改年龄和成绩
```text
你写了：
void change_student_by_name(Student* p, int size, const char* name, int* age)
但函数内部根本没有使用 age：
scanf("%d %lf", &(p+index)->age, &(p+index)->score);

你已经直接修改：
(p + index)->age
所以 int* age 可以删掉。
```

##### 按成绩从高到低排序，然后显示排序后的学生
冒泡

#### 第六步：创建菜单
```c
while (1)
{
    menu();

    int choice;
    scanf("%d", &choice);

    switch (choice)
    {
        // ...
    }
}
```

设置一个退出条件
```c
int running = 1;//退出while

while (running)
{
    menu();

    // ...

    case 0:
        running = 0;
        break;//退出switch
}
```

不过这里会出现一个 C 语言问题：
```
你在不同的 case 里重复声明了：
char name[20];
case 不是自动创建独立作用域的，所以这些 name 实际上可能属于同一个 switch 作用域，会产生重复定义问题。
推荐你给每个 case 加 {}：
这样每个 {} 都形成自己的作用域
```

#### 易错
```text
1.缺少 <string.h>
你用了：strcmp(...)
需要加：
#include<string.h>
否则 strcmp 没有正确声明。
```

```text
2.free(p) 现在实际上执行不到
你写的是：
while(1){
case 0:
    return 0;
}
而：
free(p);
p = NULL;
return 0;
在 while(1) 后面。

也就是说你现在：
选择 0 -> return 0 -> main结束

需要改成：
选择 0 -> free(p) -> main结束
```
```text
3.create_student() 申请失败后，main 还会继续
需要解决：如果 malloc 失败，怎么让 main() 知道失败了？

现在阶段的方法是：让函数返回成功或失败状态。

把：void create_student(...)
改成：int create_student(...)
约定：
返回 1 → 成功
返回 0 → 失败
```


### 第 6 步：文件操作
```c
fopen()    → 打开/创建文件
fprintf()  → 往文件写数据
fscanf()   → 读取文件中的数据
fclose()   → 关闭文件

启动程序
  ↓
读取之前保存的学生
  ↓
正常增删改查
  ↓
退出
  ↓
把学生数据保存到文件

这样才真正形成一个小型 C 项目。
```
#### 1.fopen():打开或创建、  fclose()
练习1：创建并打开文件

目标：程序运行后，在当前项目目录创建一个 students.txt，并判断文件是否打开成功。
```c
FILE* fp = fopen("students.txt", "w");
if (fp == NULL) {
	printf("打开失败\n");
	return 1;
}
else {
	printf("打开成功\n");
}

fclose(fp);
```
```text
"w" 表示写入模式：
文件不存在 → 创建
文件存在 → 原来的内容会被清空
```

#### 2.fprint(): 输出到 fp 指向的文件
printf(...) → 输出到控制台

fprintf(fp, ...) → 输出到 fp 指向的文件

格式：
```c
Student s = { "Tom", 20, 90.5 };
FILE* fp = fopen("students.txt", "w");
fprintf(fp,"%s %d %.1f\n",s.name,s.age,s.score);
```

练习：写入 3 个学生
```c
Student students[3] = {
{"Tom", 20, 90.5},
{"Jack", 21, 85.0},
{"Lucy", 19, 95.5}
};
for (int i = 0; i < 3; i++) {
	fprintf(fp, "%s %d %.1f\n", students[i].name, students[i].age, students[i].score);
}
```

#### 3.文件打开模式（mode）
```text
| 模式|  含义   | 文件不存在  | 原内容 |
| "r" |  读取   | 打开失败   | 保留   |
| "w" |  写入   | 创建文件   | 清空   |
| "a" | 追加写入 | 创建文件  | 保留   |
```

#### 4.fscanf(fp, ...)
scanf()       ← 从键盘读取

fscanf(fp)    ← 从 fp 指向的文件读取

fscanf() 的返回值表示：成功读取了几个数据项。

格式：
```c
Student s;
FILE* fp = fopen("student.txt", "r");
fscanf(fp, "%s %d %lf", s.name,&s.age,&s.score);
fclose(fp);//读取完也要关闭文件
```
练习：读取 3 个学生
```c
Student stu[3]；//为了和students区分，读取需要新的数组
for (int i = 0; i < 3; i++) {
	fscanf(fp, "%s %d %lf\n", stu[i].name, &stu[i].age, &stu[i].score);
}
print_students(stu,3);
fclose(fp);
```


#### 写入学生管理系统
```text
把现在的：固定 3 个学生 → 写文件 → 读文件
变成：
Student* p 动态学生数组 → 保存当前所有学生 → 程序退出前保存 → 下次启动时读取
```


1.文件保存函数
```c
void save_students(Student* p, int size)
{
    // 1. 打开 students.txt
    // 2. 判断是否打开成功
    // 3. 循环，把所有学生写进去
    // 4. 关闭文件
}
```

2.从文件读取学生，把文件中的所有学生追加到当前数组。
```c
void load_students(Student**pp,int* size) {
```
你事先不知道文件里有多少个学生。
先判断再申请空间
```text
students.txt
     ↓
 Student stu 临时变量
     ↓
 fscanf()
     ↓
读取成功？
  ↓       ↓
 是       否
 ↓         ↓
realloc   结束
 ↓
(*pp)[*size] = stu //把临时学生复制到动态数组最后一个位置
相当于p[*size]
 ↓
(*size)++

```


问题：
```text
1.如果 students.txt 里面有 10 个学生，而你一开始只有 Student* p = NULL；int size=0
你准备怎么让 p 逐渐装下这 10 个学生？
realloc（） //二级指针

2.还不能判断“文件有没有读完”。
根据数据项是不是3 判断
int result = fscanf(fp, "%s %d %lf", (*pp + *size)->name, &(*pp + *size)->age, &(*pp + *size)->score);

3.最终会重复读取：
原因：每次都从p[*size]开始往后添加。所以它天然就是“追加”。
解决：用文件内容重新建立当前学生数组，而不是追加。
这时候 load_students() 开始前就应该变成：
size = 0;
p = NULL;
//注意：
如果原来：p → [Tom][Jack]
你直接：*pp = NULL; 原来的内存地址就丢了。
这会造成：内存泄漏

//正确思路应该是：
原来的学生数据
        ↓
     free(p)
        ↓
   p = NULL
   size = 0
        ↓
重新从文件读取
```
```c
case 8:
    free(p);
    p = NULL;
    size = 0;

    load_students(&p, &size);

    printf("读取到 %d 个学生\n", size);
    print_students(p, size);
    break;
```
```text
4.加（）
case 3:
    char name1[20];

最好以后写成：

case 2: {
    char name[20];

    ...
    break;
}
这样每个 case 有自己的作用域。
```


#### 设计
```text
程序启动
p = NULL
size = 0
       ↓
load_students()
       ↓
读取文件
用户添加
add_student()
       ↓
size 增加
用户删除
delete_student()
       ↓
size 减少
用户修改
size 不变
用户点击「7.保存」
当前 p
  ↓
写入 students.txt
用户点击「8.读取」
当前 p
  ↓
free()
  ↓
p = NULL
size = 0
  ↓
重新读取 students.txt

这样就不会重复。
```


### 总结
```text
                学生管理系统
                     │
        ┌────────────┼────────────┐
        ↓            ↓            ↓
     学生数据      功能操作       文件
        │            │            │
 Student* p      添加/删除/修改   保存/读取
 int size        查找/排序
```

```text
Student
│
├── 动态内存
│   ├── create_student()   ← malloc练习
│   ├── revise()           ← realloc练习
│   └── add_student()      ← 实际使用
│
├── 基本操作
│   ├── add_student()
│   ├── delete_student()
│   ├── find_student()
│   ├── change_student_by_name()
│   └── print_students()
│
├── 高级操作
│   └── sort_by_score()
│
└── 文件
    ├── save_students()
    └── load_students()
```


最终main()流程
```text
程序启动
   ↓
p = NULL
size = 0
   ↓
load_students(&p, &size)
   ↓
显示菜单
   ↓
用户选择
   ├── 1 添加
   ├── 2 删除
   ├── 3 修改
   ├── 4 查找
   ├── 5 显示
   ├── 6 排序
   ├── 7 保存
   ├── 8 读取
   └── 0 退出
             ↓
          free(p)
```




