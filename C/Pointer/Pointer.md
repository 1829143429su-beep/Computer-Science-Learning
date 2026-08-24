# C语言

##  1.指针

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


### 重点：

int a = 10;

int* p = &a;

创建一个int*类型的变量p，让它保存a的地址

### 彻底搞懂

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

### 练习
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

#### 数组名与地址
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

#### 访问数组的第 i 个元素
arr[i];

*(arr+i);

p[i];

*(p+i);

#### 指针遍历数组
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

### 练习
#### 求数组最大值

#### 求数组最小值

#### 求平均值

#### 查找元素

#### 数组逆序
```text
p1 → 第一个
p2 → 最后一个
交换
↓
p1++
p2--
再交换
↓
p1++
p2--
直到两个指针相遇
```
#### 冒泡排序
核心思想非常简单：

比较相邻的两个元素，如果前面的比后面的大，就交换。

需要进行很多轮，每一轮都会选出一个最大元素，下一轮只需剩下的元素进行比较

int arr[5] = {3，8，2，10，5};


## 指针与函数
```
void swap(int* a, int* b);
```
#### 为什么函数参数使用指针后，可以修改外部变量?
传值交换：函数只能修改副本
```text
内void swap1(int a,int b);
外swap1(x,y);
外部：x = 5
     y = 10
       ↓ 复制值
函数内部：
     a = 5      ->    a=10
     b = 10    交换    b=5
x、y没有参与交换
函数结束：a、b被销毁；x、y保持不变
```

指针交换：函数通过地址修改原变量
```c
void swap2(int* a,int* b)
swap2(&x,&y);
x = 5              y = 10
 ↑                   ↑
a 保存 x 的地址      b 保存 y 的地址
```
#### 指针作为函数参数处理数组
```
swap()

max()
int array_max(int* arr, int size)；

min()

sort() 排升序
void array_sort(int* arr, int size)

reverse()数组逆序
void array_reverse(int* arr, int size)
```
#### 指针作为返回值


#### 函数指针先了解，不需要深入
int (*p)(int, int);//p 是一个函数指针，它指向一个“接收两个 int、返回 int”的函数。
```text
函数：
返回值  函数名(参数)
int* p = &a;
*p

函数指针：
返回值  (*指针名)(参数)
int (*p)(int, int) = add;
p(3, 5)
```

```text
int
 ↓
函数返回 int

(*p)
 ↓
p 是一个指针

(int, int)
 ↓
这个函数接收两个 int 参数
```


## 字符串与字符指针
```c
char str[] = "hello";
char* p = str;
```

#### 重点：
char：用来存储一个字符
```text
char ch = 'A';//单引号用来表示字符
```
字符数组：多个字符可以放进数组
```text
char str[5] = {'h', 'e', 'l', 'l', 'o'};
```
字符串：C 语言规定，字符串必须以 '\0' 作为结束标志。
```text
char str[] = {'h', 'e', 'l', 'l', 'o', '\0'};才是完整的字符串。
char str[] = "hello";//编译器会自动加上'\0'
字符串输出 %s
```

```text
当 C 语言处理字符串时，它不知道数组有多长。
它采用的规则是：
一直往后读取，直到遇到 '\0'。
```

char* p=str;//即字符型指针加字符数组
```text
str -> 'h'
p -> str[0]
*p='h'
```

指针移动：
```c
p++;// p ->'e'
p++;// p ->'l'
```

遍历
```c
普通数组：p < arr + size

字符串：*p != '\0'
```

%zu:printf() 中用于输出 size_t 类型的格式说明符
```c
标准库的 strlen() 返回的就是 size_t
char str[] = "hello";
size_t len = strlen(str);
这里 strlen(str) 返回的是size_t  而不是 int。
所以输出printf("%zu\n", len);

%zu
 ││
 │└── u：无符号整数
 └── z：size_t
%zu = 输出 size_t 类型的无符号整数。
```

```text
变量类型	     printf
int	            %d
unsigned int	%u
long	        %ld
unsigned long	%lu
float	        %f
double	        %f
char	        %c
字符串	        %s
size_t	        %zu
地址	        %p
```

#### strlen
strlen()用于取字符串的长度,不包括‘\0’

int my_strlen(char* str)
```
char str[] = "hello";
printf("%zu", strlen(str));//结果为5

h e l l o \0
←──5──→
```

#### strcpy
strcpy()用于字符串复制

strcpy(dest, src);

void my_strcpy(char* dest, char* src)
```text
从 src 一个字符一个字符复制到 dest：
src
 ↓
h e l l o \0

dest
 ↓
_ _ _ _ _ _
注意：最后的 '\0' 也必须复制。
```

#### strcmp
strcmp()：用于字符串对比

int my_strcmp(char* str1, char* str2)
```
两个字符串
   ↓
同时往后遍历
   ↓
逐个字符比较
   ↓
发现不同 → 判断大小
   ↓
一直相同直到 '\0' → 相等

"abc" 和 "abc"   // 相等
"abc" 和 "abd"   // str1 < str2
"abd" 和 "abc"   // str1 > str2
ASCII码比较
```

#### strcat
strcat()：用于字符串拼接

void my_strcat(char* dest, char* src)
```text
找到第一个字符串的 '\0'
        ↓
从这里开始写
        ↓
把第二个字符串复制过来
        ↓
最后补 '\0'

dest = "hello"
src  = " world"
        ↓
dest = "hello world"
```

dest 不能指向字符串常量：
```text
char* dest = "hello";//"hello" 是字符串字面量，不能拿它作为可写的目标空间。
char* src = "world";
*dest = *src;//相当于尝试修改 "hello"，这是错误的。

"hello"叫做字符串字面量。
它不是普通的字符数组变量，而是程序中的一段字符串数据。
可以粗略理解成：
"hello"
┌───┬───┬───┬───┬───┬────┐
│ h │ e │ l │ l │ o │ \0 │
└───┴───┴───┴───┴───┴────┘
```

char* dest = "hello";//dest 是一个指针，它指向 "hello" 的第一个字符。
```text
可以理解成：
"hello"所在的地址
       ↓
     dest
       ↓
┌───┬───┬───┬───┬───┬────┐
│ h │ e │ l │ l │ o │ \0 │
└───┴───┴───┴───┴───┴────┘
注意：指针本身可以改变，但是它指向的字符串字面量不能拿来修改。
dest++; //这是修改dest这个指针变量,没问题。
*dest = 'H'; //这是修改"hello"里面的字符,不可以。
你是在尝试：
hello
↑
把 h 改成 H
这种行为是未定义行为（Undefined Behavior）。
```

char dest[20] = "hello"; //这里创建的是一个真正的字符数组。
```text
可以理解成：
dest
 ↓
┌───┬───┬───┬───┬───┬────┬───┬───┐
│ h │ e │ l │ l │ o │ \0 │   │   │
└───┴───┴───┴───┴───┴────┴───┴───┘
这些空间属于 dest。
dest[0] = 'H'; //完全可以。
```

总结：
```text
1.char str[] = "hello";	一个字符数组，保存 "hello"，可以修改
2.char* str = "hello";	一个字符指针，指向 "hello"字符串字面量，只读
3.char* str[20];	一个数组，里面有 20 个 char*
str
 ↓
┌────────┬────────┬────────┬────────┐
│ char*  │ char*  │ char*  │  ...   │
└────────┴────────┴────────┴────────┘
    ↓
  "hello"
```

严谨写法
```text
char* src = "world"，却没问题？
代码对 src 只做了*src和src++
只是读取它，没有做 *src = ...的修改，所以没问题。

不过从更现代、更严谨的写法来说，可以写成：
const char* src = "world";
const 表示：我只读取 src 指向的字符串，不修改它。

void my_strcat(char* dest, const char* src)
这样就更加规范。
```

#### 综合练习2
输入两个字符串
    ↓
输出两个字符串长度
    ↓
复制第一个字符串
    ↓
比较两个字符串
    ↓
把两个字符串拼接起来
    ↓
输出最终结果
```c
#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<string.h>
//输出两个字符串长度
int my_strlen(char* dest) {
	int i = 0;
	while (*dest != 0) {
		i++;
		dest++;
	}//不包括'\0'
	return i;//int型函数需返回
}
//复制第一个字符串
//修改dest1
void my_strcpy(char* dest1, char* src) {
	while (*src != '\0') {
		*dest1 = *src;
		dest1++;
		src++;
	}
	*dest1 = '\0';
}
//比较两个字符串
int my_strcmp(char* dest, char* src) {
	while (*dest != '\0' && *src != '\0') {
		if (*dest == *src) {
			dest++;
			src++;
		}
		else {
			break;
		}
	}
	//遇到第一个'\0'后，开始判断是都遇到了还是只有一个结束了
	if (*dest == *src) {
		return 0;
	}
	else if (*dest > *src) {
		return 1;
	}
	else {
		return -1;
	}
}
//拼接两个字符串
	//会修改dest1,用字符数组
	void my_strcat(char* dest1, char* src) {
		while (*dest1 != '\0') {
			dest1++;
		}
		while (*src != '\0') {
			*dest1 = *src;
			dest1++;
			src++;
		}
		*dest1 = '\0';
	}

	int main() {
		//输入两个字符串
		char* dest = "hello";
		char dest1[20] = "hello";
		char* src = "world";

		//输出两个字符串长度
		printf("字符串长度分别是%zu,%zu", strlen(dest), strlen(src));
		int length1 = my_strlen(dest);
		int length2 = my_strlen(src);
		printf("字符串长度分别是%d,%d", length1, length2);

		//复制第一个字符串
		my_strcpy(dest1, src);
		printf("str复制dest1后得到：%s",dest1);//

		//比较两个字符串
		int result = my_strcmp(dest, src);//先运行或表示
		if (result == 1) {
			printf("%s>%s", dest, src);
		}
		else if (result== -1) {
			printf("%s<%s", dest, src);
		}
		else {
			printf("%s=%s", dest, src);
		}

		//把两个字符串拼接起来
		my_strcat(dest1, src);//先运行 再使用
		printf("拼接后dest为:%s",dest1 );

		return 0;
	}
```
