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
