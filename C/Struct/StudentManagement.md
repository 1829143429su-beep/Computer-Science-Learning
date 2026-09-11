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

### 第 2 步：动态数组
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
复习:
```c
realloc() //实现“学生数量可以增加”。
```
第 3 步：添加学生

例如：

当前学生：3人
        ↓
添加第4人
        ↓
realloc()
        ↓
现在：4人

第 4 步：删除学生

这个非常适合练你之前的数组知识：

Tom   80
Jack  90   ← 删除
Lucy  95
Bob   85

删除 Jack 后：

Tom   80
Lucy  95
Bob   85

本质上就是把后面的元素向前移动。

第 5 步：修改 / 查找 / 显示 / 排序

这些你其实已经会了，只是把：

struct Student s[3];

变成：

Student* students;

所以这部分是知识迁移。

第 6 步：保存文件

最后再加入：

fopen()
fprintf()
fclose()

这样才真正形成一个小型 C 项目。

```
```
```
```
```
```

