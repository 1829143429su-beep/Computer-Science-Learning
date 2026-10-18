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
