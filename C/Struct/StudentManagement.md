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

也就是：

让函数更新外面的 p，使它指向扩容后的内存。
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
函数参数已经有：Student** pp
所以函数里面再写：Student* pp
相当于：同一个作用域里，把 pp 又定义了一次。
这是错误的。
```
#### 第 3 步：添加学生
realloc() //实现“学生数量可以增加”。

为什么 realloc 扩容后，第 4 个学生的数据需要我们重新输入，而前 3 个不用重新输入？

realloc(*pp, sizeof(Student) * new_size);//调整这块动态内存的大小，并尽可能保留原来的数据。

realloc 不是“清空后重新申请”。

它的核心作用是：改变已有动态内存块的大小，同时保留原有数据（在成功扩容的情况下）。

##### 练习3：添加学生,每次加1人
```c
void add_student(Student** pp,int* size) { //main中的size也要同步改
	(*size)++;//每次加1人
	Student* temp = realloc(*pp, sizeof(Student) * (*size));
	if (temp != NULL) {
		*pp = temp;
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

#### 第 5 步：修改 / 查找 / 显示 / 排序

这些你其实已经会了，只是把：

struct Student s[3];

变成：

Student* students;

所以这部分是知识迁移。

#### 第 6 步：保存文件

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

