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
#### 结构体定义（按照1）
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

#### 4获取栈顶元素
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




```

```









