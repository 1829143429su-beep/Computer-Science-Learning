#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct Node{
	int data;
	struct Node* next;
}Node;

typedef struct {
	Node* top;
}LinkStack;

//基本操作
//1.初始化
void init(LinkStack*s) {
	s->top = NULL;
	printf("链式栈初始化成功！\n");
}

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

//3.出栈
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

//4.获取栈顶元素
bool GetTop(LinkStack* s, int* e) {
	// 判断栈是否为空
	if (s->top == NULL) {
		printf("栈空\n");
		return false;
	}
	*e = s->top->data;
	return true;
}

//5.求栈长
void StackLength(LinkStack* s) {
	if (s->top == NULL) {
		printf("栈长：0\n");
		return;
	}

	Node* cur = s->top;
	int length = 0;
	while (cur) {
		cur = cur->next;
		length++;
	}

	printf("栈长:%d", length);
}

//6.判空
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

//7.清空
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


//8.遍历
void TraverseStack(LinkStack* s) {
	if (StackEmpty(s)) {
		return;
	}

	//遍历指针
	Node* cur = s->top;
	while (cur) {
		printf("%d ", cur->data);
		cur = cur->next;
	}
}

//菜单
void menu(LinkStack* s) {
	int choice;

	do {
		printf("\n========== 链式栈菜单 ==========\n");
		//printf("1. 初始化栈\n");
		printf("2. 入栈\n");
		printf("3. 出栈\n");
		printf("4. 获取栈顶元素\n");
		printf("5. 求栈长\n");
		printf("6. 判断栈是否为空\n");
		printf("7. 清空栈\n");
		printf("8. 遍历栈\n");
		printf("0. 退出程序\n");
		printf("==============================\n");
		printf("请选择：");

		scanf("%d", &choice);

		switch(choice) {
			
			case 2: {
				// 入栈
				int data;
				printf("请输入要入栈的元素：\n");
				scanf("%d", &data);
				Push(s, data);
				break;
			}
			case 3: {
				// 出栈
				int e;
				if (Pop(s, &e)) {
					printf("%d", e);
				}
				break;
			}
			case 4: {
				// 获取栈顶元素
				int e;
				if (GetTop(s, &e)) {
					printf("栈顶元素：%d", e);
				}
				break;
			}
		    
		   // 5. 求栈长
			case 5:
				StackLength(s);
				break;

				// 6. 判断栈是否为空
			case 6:
				if (StackEmpty(s)) {
					printf("当前栈为空！\n");
				}
				else {
					printf("当前栈非空！\n");
				}
				break;

				// 7. 清空栈
			case 7:
				ClearStack(s);
				break;

				// 8. 遍历栈
			case 8:
				printf("栈顶 -> ");
				TraverseStack(s);
				printf("NULL\n");
				break;

			case 0:
				printf("退出程序\n");
				break;
			default:
				printf("输入错误，请重新选择！\n");
		}
	} while (choice!=0);
}







int main() {
	LinkStack s;
	init(&s);
	menu(&s);
	return 0;
}