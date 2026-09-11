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
#### 1.结构体 + malloc
先理解：
```c
typedef struct
{
    char name[20];
    int age;
    double score;
} Student;
```
然后：
```c
Student* p = malloc(sizeof(Student));
```
##### 练习1：
动态创建一个学生，输入姓名、年龄、成绩，然后输出，最后 free()。

第 2 步：动态数组

从：

Student* p = malloc(sizeof(Student));

变成：

Student* p = malloc(sizeof(Student) * 3);

理解：

p
↓
┌────────┬────────┬────────┐
│Student │Student │Student │
│   0    │   1    │   2    │
└────────┴────────┴────────┘

然后复习你之前学的：

realloc()

实现“学生数量可以增加”。

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

