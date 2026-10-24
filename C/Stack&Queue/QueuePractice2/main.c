#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define MAXSIZE 5

typedef struct {
	int data[MAXSIZE];
	int front;
	int rear;
}CircleQueue;

//初始化
void InitCircleQueue(CircleQueue* q) {
	q->front = q->rear = 0;
}


//2.判断队列是否为空
bool CircleQueueEmpty(CircleQueue* q) {
	return q->front == q->rear;
}
bool CircleQueueEmpty2(CircleQueue* q) {
	if (q->rear == q->front) {
		printf("队列为空\n");
		return true;
	}
	else {
		printf("队列不为空\n");
		return false;
	}
}

//3. 判断队满
//预留一个空位
// 3. 判断队列是否已满
bool CircleQueueFull(CircleQueue* q) {
	return (q->rear + 1) % MAXSIZE == q->front;
}
bool CircleQueueFull2(CircleQueue* q) {
	if ((q->rear + 1) % MAXSIZE == q->front) {
		printf("队满\n");
		return true;
	}
	else {
		printf("队未满\n");
		return false;
	}
}

//4. 获取队列长度
int CircleQueueLength(CircleQueue* q) {
	return (q->rear - q->front + MAXSIZE) % MAXSIZE;
}

//5. 入队
bool EnCircleQueue(CircleQueue* q, int value) {
	if (CircleQueueFull(q)) {
		printf("队满，入队失败\n");
		return false;
	}
	//先存入数据，再移动rear
	q->data[q->rear] = value;
	q->rear =( q->rear + 1) % MAXSIZE;
	printf("%d入队成功\n", value);
	return true;
}

//6. 出队
bool DeCircleQueue(CircleQueue* q, int* e) {
	if (CircleQueueEmpty(q)) {
		printf("队空，无法出队\n");
		return false;
	}

	*e = q->data[q->front];
	q->front = (q->front + 1) % MAXSIZE;
	printf("%d出队成功\n", *e);
	return true;
}

//7. 获取队头元素
bool GetCircleQueueHead(CircleQueue* q, int* e) {
	if (CircleQueueEmpty(q)) {
		printf("队空，不存在队头元素\n");
		return false;
	}
	*e = q->data[q->front];
	return true;
}

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

//9. 清空队列
void ClearCircleQueue(CircleQueue* q) {
	q->front = q->rear;
	printf("队列已经清空\n");
}

//10.循环队列菜单
void menu(CircleQueue*q) {
	int choice;
	int value;
	int e;

	do {
		printf("\n========== 循环队列 ==========\n");
		printf("1. 入队\n");
		printf("2. 出队\n");
		printf("3. 获取队头\n");
		printf("4. 获取队列长度\n");
		printf("5. 判断队空\n");
		printf("6. 判断队满\n");
		printf("7. 遍历队列\n");
		printf("8. 清空队列\n");
		printf("0. 退出\n");
		printf("请输入选项：");

		if (scanf("%d", &choice) != 1) {
			printf("输入无效，程序退出\n");
			return;
		}


		switch(choice){
		case 1:
			printf("请输入入队元素：");
			if (scanf("%d", &value) != 1) {
				printf("输入无效，程序退出\n");
				return;
			}
			EnCircleQueue(q, value);
			break;

		case 2:
			if (DeCircleQueue(q, &e)) {
				printf("取出的元素：%d\n", e);
			}
			break;

		case 3:
			if (GetCircleQueueHead(q, &e)) {
				printf("队头元素：%d\n", e);
			}
			break;

		case 4:
			printf("队列长度：%d\n", CircleQueueLength(q));
			break;

		case 5:
			if (CircleQueueEmpty(q)) {
				printf("队列为空\n");
			}
			else {
				printf("队列不为空\n");
			}
			break;

		case 6:
			if (CircleQueueFull(q)) {
				printf("队列已满\n");
			}
			else {
				printf("队列未满\n");
			}
			break;

		case 7:
			TraverseCircleQueue(q);
			break;

		case 8:
			ClearCircleQueue(q);
			printf("队列已清空\n");
			break;

		case 0:
			printf("退出循环队列程序\n");
			break;

		default:
			printf("选择无效，请重新输入\n");
		}
	} while (choice != 0);
}


int main() {
	CircleQueue q;

	InitCircleQueue(&q);
	menu(&q);

	return 0;
	return 0;
}