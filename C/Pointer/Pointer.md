# C语言指针

##  指针是什么

指针变量用于存储变量的地址。

例如：

```c
#include <stdio.h>

int main()
{
    int a = 10;
    int* p = &a;

    printf("a = %d\n", a);
    printf("a的地址 = %p\n", &a);
    printf("*p = %d\n", *p);

    return 0;
}
```


## 重点：

int a = 10;

int* p = &a;

创建一个int*类型的变量p，让它保存a的地址

## 彻底搞懂

a：变量本身 ->10

&a: &取地址运算符；得到a在内存中的地址 ->1000

```text
a
┌───────┐
│  10   │
└───────┘
  1000
```

p:指针变量，保存a的地址(p → &a) ->1000

*p：*解引用；去p保存的那个地址，找到里面的变量 ->10

  
指针类型

NULL

## 练习
#### 输出变量和地址
易混：
```c
printf("输入一个数：");
scanf("%d",p);//相当于给*p赋值，即给a赋值;p → a的地址 → 修改a
scanf("%d",&p);//&p → p的地址 → 修改p
p=&a;//给p赋值，赋的是p的地址
```
#### 使用指针修改变量

#### 使用指针交换两个变量
易错：
```c
 int a=4;
 int b=5;
 int* p1 = &a;
 int* p2 = &b;
 *p1=b;//此时p1指向变量a，赋了b值；即a=b=5
 *p2=a;//b=a=5
交换失败，缺少中间变量temp保存a
```
#### 使用指针遍历数组
```c
//使用数组下标遍历
void test_array()
{
    int arr[5] = { 1,2,3,4,5 };
    int* p = arr;
    for (int i = 0; i <5; i++) {
        printf("%d\n", arr[i]);
    }
}

//使用指针遍历
while循环

p++:让 p 指向下一个 int 元素。
如果 int 占 4 字节，那么底层地址可能是：
p       → 1000
p++     → 1004
p++     → 1008
p++     → 1012
所以指针的移动距离和指针类型有关。
```
#### 使用函数和指针修改变量
```c
调用函数
传地址
test_modify_with_function()
│
├── 创建 a
│
│   a = 4
│
├── 获取 a 的地址
│
│   &a
│
└── 把 &a 传给 test_modify1()
              │
              ↓
          int* p
              │
              ↓
             *p
              │
              ↓
          原来的 a
```
#### 综合练习1
```c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

//输出变量和地址
void test_address()
{
    int a = 4;
    int* p = &a;
    printf("a = %d\n", a);//变量a
    printf("*p = %d\n", *p);//*p是解引用，获取指针p指向的值，即a
    printf("a的地址是%p",p);//指针变量p，保存a的地址
    printf("a的地址是%p", &a);//&a取a的地址
}

//用指针修改变量
void test_modify() 
{
    int a = 4;
    int* p = &a;
    printf("输入想要修改的值：");
    scanf("%d", p);
   // *p = 10;
    printf("a=%d", a);
}

//使用指针交换两个变量
void test_swap()
{
    int a = 4;
    int b = 5;
    int* p1 = &a;
    int* p2 = &b;
    int temp = *p1;

    *p1=*p2;
    *p2=temp;
    printf("交换后，a=%d,b=%d", a, b);
}

//使用指针遍历数组
void test_array()
{
    int arr[5] = { 1,2,3,4,5 };
    int* p = arr;
    int i = 0;
    while (i < 5) {
        printf("%d\n", *p);
        i++;
        p++;
    }
}

//使用函数和指针修改变量
void test_modify1(int* p)
{
    int b=0;
    printf("输入修改后的值:");
    scanf("%d",&b);
    *p = b;
}
void test_modify_with_function()
{
    int a = 4;
    int* p = &a;
    printf("修改前a=%d\n", a);
    test_modify1(&a);//p也可以
    printf("修改后a=%d", a);
}

//NULL
void test_null()
{
    int* p = NULL;
    if (p == NULL) {
        printf("p没有指向任何对象\n");
    }
    int a = 10;
    p = &a;
    if (p != NULL) {
        printf("%d", *p);
    }
}
int main()
{
    test_null();
    return 0;
}
```
## 指针与数组
```text
int arr[5] = {1,2,3,4,5};
int* p = arr;
```

### 数组名与地址
```text
arr
 ↓
arr[0] 的地址

 p
 ↓
arr[0] 的地址

*p
 ↓
arr[0]


int* p = arr;
int* p = &arr[0];


p++
 ↓
arr[1]的地址

*p
 ↓
arr[1]的值
```

### 访问数组的第 i 个元素
arr[i];

*(arr+i);

p[i];

*(p+i);

### 指针遍历数组
```c
void test_array_with_pointer()
{
    int arr[5] = { 1,2,3,4,5 };
    int* p = arr;
   
    while (p < arr + 5) {    //arr+5是该数组末尾元素之后的位置
        printf("%d\n", *p);
        p++;
    }
arr
 ↓
┌─────┬─────┬─────┬─────┬─────┐
│  1  │  2  │  3  │  4  │  5  │
└─────┴─────┴─────┴─────┴─────┘
 ↑                                   ↑
arr                              arr + 5
```

## 练习
#### 求数组最大值
#### 求数组最小值
#### 求平均值
#### 数组逆序
#### 冒泡排序
#### 查找元素
