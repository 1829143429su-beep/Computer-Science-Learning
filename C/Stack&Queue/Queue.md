## 队列
先进先出

### 基本操作
```text
入队 EnQueue()：把元素添加到队尾。
出队 DeQueue()：从队头删除元素，并取出该元素。
```

### 链式队列
```text
链式队列本质上也是由节点连接起来的链表，只不过它有明确的队头和队尾。

front:指向队头，出队时从这里删除节点。
rear:指向队尾，入队时从这里添加节点。

为什么两个指针都需要？
- 如果只有 front，想要在队尾插入新节点，就得从头遍历到最后一个节点，时间复杂度是 O(n)。
- 如果同时维护 rear，就可以直接找到队尾，在队尾插入，时间复杂度是 O(1)。
```

#### 结构体定义：
```c
typedef struct Node {
	int data;
	struct Node* next;
}Node;

typedef struct{
	Node* front;
	Node* rear;
}LinkQueue;
//LinkQueue 本身不直接存储 10、20、30，它保存的是两个指针，用来找到链表中的节点。
```

#### 1.初始化
```c
void InitQueue(LinkQueue* q)
{
    q->front = NULL;
    q->rear = NULL;

    printf("队列初始化成功！\n");
}
```

#### 2.入队

#### 3.出队
```text
temp = q;//😢
这里的 q 是 LinkQueue* 类型，指向整个队列结构体；而 temp 是 Node* 类型，应该指向节点。
你要释放的是队头节点，而不是整个队列结构体，所以应该写：
temp = q->front;
即使队列只有一个节点，q->front 也指向那个节点。
```
```text
int* data; //是指针，保存的是一个地址。

这句把出队元素的值存入了 data 指向的变量。因此，输出时应该写：
printf("%d 出队成功！\n", *data);
```


#### 4.获取对头元素
```c
bool GetHead(LinkQueue* q, int* e) 
```

#### 5.计算队列长度 
```c
int QueueLength(LinkQueue* q) 
```

#### 6.判断队列是否为空
```c
//简化版
bool QueueEmpty2(LinkQueue* q) {
	return q->front == NULL;
}
```

#### 7.清空队列 
```c
void ClearQueue(LinkQueue* q) {
	if (QueueEmpty(q)) {
		printf("队空\n");
		return;
	}
	
	Node* temp =NULL;
	while (q->front) {
		temp = q->front;
		q->front = temp->next;
		free(temp);
	}

	//将 front 和 rear 都设为 NULL
	q->front = q->rear = NULL;
	printf("清空成功\n");
}
```

#### 8.遍历队列
```c
void TraverseQueue(LinkQueue* q)
```
#### 9.菜单

#### 10.销毁队列
```c
void DestroyQueue(LinkQueue* q) {
    ClearQueue(q);
    printf("队列销毁成功\n");
}
```

区别
```text
清空队列 ClearQueue()
释放所有节点，保留队列对象；清空后可以继续使用。

销毁队列 DestroyQueue()
概念上是结束队列的使用并释放它占用的资源。若队列对象本身由动态内存分配，还需要释放队列对象本身。
例如，如果队列对象本身是动态分配的：
LinkQueue* q = malloc(sizeof(LinkQueue));
那么销毁时才需要在清理节点之后，再执行：
ClearQueue(q);
free(q);
q = NULL;
```


### 顺序队列
```text
与链式队列相比：
- 链式队列：每个节点通过指针连接，入队时通常需要动态申请内存。
- 顺序队列：使用数组存储，访问简单，但普通线性队列可能出现数组前面有空位、队尾却无法继续入队的情况。
```

#### 结构体定义
```c
#define MAXSIZE 100

typedef struct {
	int data[MAXSIZE];//存放队列元素的数组
	int front;//指向当前队头元素的下标
	int rear;//指向下一个可插入位置的下标
}SqQueue;
```

### 基本操作
#### 1.初始化
```c
void InitQueue(SqQueue* q) {
	q->front = q->rear = 0;
}
```

#### 2.入队
注意判断队满
```c
bool EnQueue(SqQueue* q,int data) {
	if (q->rear == 100) {
		printf("队满，入队失败\n");
		return false;
	}

	q->data[q->rear]=data;
	q->rear++;
	printf("入队成功\n");
	return true;
}
```

#### 3.出队
判空
```c
// 3. 出队
bool DeQueue(SqQueue* q, int* e) {
    // 判空
    if (q->front == q->rear) {
        printf("队空，出队失败\n");
        return false;
    }

    *e = q->data[q->front];
    q->front++;

    printf("%d 出队成功\n", *e);
    return true;
}
```

#### 4.获取队头元素
```c
bool GetHead(SqQueue*q,int*e)
```

#### 5.计算队列长度 
```c
int QueueLength(SqQueue* q) {
	int length =q->rear-q->front ;//rear是队尾元素下一个位置的下标
	printf("队长为%d", length);
	return length;
}
```
#### 6.判空
```c
bool QueueEmpty(SqQueue* q) {
    return q->front == q->rear;
}
```

#### 7.遍历
注意：遍历时不能修改 q->front，否则会改变队列的状态。
```
```
#### 8.清空
```c
void ClearQueue(SqQueue* q) {
    q->front = q->rear;
    printf("队列清空成功！\n");
}
```
普通顺序队列即使出队了，front 之前的数组空间也无法直接复用。

#### 9.判断队列是否已满
```c
bool QueueFull(SqQueue* q) {
    return q->rear == MAXSIZE;
}
```


### 循环队列
```text
循环队列的思路：让数组首尾相连。 当 rear 到达最后一个下标之后，就回到下标 0，继续利用空出来的位置。
```

理解取模运算 %
```text
假设数组长度为 5：
表达式	结果
0 % 5	0
1 % 5	1
4 % 5	4
5 % 5	0
6 % 5	1
所以：
rear = (rear + 1) % MAXSIZE;
就能让 rear 从 4 回到 0，实现循环。
```

判空/判满
```c
队空： front == rear；
队满： (rear + 1) % MAXSIZE == front；
```

#### 结构体定义
```c
#define MAXSIZE 5

typedef struct {
	int data[MAXSIZE];
	int front;//数组下标
	int rear;//数组下标
}CircleQueue;
```

#### 1.初始化
```c
void InitCircleQueue(CircleQueue* q)
{
    q->front = 0;
    q->rear = 0;
}
```
#### 2.判空
```c
bool CircleQueueEmpty(CircleQueue* q) {
    return q->front == q->rear;
}
```
当 front == rear 时返回 true，否则返回 false。

#### 3. 判断队满
```c
// 3. 判断队列是否已满
bool CircleQueueFull(CircleQueue* q) {
    return (q->rear + 1) % MAXSIZE == q->front;
}

//注意：循环队列需要预留一个数组位置。
```

#### 4. 获取队列长度
```c
int CircleQueueLength(CircleQueue* q);
//提示：由于下标可能绕回数组开头，需要使用取模运算。
```

#### 5. 入队
```c
bool EnCircleQueue(CircleQueue* q, int value);
```
```text
要求：
- 队满时，输出提示信息并返回 false。
- 未满时，将元素放到 rear 对应的位置。
- 更新 rear，返回 true。
```

#### 6. 出队
```c
bool DeCircleQueue(CircleQueue* q, int* e);
```
```text
要求：
- 队空时，输出提示信息并返回 false。
- 否则将队头元素保存到 *e。
- 更新 front，返回 true。
```

#### 7. 获取队头元素
```c
bool GetCircleQueueHead(CircleQueue* q, int* e);
```
```text
要求：
- 队空时返回 false。
- 否则将队头元素保存到 *e。
- 不能修改 front，因为这不是出队操作。
```

#### 8. 遍历队列
```c
//8. 遍历队列
void TraverseCircleQueue(CircleQueue* q) {
	if (CircleQueueEmpty(q)) {
		printf("队空\n");
		return;
	}
	int order = q->front;
	while (order!=q->rear) {
		printf("%d ", q->data[order]);
		order=(order+1)%MAXSIZE;
	}
	printf("\n遍历完成\n");
}
```
```text
要求：
- 队空时输出“队列为空”。
- 否则按队头到队尾的顺序输出元素。
- 遍历时使用局部变量，不能修改队列本身的 front 和 rear。
```

#### 9. 清空队列
```c
void ClearCircleQueue(CircleQueue* q);
//循环队列使用静态数组，不需要 free()，只需让队列恢复为空的状态。
```


### 对比
```text
对比项	               链队列	            普通顺序队列	        循环队列
存储方式	               链表节点	                连续数组	        连续数组
入队位置	           队尾节点后面	              rear 位置  	   rear 位置
出队方式	            删除队头节点	                front++	      front = (front+1)%MAXSIZE
是否需要动态分配内存	通常需要	不需要	           不需要
是否可能假溢出	  不会因数组位置耗尽而假溢出  	会	             解决了这种假溢出
主要限制          	内存分配与指针管理	数组尾部空间不能重复利用	预留一个空位来区分队空和队满
```


### 队列应用

#### 树的层次遍历
```text
结点1入队；
其左右孩子结点也入队，此时结点1出队；
如果没有左右孩子结点可以直接出队。
```
#### 图的广度优先遍历
```text
结点1入队；
和结点1相邻的结点有没有遍历过，没有遍历的都放在队尾；
结点1出队；
继续检查相邻节点2，看结点2的相邻结点有没有未被处理过的；
未处理的入队；
结点2出队
```

#### 在操作系统中
```text
多个进程争抢有限的系统资源，FCFS是一种策略；
可用队列实现
```
例子：打印数据缓冲区
```text
打印店，多个人传输打印文件
放在缓冲区（用“队列”组织打印数据）
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
