#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

//一、链式队列
typedef struct Node {
	int data;
	struct Node* next;
}Node;
typedef struct{
	Node* front;
	Node* rear;
}LinkQueue;


//1,初始化
void InitQueue(LinkQueue* q) {
	q->front = NULL;
	q->rear = NULL;

	printf("队列初始化成功！\n");
}

//2.入队
bool EnQueue(LinkQueue* q, int data) {
	Node* newNode = malloc(sizeof(Node));

	if (newNode == NULL) {
		printf("内存申请失败\n");
		return false;
	}

	//初始化新节点
	newNode->data = data;
	newNode->next = NULL;

	// 1. 判断队列是否为空
	if (q->front == NULL) {
		printf("队列为空\n");
		//如果为空，处理 front 和 rear
		q->front =q->rear= newNode;
	}
	else {
		//如果不为空，把新节点接到队尾
		q->rear->next = newNode;
		q->rear = newNode;
		//newNode->next=NULL;//初始化时已经执行
	}

	printf("成功入队:%d\n",data);
	return true;
}

//3，出队
bool DeQueue(LinkQueue* q, int* data) {
	if (q->front == NULL) {
		printf("队空，出队失败\n");
		return false;
	}

	Node* temp = NULL;
	if (q->front == q->rear) {
		temp = q->front;//front是节点类型，q是LinkQueue* 类型
		*data = temp->data;
		q->front = q->rear = NULL;
		free(temp);
	}
	else {
		temp = q->front;
		*data = temp->data;
		q->front = q->front->next;
		free(temp);
	}

	printf("%d出队成功\n",*data);
	return true;
}

//4.获取队头元素 
bool GetHead(LinkQueue* q, int* e) {
	if (q->front == NULL) {
		printf("队空，获取失败\n");
		return false;
	}

	*e = q->front->data;
	return true;
}

//5.计算队列长度 
int QueueLength(LinkQueue* q) {
	if (q->front == NULL) {
		printf("当前队列长度为 0\n");
		return 0;
	}

	Node* cur = q->front;
	int count = 0;
	while (cur) {
		cur = cur->next;
		count++;
	}

	return count;
}

//6.判断队列是否为空
bool QueueEmpty(LinkQueue* q) {
	if (q->front == NULL) {
		printf("队列为空\n");
		return true;
	}
	else {
		printf("队列不为空\n");
		return false;
	}
}
//简化版
bool QueueEmpty2(LinkQueue* q) {
	return q->front == NULL;
}

//7.清空队列 
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


//8.遍历队列 
void TraverseQueue(LinkQueue* q) {
	if (QueueEmpty(q)) {
		printf("队空,无法遍历\n");
		return;
	}

	Node* cur = q->front;
	while (cur) {
		printf("%d ", cur->data);
		cur = cur->next;
	}

	printf("遍历完成\n");
}

//9.链式队列菜单
void Menu(LinkQueue* q) {
	int choice;
	int data;
	do {
		printf("\n===== 链式队列菜单 =====\n");
		printf("1. 初始化队列\n");
		printf("2. 入队\n");
		printf("3. 出队\n");
		printf("4. 获取队头元素\n");
		printf("5. 计算队列长度\n");
		printf("6. 判断队列是否为空\n");
		printf("7. 清空队列\n");
		printf("8. 遍历队列\n");
		printf("0. 退出程序\n");
		printf("请选择操作：");

		scanf("%d", &choice);

		switch (choice) {
		case 1:
			if (q->front != NULL) {
				printf("队列已经初始化且包含元素，请先清空队列！\n");
			}
			else {
				InitQueue(q);
			}
			break;

		case 2:
			printf("请输入入队元素：");
			if (scanf("%d", &data) == 1) {
				EnQueue(q, data);
			}
			else {
				printf("输入无效！\n");
				while (getchar() != '\n');
			}
			break;

		case 3:
			if (DeQueue(q, &data)) {
				// DeQueue 内部已经输出出队结果
			}
			break;

		case 4:
			if (GetHead(q, &data)) {
				printf("队头元素为：%d\n", data);
			}
			break;

		case 5:
			printf("当前队列长度为：%d\n", QueueLength(q));
			break;

		case 6:
			QueueEmpty(q);
			break;

		case 7:
			ClearQueue(q);
			break;

		case 8:
			TraverseQueue(q);
			break;

		case 0:
			ClearQueue(q);
			printf("程序退出！\n");
			break;

		default:
			printf("输入无效，请重新选择！\n");
		}


	} while (choice!=0);
}

//10.销毁队列
void DestroyQueue(LinkQueue* q) {
	ClearQueue(q);
	printf("队列销毁成功\n");
	//这个版本只是清空节点，并输出销毁提示。
	// q 本身仍然存在，之后仍可再次入队。
}


//二、顺序队列

/*
#define MAXSIZE 100

typedef struct {
	int data[MAXSIZE];//存放队列元素的数组
	int front;//指向当前队头元素的下标
	int rear;//指向下一个可插入位置的下标
}SqQueue;

//1.初始化
void InitQueue(SqQueue* q) {
	q->front = q->rear = 0;
}

//2.入队
bool EnQueue(SqQueue* q,int data) {
	if (q->rear == 100) {
		printf("队满，入队失败\n");
		return false;
	}

	q->data[q->rear]=data;
	q->rear++;
	printf("入队成功:%d\n",data);
	return true;
}

//3.出队
bool DeQueue(SqQueue* q,int*e) {
	//判空
	if (q->front == q->rear) {
		printf("队空，出队失败\n");
		return false;
	}

	*e = q->data[q->front];
	q->front++;

	printf("%d出队", *e);
	return true;
}

//4.获取队头元素
bool GetHead(SqQueue*q,int*e){
	//判空
	if (q->front == q->rear) {
		printf("队空，无法获取\n");
		return false;
	}

	*e = q->data[q->front];
	printf("获取成功：%d\n", *e);
	return true;
}

//5.计算队列长度
int QueueLength(SqQueue* q) {
	int length =q->rear-q->front ;//rear是队尾元素下一个位置的下标
	printf("队长为%d", length);
	return length;
}

//6.判断队列是否为空
bool QueueEmpty(SqQueue* q) {
	if (q->front == q->rear) {
		printf("队列为空\n");
		return true;
	}
	else {
		printf("队列不为空\n");
		return false;
	}
}
//简化
bool QueueEmpty2(SqQueue* q) {
	return q->front == q->rear;
}

//7.遍历
void TraverseQueue(SqQueue* q) {
	if (QueueEmpty(q)) {
		printf("队列为空，无法遍历\n");
		return;
	}

	int order = q->front;
	while (order < q->rear) {
		printf("%d ", q->data[order]);
		order++;
	}
	printf("\n遍历完成\n");
}

//8.清空
void ClearQueue(SqQueue* q) {
	q->front = q->rear;
	printf("队列清空成功！\n");
}



//9.判断队列是否已满
bool QueueFull(SqQueue* q) {
	if (q->rear == MAXSIZE) {
		printf("队列已满\n");
		return true;
	}
	else {
		printf("队列未满\n");
		return false;
	}
}
bool QueueFull2(SqQueue* q) {
	return q->rear == MAXSIZE;
}
*/
int main() {
	LinkQueue q;
	InitQueue(&q);

	Menu(&q);
	return 0;
}