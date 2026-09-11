## 结构体 + 动态内存 → 学生管理系统

### 第 1 步：结构体 + malloc
先理解：

typedef struct
{
    char name[20];
    int age;
    double score;
} Student;

然后：

Student* p = malloc(sizeof(Student));

练习：

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

最终结构

最后我们的学生管理系统大概会变成：

学生管理系统
│
├── 添加学生
├── 删除学生
├── 修改学生
├── 查找学生
├── 显示学生
├── 按成绩排序
├── 保存到文件
└── 退出
