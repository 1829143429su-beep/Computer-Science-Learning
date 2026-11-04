## 文件

### 理解：文件操作解决了什么问题
你之前写的学生管理程序，数据通常保存在内存中
```text
运行程序
    ↓
输入学生信息
    ↓
数据保存在内存中
    ↓
退出程序
    ↓
内存中的数据释放，数据丢失
```

加入文件操作后：
```text
运行程序
    ↓
读取文件中的数据
    ↓
数据加载到内存
    ↓
添加、修改、删除等操作
    ↓
将数据保存到文件
    ↓
退出程序
```
核心区别：内存用于程序运行时处理数据，文件用于持久保存数据。


### 掌握：
文件操作基础。能够把数据写入文件，再读取出来。
```text
- FILE*：文件指针
- fopen()、fclose()：打开和关闭文件
- fprintf()、fscanf()：格式化写入和读取
- fread()、fwrite()：二进制数据读写
- fopen() 失败、文件不存在、读写失败等错误处理
```

完成通讯录项目。退出程序后重新运行，联系人仍然存在。
```text
- 添加、删除、修改联系人
- 查找、显示、排序联系人
- 保存联系人到文件
- 启动程序时读取已有联系人
- 测试异常情况和数据持久化
```


#### 1.FILE* 和 fopen()
```text
fopen()：打开文件。
fprintf()：向文件写入数据。
fscanf()：从文件读取数据。
fclose()：关闭文件。
fp == NULL：判断文件是否打开失败。
fscanf(...) == 3：检查是否成功读取了三个数据项。
```

##### 1.1 使用 fopen() 打开文件
```c
FILE* fp = fopen("文件名.txt", "w");
```
##### 文件打开模式
```text
模式	 含义
"r"	  读取文件，文件必须存在
"w"	  写入文件，不存在则创建，旧内容清空
"a"	  追加写入，不存在则创建，原内容保留
"rb"	以二进制模式读取
"wb"	以二进制模式写入，不存在则创建，存在则清空
```
##### 1.2 通过 fprintf() 将数据写入文件
```c
fprintf(fp, "格式控制字符串", 变量列表);

fprintf(fp, "内容\n");
```

```c
#include<stdio.h>

int main(void) {
	FILE* fp = fopen("contacts.txt","w");
//声明一个文件指针，用于后续文件操作。
//以写入模式打开文件；如果文件不存在，通常会创建文件；如果文件已经存在，原有内容会被清空。

	if (fp == NULL) {
		printf("文件打开失败!\n");
		return 1;
	}

	printf("文件打开成功！\n");
  fprintf(fp, "张三 20 123456789\n");

  printf("联系人信息已写入文件！\n");
	fclose(fp);//关闭已经打开的文件。
	return 0;
}
```

为什么必须检查 fp == NULL？
```text
因为文件可能无法打开，例如路径不正确或没有相应权限。打开失败后，不能继续把这个指针当作有效文件来读写。
```

##### 1.3 fscanf():文件保存数据，变量接收读取出来的数据。
```c
fscanf(文件指针, "格式控制符", 变量地址);
```
```c
char name[20];
int age;
char phone[20];
fscanf(fp, "%19s %d %19s", name, &age, phone);
//%s 不限制读取的字符数量，可能导致数组越界。你可以加上宽度限制：
//因为数组长度是 20，需要预留一个位置存放字符串结束符 '\0'。
//在 C 语言中，数组名在大多数表达式中会自动转换为指向数组第一个元素的指针。
```
检查读取是否成功
```c
if (fscanf(fp, "%19s %d %19s", name, &age, phone) == 3) {//检查是否成功读取了 3 项
    printf("姓名：%s\n", name);
    printf("年龄：%d\n", age);
    printf("电话：%s\n", phone);
}
else {
    printf("读取失败！\n");
}
```
##### 以“r"模式打开文件：只读，文件必须存在
```c
int main(void) {
    FILE* fp = fopen("contacts.txt", "r");

    if (fp == NULL) {
        printf("文件打开失败！\n");
        return 1;
    }

    printf("文件打开成功！\n");

    char name[20];
    int age;
    char phone[20];

    // 读取文件，并检查是否成功读取3项
    if (fscanf(fp, "%19s %d %19s", name, &age, phone) == 3) {
        printf("姓名：%s\n", name);
        printf("年龄：%d\n", age);
        printf("电话：%s\n", phone);
    }
    else {
        printf("读取失败！\n");
    }

    fclose(fp);
    return 0;
}
```


#### 2.以“a"模式打开文件：保留原内容，在末尾追加
```text
"a" 模式下，如果文件不存在，通常会自动创建文件。
```
###### 如何在同一个程序中先写入文件，再读取文件。
如果你希望程序每次运行时都把新的联系人添加到文件末尾，而不是覆盖原来的内容
```c
原文件内容是：
张三 20 123456789

执行：
FILE* fp = fopen("contacts.txt", "a");
fprintf(fp, "李四 21 987654321\n");
fclose(fp);

文件就会变成：
张三 20 123456789
李四 21 987654321
```
##### 把用户输入的多个联系人追加写入文件。
要求：
```text
使用 fopen() 以 "a" 模式打开 contacts.txt。
定义三个变量，分别保存姓名、年龄和电话号码。
使用 scanf() 从终端输入联系人信息。
使用 fprintf() 将信息追加到文件，每个联系人占一行。
使用 fclose() 关闭文件。
```

```c
int main(void) {
	FILE* fp = fopen("contacts.txt","a");

	if (fp == NULL) {
		printf("文件打开失败!\n");
		return 1;
	}
	printf("文件打开成功！\n");

	char name[20];
	int age;
	char phone[20];
	printf("输入联系人的信息：\n");
	//scanf("%19s %d %19s", name, &age, phone);
	if (scanf("%19s %d %19s", name, &age, phone) != 3) {
		printf("输入格式错误！\n");
		fclose(fp);
		return 1;
	}
	fprintf(fp, "%s %d %s\n", name, age, phone);

	fclose(fp);
	return 0;
}
```

#### 3.fwrite() & fread()
对比：
```
fprintf() / fscanf()：按照格式读写数据。
fwrite() / fread()：按照指定的字节数写入或读取数据，常用于二进制文件，也可以读写结构体。
```
文件打开模式：
```text
"wb"：以二进制写入模式打开文件；文件不存在就创建，存在则清空原内容。
"rb"：以二进制读取模式打开文件。
```
##### 3.1 fwrite()：
格式：
```c
fwrite(数据起始地址, 每个数据块的大小, 数据块数量, 文件指针);
//fwrite() 的返回值是实际成功写入的数据块数量
```

把整个结构体直接写入二进制文件
```c
typedef struct {
    char name[20];
    int age;
    char phone[20];
} Contact;

int main(void) {
    Contact c = { "ZhangSan", 20, "123456789" };//

    FILE* fp = fopen("contact.dat", "wb");//以二进制写入模式打开文件
    if (fp == NULL) {
        printf("文件打开失败！\n");
        return 1;
    }

    if (fwrite(&c, sizeof(Contact), 1, fp) == 1) {//
        printf("联系人写入成功！\n");
    }
    else {
        printf("联系人写入失败！\n");
    }

    fclose(fp);
    return 0;
}
```

##### 3.2 fread():从文件读取结构体
格式：
```c
fread(数据存放地址, 每个数据块的大小, 数据块数量, 文件指针);
//fread() 的返回值是实际成功读取的数据块数量
```
```c
Contact c;

FILE* fp = fopen("contact.dat", "rb");

if (fp == NULL) {
    printf("文件打开失败！\n");
    return 1;
}

if (fread(&c, sizeof(Contact), 1, fp) == 1) {
    printf("姓名：%s\n", c.name);
    printf("年龄：%d\n", c.age);
    printf("电话：%s\n", c.phone);
}
else {
    printf("读取失败！\n");
}

fclose(fp);
```
如果文件里存储了 3 个联系人，而你希望一次读取这 3 个联系人;
```c
//假设它们保存在数组 Contact contacts[3] 中
Contact contacts[3];

if (fread(contacts, sizeof(Contact), 3, fp) == 3) {//修改数据块数量，数组的地址不需要&
    printf("成功读取 3 个联系人！\n");
}
else {
    printf("读取的联系人数量不足 3 个！\n");
}
//fread() 的返回值是实际成功读取的数据块数量。因此，可以这样判断是否读取了全部 3 个联系人：
```

##### 练习：联系人信息的二进制读写
任务要求:
```text
1. 创建一个 Contact 结构体数组，存放 3 个联系人。
2. 使用 fopen() 的 "wb" 模式打开 contact.dat。
3. 使用 fwrite() 一次性写入 3 个联系人，并检查是否写入成功。
4. 关闭文件。
5. 使用 "rb" 模式重新打开文件。
6. 使用 fread() 一次性读取 3 个联系人，并检查是否读取成功。
7. 使用 printf() 输出读取到的每个联系人的姓名、年龄和电话。
8. 最后关闭文件。

测试：
姓名	    年龄	电话
ZhangSan	20	  123456789
LiSi	    21	  987654321
WangWu	    22    111222333

注意： 写入和读取都要检查文件是否打开成功；读取前要重新打开文件。
```
```
写入后，先fclose(fp)，再打开文件，且需要fp保存一遍
fopen("contact.dat", "rb") 会返回一个新的文件指针，仍旧需要保存它；
否则fp 仍然是已经关闭的文件指针。
即：fp=fopen("contact.dat", "rb")
```
```c
int main(void) {
	//数组初始化
	Contact c[3] = {
		{"ZhangSan",20,"123456789"},
		{"LiSi",21,"987654321"},
		{"WangWu",22,"111222333"}
	};

	FILE* fp = fopen("contact.dat", "wb");
	if (fp == NULL) {
		printf("文件打开失败\n");
		return 1;
	}

	if (fwrite(c, sizeof(Contact), 3, fp) == 3) {
		printf("成功写入3个联系人\n");
	}
	else {
		printf("写入失败或者全部未写入\n");
	}

	fclose(fp);
	fp=fopen("contact.dat","rb");
	if (fread(c, sizeof(Contact), 3, fp) == 3) {
		printf("成功读取3个联系人\n");
		for (int i = 0; i < 3; i++) {
			printf("姓名：%s，年龄：%d，电话：%s\n",
				c[i].name, c[i].age, c[i].phone);
		}
	}
	else {
		printf("读取人数不足3个\\n");
	}

	fclose(fp);
	return 0;
}
```

```text
函数	     作用	            示例
fprintf()	按指定格式写入文本	fprintf(fp, "%s %d\n", name, age);
fscanf()	按指定格式读取文本	fscanf(fp, "%19s %d", name, &age);
fwrite()	将内存中的数据块写入文件	fwrite(c, sizeof(Contact), 3, fp);
fread()	    从文件读取数据块到内存	fread(c, sizeof(Contact), 3, fp);
```


#### 练习：文件操作的错误处理
```text
假设你要读取一个文件：
FILE* fp = fopen("contact.dat", "rb");
fread() 需要通过文件指针 fp 找到要读取的文件；

如果 fopen() 失败，fp 就是 NULL，此时没有有效的文件指针可供 fread() 使用，继续读取可能导致程序出错。
if (fp == NULL) {
    printf("文件打开失败！\n");
    return 1;
}

如果 fopen() 成功，文件也可能是空的，或者数据不足。之后还需要检查 fread() 的返回值。
if (fread(&c, sizeof(Contact), 3, fp) == 3) 
```


### 项目——通讯录
结构体、动态内存、文件操作
```text
1.添加联系人
2.显示联系人
3.查找联系人
4.删除联系人
5.修改联系人
6.保存联系人到文件，并在下次运行时读取
```

#### 1.结构体
```text
写出 Contact 结构体的定义，以及一个表示通讯录的结构体 AddressBook。

提示：
- Contact 表示一个联系人。
- AddressBook 表示整个通讯录。
- 通讯录需要保存联系人数组的指针，以及当前联系人的数量。
- 联系人数组使用动态内存分配，先不设置 capacity。
```

#### 2.初始化
```c
//初始化函数需要修改原来 AddressBook 变量中的成员，所以传入它的地址。
void init_addressbook(AddressBook* pb) {
    pb->contacts = NULL;
    pb->size = 0;
}
```

#### 3.添加第一个联系人
```c
//添加第一个联系人时，需要为联系人申请内存。
//
pb->contacts->name
strcpy(pb->contacts->name, "ZhangSan");
strcpy(pb->contacts->phone, "123456789");
```

```text
如果要让用户输入姓名、年龄和电话，应该使用 scanf()，而不是 fscanf()；
这取决于数据从哪里来：
scanf()：从键盘读取用户输入的数据。
fscanf()：从指定文件读取数据。

```

```c
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//联系人
typedef struct {
	char name[20];
	int age;
	char phone[20];
}Contact;

//通讯录
typedef struct {
	Contact* contacts;// 指向动态分配的联系人数组
	int size;   // 当前联系人数量
}AddressBook;

//初始化函数
void init_addressbook(AddressBook* pb) {
	pb->contacts = NULL;
	pb->size = 0;
}

//添加第一个联系人,并输入信息
int add_contact(AddressBook* pb) {
	pb->contacts = malloc(sizeof(Contact));
	if (pb->contacts == NULL) {
		printf("内存申请失败！\n");
		return 0;
	}


	printf("请输入第一位联系人的信息：\n");
	if (scanf("%19s %d %19s",
		pb->contacts->name,
		&pb->contacts->age,
		pb->contacts->phone) != 3) {
		printf("输入格式错误！\n");
		free(pb->contacts);//释放内存
		pb->contacts = NULL;//指向NULL
		pb->size = 0;//归零
		return 0;
	}

	//输入成功后再改size
	pb->size++;
	printf("联系人添加成功\n");
	
	return 1;
}
```



## 模块化编程
这一阶段主要学习三个文件如何协同工作：
```text
main.c
主函数：调用其他模块提供的功能

student.h
声明函数、定义类型

student.c
实现具体功能
```

### 学习：
```text
1.理解 .h 和 .c 的区别
学习函数声明与函数定义分离
2.学习 #include 和头文件保护
3.学习多个 .c 文件如何编译、链接
4.学习全局变量、extern、static
将已有的小程序拆分成多个文件
```

#### 1.举例说明
假设我们有一个计算两个整数之和的函数：

##### student.h
```c
int Add(int a, int b);
```
##### student.c
```c
#include "student.h"

int Add(int a, int b) {
    return a + b;
}
```
##### main.c
```c
#include <stdio.h>
#include "student.h"

int main(void) {
    int result = Add(10, 20);
    printf("结果：%d\n", result);
    return 0;
}
```
```text
student.h 告诉其他文件：存在一个 Add() 函数，它接收两个整数并返回一个整数。
student.c 真正编写 Add() 的功能。
main.c 只需要知道函数的声明，就可以调用它。
```

##### 问题1：为什么一个带分号，一个不需要；二者区别
```text
int Add(int a, int b);
函数声明以分号结束，表示声明到此结束。

int Add(int a, int b) { return a + b; }
函数定义以 {} 包含函数体，右花括号 } 表示定义结束，不需要再加分号。
```

##### 问题2：为什么 main.c 和 student.c 都要写 #include "student.h"
```text
1.在 main.c 中写：#include "student.h"
就能引入 student.h 中的函数声明,然后可以调用 student.c 中的 Add()

2.student.c 也要写： #include "student.h"
如果 student.c 中的函数定义不小心写成了 double Add(int a, int b)，它和头文件中的声明就不一致
引入头文件能帮助编译器检查这种不一致。

student.h：集中存放函数声明。
student.c：引入头文件，按照声明实现函数。
main.c：引入头文件，使用函数。
```

##### 问题3：#include 是把 student.h 中的内容复制到当前 .c 文件中吗？
```text
#include：负责引入文件内容，不负责实现函数。
```

##### 问题4：如果 main.c 只有函数声明，却没有函数定义，程序最终能正常运行吗？
```text
如果只有函数声明，没有函数定义，程序通常无法通过链接阶段。

需要区分两个阶段：
1. 编译阶段：main.c 通过头文件知道 Add() 的声明，因此可以检查调用是否正确。
2. 链接阶段：链接器需要找到 student.c 中 Add() 的具体实现，把它和 main.c 联系起来。
```

#### 2.头文件保护
```text
假设 main.c 中不小心两次引入了同一个头文件：
#include "student.h"
#include "student.h"
这样可能导致头文件中的声明被重复处理。
```
使用头文件保护：
```c
#ifndef STUDENT_H  //如果 STUDENT_H 还没有被定义，就执行下面的内容。
#define STUDENT_H 

int Add(int a, int b);

#endif  //结束条件编译区域

//小提醒：STUDENT_H 是我们自己起的标记名称，通常使用大写字母，并与头文件名对应。
```
执行过程：
```text
1. 第一次引入 student.h：STUDENT_H 尚未定义，于是执行下面的内容。
2. 执行 #define STUDENT_H，标记它已经定义。
3. 第二次引入 student.h：发现 STUDENT_H 已经定义，就跳过这部分内容。
```

#### 3.学习多个 .c 文件如何编译和链接
##### 问题1：编译时，应该只编译 main.c，还是 main.c 和 student.c 都要参与编译？
```text
main.c 和 student.c 都要参与编译和链接。

原因是：
- main.c 中有 main()，负责程序入口，也调用了 Add()。
- student.c 中有 Add() 的具体实现。
- student.h 提供函数声明，但它本身不提供函数实现。不需要单独编译。
```
使用 GCC 时可以这样编译：
```c
gcc main.c student.c -o program
```

##### 问题2：如果只编译 main.c，为什么链接器找不到 Add()？
```text
main.c 中虽然通过 student.h 知道了 Add() 的声明，但 Add() 的具体实现位于 student.c。
```
记住一个区别：
```text
- 编译：将每个 .c 文件编译成目标文件（如 .o）。
- 链接：将目标文件组合起来，解析函数调用与函数实现之间的关系。
```
例如：
```c
gcc -c main.c
gcc -c student.c
gcc main.o student.o -o program
```
解释：
```text
1.gcc -c main.c

gcc：调用 GCC 编译器。
-c：只编译，不进行链接。//!!!!!!
main.c：需要编译的源文件。
//执行后会生成main.o
main.o 是目标文件，里面包含编译后的机器代码，但还不是可以独立运行的完整程序。

2.gcc main.o student.o -o program
main.o：包含 main()，以及对 Add() 的调用。
student.o：包含 Add() 的具体实现。
-o program：指定最终生成的可执行文件名称为 program。
链接器会找到 main.o 中需要的 Add()，并将它与 student.o 中的实现对应起来。
最终生成：program //这就是可以运行的程序。
```

#### 4.extern 和 static，学习多个文件之间如何使用全局变量。
##### 问题1：如何让多个 .c 文件访问同一个全局变量？
```text
假设有两个文件。
1.student.c：
int count = 10;

2.main.c：
#include <stdio.h>

int main(void) {
    printf("%d\n", count);
    return 0;
}

//这段代码不能正常编译。
student.c 中定义了全局变量 count，但 main.c 并不知道这个变量的存在。
//需要用 extern 告诉 main.c：
“有一个 count 变量，它是在其他地方定义的，你可以使用它。”
```
修改：
```c
//student.c
int count = 10;//定义全局变量

//main.c
#include <stdio.h>

extern int count; //声明其他地方定义的变量

int main(void) {
    printf("%d\n", count);
    return 0;
}

//编译时：
gcc main.c student.c -o program
//运行结果：
10
```
```text
int count = 10;	定义全局变量
extern int count;	声明其他地方定义的变量
通常，一个全局变量只在一个 .c 文件中定义，其他文件通过 extern 声明后使用。
```

#### 理解 extern
```text
它是一个外部变量声明：
- extern：告诉编译器，这个变量在其他地方定义。
- int count：告诉编译器，这个变量的类型和名称。
- 末尾的分号：表示声明结束。
```

##### 问题2：重复定义
```text
如果 main.c 中写：int count = 20;
而 student.c 中也有：int count = 10;
两个文件都定义了一个具有外部链接属性的全局变量 count。

当两个文件一起编译、链接时，链接器会发现：
- main.c 定义了一个 count
- student.c 也定义了一个 count
它无法确定应该使用哪个定义，因此通常会报错：multiple definition of count（重复定义）。
```


##### 问题3：如果我希望 count 只能在 student.c 文件内部使用，其他 .c 文件都不能访问，应该怎么做？
解决：
```c
//student.c 
static int count = 10;
//这里的 static 改变的是全局变量的链接属性，不是它的生命周期。它仍然在整个程序运行期间存在。
```

对比：
```text
int count = 10;	普通全局变量，其他文件可以通过 extern 声明使用
static int count = 10;	限制在当前 .c 文件内部使用
extern int count;	声明其他地方定义的外部变量
```


```
```
```
```



```
```
```
```



```
```
```
```

```
```
```
```

```
```
```
```

```
```
```
```


```
```
```
```
