## 栈
#### 定义：
```text
栈是一种特殊的线性数据结构，它遵循：
后进先出（LIFO，Last In, First Out）
想象一下，你把几本书依次叠起来，最后放上去的书，通常最先拿走。
```
#### 存储分类：
栈可以用不同方式实现：
```
- 顺序栈：使用数组存储元素。
- 链栈：使用链表存储元素。
```

#### 栈的两个基本操作：
```text
push	入栈，把元素放进去	放入 40
pop	  出栈，取出栈顶元素	取出 30
```


## 顺序栈
### 结构体定义（按照1）
1.王道！！！！

top 是栈顶元素的下标，空栈时为 -1
```text
#define MAXSIZE 5

typedef struct {
    int data[MAXSIZE];  // 存储栈中元素
    int top;            // 栈顶下标

} SqStack;
```
2.教材
```text
#define MAXSIZE 100
typedef struct {
    int* base;     //指向栈底，也就是动态数组的起始位置
    int* top;      //指向栈顶元素的下一个位置！！！！
    int stacksize; //当前分配的存储空间可以的元素量
} SqStack;
```
```text
MAXSIZE	预先定义的初始容量	宏常量
stacksize	当前实际分配的容量	结构体成员变量
```
### 基本操作
#### 1.初始化
```c
void init_stack(SqStack* s)
{
    s->top = -1;
    printf("栈初始化成功！\n");
}
```
为什么参数是 SqStack* s？

因为我们要修改调用者的栈的 top。传入栈的地址后，通过 s->top 修改原来的结构体。

使用方式：
```c
SqStack s;
init_stack(&s);  //这里的 &s 就是把栈 s 的地址传给函数。
```

#### 2.入栈
先top++;再添加数据
```c
bool Push(SqStack*s,int data) {
	if (s->top == MAXSIZE-1) {
		printf("栈已满,入栈失败\n");
		return false;
	}
	s->top++;
	s->data[s->top] = data;

	printf("入栈成功：%d\n", data);
	return true;
}
```

#### 3.出栈
先保存数据，再top--
```c
bool Pop(SqStack* s,int *data) {
	if (s->top == -1) {
		printf("栈空，出栈失败\n");
		return false;
	}
	*data = s->data[s->top];
	s->top--;

	return true;
}
```
调用时：
```c
int e;
if (Pop(&s, &e)) {
    printf("出栈元素：%d\n", e);
}
```

#### 4.获取栈顶元素
```c
bool GetTop(SqStack* s, SElemType* e)
{
	if (s->top == -1) {
		printf("栈空\n");
		return false;
	}
	*e = s->data[s->top];
	return true;
}
```
```c
调用：
SElemType e;

if (GetTop(&s, &e)) {
    printf("栈顶元素是：%d\n", e);
}
```

#### 5.获取当前栈中有多少个元素
元素个数 = top + 1

#### 6.判断栈空
```c
bool StackEmpty(SqStack s) {
    return s.top == -1;
}
```

#### 7.清空栈
可以直接赋值，不需要循环
```
void ClearStack(SqStack* s) {
    s->top = -1;
    printf("栈已清空！\n");
}
//清空栈只需要修改有效元素的边界，不需要逐个删除数组中的元素。
//原来的 10、20、30 可能还留在数组内存中，但已经不属于栈的有效内容。
//另外，void 函数执行到末尾会自动返回，所以 return; 也可以省略。
```

#### 8.销毁栈
```text
清空栈和销毁栈在当前实现中没有明显的内存操作区别：
- 清空栈：把 top 设为 -1，栈还可以继续使用。
- 销毁栈：当前结构体不需要 free，因为没有单独申请堆内存；如果后续不再使用这个栈，让结构体变量生命周期结束即可。
```

### 练习

#### 1. 遍历栈
```
编写 TraverseStack(SqStack s)，从栈底到栈顶依次打印所有元素。空栈时输出提示。
提示：下标从 0 开始，遍历到 s.top 结束。
```

#### 2. 查找元素

基础
```text
编写 FindStack(SqStack s, SElemType target)，找到返回 true，否则返回 false。
提示：遍历有效元素 data[0] 到 data[top]。
```

#### 3. 计算指定元素出现次数
```text
编写 CountElement(SqStack s, SElemType target)，返回目标元素出现的次数。
提示：定义计数变量 count，遍历时匹配就加一。
```

#### 4. 获取栈顶元素并出栈
```text
编写 PopTop(SqStack* s)，成功时打印出栈元素，栈空时给出提示。
提示：可以复用你写好的 Pop 函数，不要重复实现全部逻辑。
```

### 综合练习
#### 5.菜单
```text
编写一个循环菜单，允许用户选择操作，直到选择退出。
菜单至少包含：
- 1：入栈
- 2：出栈
- 3：查看栈顶
- 4：查看栈长度
- 5：判断栈是否为空
- 6：遍历栈
- 7：清空栈
- 0：退出程序
要求： 每次操作都要输出明确结果；栈满、栈空时要处理异常情况。
```

```text
if (scanf("%d", &data) != 1)

scanf("%d", &data) 读取输入，保存到 data 中。
此时 data = 25。
scanf 成功读取了一个变量，因此它的返回值是 1。
判断 1 != 1，结果为假，不进入 if。
```
```text
case 0 里的 break 只负责跳出 switch，不是直接退出整个循环。真正让循环结束的是 while (choice != 0)。
```


#### 6. 利用栈实现字符串反转
```text
输入一个字符串，例如 hello，借助顺序栈反转后输出 olleh。
要求： 先将字符依次入栈，再依次出栈并输出。注意字符数组容量和字符串结束符 '\0'。
```
#### 7. 括号匹配检查
```text
判断表达式中的括号是否匹配，例如：
输入	结果
(a+b)*c	匹配
((a+b)	不匹配
(a+b))	不匹配
a+(b*c)	匹配
要求： 遇到左括号就入栈；遇到右括号时，检查栈是否为空，若不为空则出栈。最后检查栈是否为空。
先只处理圆括号 ( 和 )，不必考虑其他符号。
```

#### 8.用栈实现十进制转二进制
```text
输入一个非负整数，将其转换为二进制并输出。
例如：
输入：13
输出：1101
要求： 反复对数字除以 2，将余数入栈；再依次出栈输出余数。特别处理输入 0 的情况。
```




 
## 链式栈
### 对比
```text
顺序栈用固定大小的数组保存元素，top 记录栈顶下标。
10 20 30 空位
栈顶是 30。

链式栈：使用链表节点来保存元素，不需要提前定义固定的数组容量。
栈顶
30 -> 20 -> 10 -> NULL
节点通过指针连接，栈顶指向第一个节点。
我们约定：链式栈的栈顶放在链表头部，这样入栈和出栈都很方便。
```

### 结构体定义
```c
typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* top;//一个指针，而不是顺序栈里那种下标
} LinkStack;

//空链栈的 top = NULL
```

### 基本操作
#### 1.初始化
让栈顶指针指向空
```c
void InitStack(LinkStack* s) {
    s->top = NULL;
    printf("链式栈初始化成功！\n");
}
```

#### 2.入栈
```c
//2.入栈
bool Push(LinkStack* s, int data) {
	// 1. 创建新节点
	Node* newNode = malloc(sizeof(Node));


	// 2. 判断内存申请是否成功
	if (newNode != NULL) {
		printf("内存申请成功\n");
	}
	else {
		return false;
	}

	// 3. 给新节点赋值
	newNode->data = data;

	// 4. 让新节点指向原来的栈顶
	newNode->next = s->top;

	// 5. 更新栈顶指针
	s->top = newNode;

	return true;
}
```

#### 3.出栈
```c
bool Pop(LinkStack* s,int*e) {
	// 1. 判断栈是否为空
	if (s->top == NULL) {
		printf("栈空\n");
		return false;
	}

   // 2. 保存原来的栈顶节点
	Node* temp = s->top;

   // 3. 将栈顶节点的数据传给 e
	*e = s->top->data;

   // 4. 更新栈顶指针
	s->top = temp->next;

   // 5. 释放原栈顶节点
	free(temp);

	printf("出栈成功，元素为：%d\n", *e);
	return true;
}
```

#### 4.获取栈顶元素
```c
bool GetTop(LinkStack* s, int* e) {
	// 判断栈是否为空
	if (s->top == NULL) {
		printf("栈空\n");
		return false;
	}
	*e = s->top->data;
	return true;
```

#### 5.求栈长

#### 6.判空
```c
bool StackEmpty(LinkStack* s) {
    if (s->top == NULL) {
        printf("栈空\n");
        return true;
    }
    else {
        printf("栈非空\n");
        return false;
    }
}
```

#### 7.清空
释放链式栈中的所有节点，并将栈恢复为空栈
```c
void ClearStack(LinkStack* s) {
	if (StackEmpty(s)) {
		return;
	}

	Node* cur = s->top;
	//遍历
	while (cur) {
		Node* temp = cur;
		cur=cur->next;
		free(temp);
	}
	s->top = NULL;
	printf("栈已为空\n");
}
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



