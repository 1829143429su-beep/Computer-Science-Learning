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

##### 使用 fopen() 打开文件
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
##### 通过 fprintf() 将数据写入文件
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

##### fscanf():文件保存数据，变量接收读取出来的数据。
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


#### 2.如何在同一个程序中先写入文件，再读取文件。
如果你希望程序每次运行时都把新的联系人添加到文件末尾，而不是覆盖原来的内容
```text
fopen() 应该使用模式"a":追加	保留原内容，在末尾追加
"a" 模式下，如果文件不存在，通常会自动创建文件。
```
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
##### fwrite()：
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

##### fread():从文件读取结构体
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
fread(contacts, sizeof(Contact), 3, fp);//修改数据块数量，数组的地址不需要&

if (fread(contacts, sizeof(Contact), 3, fp) == 3) {
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
```


```
```
```
```
```
```
```



