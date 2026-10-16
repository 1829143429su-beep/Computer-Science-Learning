#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
	int data;
	struct Node* prev;
	struct Node* next;
}Node;

//创建第一个双向链表节点
Node* create_node(int data)
{
	Node* newNode = malloc(sizeof(Node));

	newNode->data = data;
	newNode->prev = NULL;
	newNode->next = NULL;

	return newNode;
}


//1.删除cur指向的结点
void delete_node(Node**pp,Node* cur) {
	//只有一个结点
	if (cur->prev == NULL && cur->next == NULL) {
		*pp = NULL;
	}
	//删除的是头结点
	else if (cur->prev == NULL) {
		*pp = cur->next;//更新头结点
		cur->next->prev = NULL;
	}
	// 删除尾节点
	else if (cur->next == NULL)
	{
		cur->prev->next = cur->next;
	}
	//删除中间结点
	else {
		cur->prev->next = cur->next;
		cur->next->prev = cur->prev;
	}
	free(cur);
}

//2.在指定节点cur后面插入节点
void insert_after(Node* cur, int data)
{
	Node* newNode = create_node(data);

	if (cur->next == NULL) {
		// cur 是尾节点
		cur->next = newNode;
		newNode->prev = cur;
	}
	else {
		// cur 后面原本有节点
		newNode->next = cur->next;
		cur->next->prev = newNode;  // ⭐ 不能漏
		cur->next = newNode;
		newNode->prev = cur;
	}
}


//2.2在 cur 前面插入结点
void insert_before(Node**pp,Node* cur, int data) {

	Node* newNode = create_node(data);

	//首节点
	if (cur->prev == NULL) {
		newNode->next = cur;
		cur->prev = newNode;
		newNode->prev = NULL;

		*pp = newNode;
	}
	else {
		cur->prev->next = newNode;
		newNode->prev =cur->prev;
		newNode->next = cur;
		cur->prev = newNode;
	}
}

//3.从前往后遍历：
void print_forward(Node* head) {
	Node* cur = head;
	while (cur != NULL) {
		printf("%d", cur->data);
		cur = cur->next;
	}
}

//3.2从后往前遍历：
//寻找尾结点
Node* get_tail(Node* head)
{
	if (!head) {
		return NULL;
	}
	Node* cur = head;
	while (cur->next) {
		cur = cur->next;
	}
	return cur;
}
void print_backward(Node* head) {
	Node* cur = get_tail(head);
	while (cur) {
		printf("%d", cur->data);
		cur = cur->prev;
	}
}

//一、基本操作：
// 1.按值查找
Node* find_node(Node*head,int value) {
	Node* cur = head;
	
	while (cur) {
		if (cur->data == value) {
			return cur;
		}
		cur = cur->next;
	}

	return NULL;
}
//2.修改结点
// 3.统计长度
// 4.查找最大值

//5.删除双向链表中第一个值等于 target 的节点。
void delete_first(Node**pp,int target) {
	Node* cur = *pp;//但这不代表之后修改 cur，也会修改 *pp。

	//判空
	if (!cur) return;

	//首元素且只有一个元素
	if (cur->data == target&&cur->next==NULL) {
		cur->prev = NULL;
		cur->next = NULL;
		free(cur);
		*pp = NULL;//把唯一节点删除后，头指针也要更新为空指针
		return;
	}

	//首元素但不止一个
	if (cur->data == target) {
		Node* p = cur;
		cur = cur->next;
		cur->prev = NULL;
		free(p);
		*pp = cur;//更新头指针
		return;
	}

	//此时确定首元素不是target，不知道后面还有没有元素；
	//中间元素,双链表不需要刻意找前驱，有prev指针
	while (cur->next) {
		if (cur->data == target) {
			Node* p = cur;//临时指针
			cur->prev->next = cur->next;
			cur->next->prev = cur->prev;
			free(p);
			return;
		}
		cur = cur->next;
	}

	//此时cur指向尾元素
	//尾元素删除
	if (cur->data == target) {
		Node* p = cur;
		cur->prev->next = NULL;
		free(p);
		return;
	}
}

void delete_first2(Node** pp, int data)
{
	Node* cur = *pp;

	//遍历查找指定节点
	while (cur) {
		if (cur->data == data) {
			delete_node(pp, cur);
			return;
		}
		cur = cur->next;
	}
}

//6.删除所有指定值的节点
void delete_all(Node** pp, int data)
{
	Node* cur = *pp;
	
	while (cur) {
		if (cur->data == data) {
			Node* cur2 = cur->next;
			delete_node(pp, cur);
			cur = cur2;
		}
		else
		{
			cur = cur->next;
		}
	}
}

//二、插入与删除进阶

//7.按位置删除
void delete_pos(Node** pp, int pos) {
	//边界：
	if (pos < 1) {
		printf("位置无效\n");
		return;
	}
	//空链表：
	if (*pp == NULL) return;

	Node* cur = *pp;

	//找到位置i的结点cur
	while (pos>1&&cur->next) {
		cur = cur->next;
		pos--;
	}
	//跳出while分两种情况
	//给的pos超过表长，cur->next==NULL;
	if (pos > 1) {
		return;
	}
	//恰好到位置pos
	else {
		delete_node(pp, cur);
	}
}

//8.双向链表按位置插入
void insert_pos(Node** pp, int pos, int data)
{
	//边界：
	if (pos < 1) {
		printf("位置无效\n");
		return;
	}
	//空链表：
	if (*pp == NULL) {
		if (pos == 1) {
			*pp = create_node(data);
			//创建一个新节点，并让头指针指向它（把新节点作为链表的第一个节点）
		}
		else {
			printf("位置无效\n");
		}
		return;
	}

	Node* cur = *pp;//第一个结点处
	int position = 1;
	//找到第pos个结点
	while (cur&&position<pos) {
		cur = cur->next;
		position++;
	}//cur此时保存第pos个结点，需要插入在cur之前
	if (cur) {
		insert_before(pp, cur, data);
	}
	else if (cur==NULL&&position == pos)//新节点
	{
		//此时cur==NULL没法用。需要找到尾结点
		Node* tail = *pp;

		while (tail->next) {
			tail = tail->next;
		}

		insert_after(tail, data);
	}
	else {
		printf("位置无效\n");//pos 太大了超过表长+1
	}
}

//9.在有序链表(从小到大)中插入
// 重复值放在已有相同值之前
void insert_sorted(Node** pp, int data) {
	//空链表：
	if (*pp == NULL) {
		*pp = create_node(data);
		//创建一个新节点，并让头指针指向它（把新节点作为链表的第一个节点）
		return;
	}

	Node* cur = *pp;
	Node* p = create_node(data);

	//首元素
	if (data <= cur->data) {
		p->next = cur;
		p->prev = NULL;
		cur->prev = p;
		*pp = p;
		(*pp)->prev = NULL;//注意优先级
		
		return;
	}

	//中间元素
	while (cur->next) {
		if (data > cur->data) {
			cur = cur->next;
		}
		else {
			p->prev = cur->prev;
			cur->prev->next = p;
			cur->prev = p;
			p->next = cur;
			return;
		}
	}

	//末尾
	if (data > cur->data) {
		cur->next = p;
		p->prev = cur;
	}
	else {
		p->prev = cur->prev;
		cur->prev->next = p;
		cur->prev = p;
		p->next = cur;
	}
}

//10.删除重复值
//保留每个值第一次出现的节点，删除后续重复节点
void delete_re(Node** pp) {
	Node* cur = *pp;

	while (cur) {
		Node* temp = cur->next;
		while (temp) {
			if (cur->data == temp->data) {
				Node*dele=temp;
				temp = temp->next;
				delete_node(pp, dele);
			}
			else {
				temp = temp->next;
			}
		}
		cur = cur->next;
	}
}

//三、双向链表综合操作

//11.反转链表！！
//(1)交换数据
void reverse_list(Node**pp) {
	Node* cur = *pp;
	//判空
	if (*pp == NULL) return;
	Node* left = cur;
	Node* right = cur;
	//right移动到尾结点
	while (right->next) {
		right = right->next;
	}

	//开始交换
	while (right!=left&&left->prev!=right) {
		int temp = left->data;
		left->data = right->data;
		right->data = temp;

		left=left->next;
		right=right->prev;
	}
}
//(2)修改指针
void reverse_list2(Node**pp){
	Node* cur = *pp;
	//判空
	if (cur==NULL) {
		printf("链表为空\n");
		return;
	}
	Node* next = NULL;//保存下一结点
	Node* newHead = NULL;//保存当前节点
	while (cur != NULL) {
		newHead = cur;
		next = cur->next;
		Node* temp = cur->prev;
		cur->prev = cur->next;
		cur->next = temp;
		//交换后，原来的下一个节点会变成 cur->prev。
		//但我们提前保存了它，所以仍然可以继续遍历。
		cur = next;
	}
	*pp = newHead;
}


//12.清空链表
void clear_list(Node** pp) {
	Node* cur = *pp;
	if (cur == NULL) return;
	
	while (cur) {
		Node*temp = cur;
		cur = cur->next;
		free(temp);
	}
	*pp = NULL;
	//你释放完所有节点后，局部指针 cur 变成了 NULL，
	//但外部的头指针 *pp 仍然保存着原来第一个节点的地址。
}
//13.合并两个有序链表！！
//将两个升序双向链表合并为一个升序链表
Node* merge_list(Node*A,Node*B) {
	
	//判空
	if (A == NULL ) {
		return B;
	}
	else if (B == NULL) {
		return A;
	}

	Node* head = NULL;
	Node* tail = NULL;
	if (A->data <= B->data) {
		head=tail=A;
		A = A->next;//更新
	}
	else {
		head=tail=B;
		B = B->next;//更新
	}
	//A、B都非空
	while (A && B) {
		if (A->data <= B->data) {
			tail->next = A;
			A->prev = tail;
			tail = A;
			A = A->next;
		}
		else {
			tail->next = B;
			B->prev = tail;
			tail = B;
			B = B->next;
		}
	}

	//处理剩余节点
	//A空
	if (!A) {
		tail->next = B;
		if (B != NULL) {
			B->prev = tail;
		}
	}
	//B空
	else {
		tail->next = A;
		A->prev = tail;
	}
	head->prev = NULL;
	return head;
}

//14. 判断是否有序
int is_sorted(Node* head) {
	Node* cur = head;
	
	if (cur == NULL) return 1;
	else if (cur->next == NULL) {
		return 1;
	}
	while (cur->next) {
		if (cur->data <= cur->next->data) {
			cur = cur->next;
		}
		else {
			return 0;
		}
	}
	return 1;
}
//15. 查找倒数第 k 个节点
Node* find_kth_from_end(Node* head, int k) {
	//可以直接使用head
	Node* cur = head;
	//判空
	if (cur == NULL)return NULL;

	//k
	if (k <= 0) return NULL;

	//寻找尾结点
	Node* tail = cur;
	while (tail->next) {
		tail=tail->next;
	}

	//倒遍历
	//k大于链表长度
	while (k>1&&tail!=NULL) {
		tail = tail->prev;
		k--;
	}
	if (tail) {
		return tail;
	}//如果有效
	//如果无效（即tail->prev到了NULL）
	/*
	else {
		return NULL;
	}*/
}


//第二部分：循环链表
/*16. 建立并遍历循环单链表
- 创建节点并连接成环。
- 正确遍历一圈后停止。
- 分别测试空链表、一个节点和多个节点。*/

//遍历函数
void print_list(Node* head) {
	if (head == NULL)return;

	Node* cur = head;
	do {
		printf("%d", cur->data);
		cur = cur->next;
	} while (cur != head);

	printf("\n");
}
//创建包含 n 个节点的循环单链表
Node* create_circle_list(int n) {
	if (n <= 0)return NULL;
	int i = 1;
	Node* head = create_node(i);
	head->next = head;
	Node* cur = head;

	while (n > 1) {
		Node* newNode = create_node(++i);

		if (newNode == NULL) {
			printf("创建失败：内存不足！\n");

			// 释放已经创建的节点
			Node* p = head->next;
			while (p != head) {
				Node* temp = p;
				p = p->next;
				free(temp);
			}
			free(head);

			return NULL;
		}

		cur->next = newNode;
		newNode->next = head;
		cur = newNode;
		n--;
	}

	printf("循环链表创建成功，共 %d 个节点！\n", i);
	return head;
}





/*17. 在循环单链表中插入与删除
- 在头部插入。
- 在尾部插入。
- 删除头节点、尾节点和指定值节点。
- 特别处理只有一个节点的情况。*/

//插入
Node* insert_circle_list(Node* head, int pos, int data) {
	if (pos < 1)return head;
	
	Node* cur = head;
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;

	//判空
	if (head == NULL) {
		if (pos != 1) {
			free(newNode);
			return head;
		}
		newNode->next = newNode;
		return newNode;
	}
	//找尾结点(没有NULL)
	Node* tail = cur;
	while (tail->next!=head) {//!!!
		tail = tail->next;
	}
	//首插
	if (pos == 1) {
		newNode->next = cur;
	    tail->next = newNode;
		return newNode;
	}
	//插入中间(找前驱)
	cur = head;
	int index = 1;//正着找

	while (index < pos - 1 && cur->next != head) {// 找到第 pos-1 个结点
		cur = cur->next;
		index++;
	}//pos=2,1<1;不执行，cur依旧指向第一个结点

	if (index != pos - 1) {// 1.位置超出范围
		free(newNode);
		printf("插入失败：位置 %d 超出范围！\n", pos);
		return head;
	}
	//2.遇到尾结点
	// 插入结点
	newNode->next = cur->next;
	cur->next = newNode;

	return head;
}



//删除指定位置的结点
Node* delete_circle_list(Node* head, int pos) {
	Node* cur = head;

	//检查位置是否合法
	if (pos < 1) {
		printf("删除失败，所给位置不合法\n");
		return head;
	}

	//判空
	if (cur == NULL) {
		printf("删除失败，链表为空\n");
		return head;
	}

	//寻找尾节点
	Node* tail = cur;
	while (tail->next != head) {
		tail=tail->next;
	}
	//删除头结点
	if (pos == 1) {
		if (cur->next == cur) {//注意：循环链表判断条件不是指向NULL
			free(cur);
			head = NULL;
			return head;
		}
		else {
			head = cur->next;
			tail->next = head;//更新尾节点
			free(cur);
			return head;
		}
	}

	//删除其他节点(包括尾结点)
	cur = head;
	int index = 1;
	while (index < pos - 1 && cur->next != head) {
		cur = cur->next;
		index++;
	}
	//跳出while：index=pos-1;cur遍历到尾结点了
	if (index!=pos-1) {//说明是遍历结束但index还未达到所要求的pos-1
		printf("删除失败，位置超出表长\n");
		return head;
	}
	//没有NULL,故删除操作一致
	Node* temp = cur->next;
	cur->next = temp->next;
	free(temp);

	printf("删除成功：已删除第 %d 个结点。\n", pos);
	return head;

}





/*18. 约瑟夫环问题
- 有 n 个人围成一圈，从指定位置开始报数。
- 每数到 m 就删除该节点。
- 输出删除顺序和最后剩下的人。*/

//循环链表：数到第m个结点(每次循环删除一个人，直到人数=1)
void Josephus(Node* head, int n, int start, int m) {
	Node* cur = head;

	//边界
	if (m<1||n<=0||start<1 || start>n) {
		printf("m不合适\n");
		return;
	}
	//空表
	if (!cur) {
		printf("没有空间\n");
		return;
	}

	//找到开始位置的前驱
	int i = 1;
	if (start == 1) {
		while (cur->next != head) {
			cur = cur->next;
		}
	}
	else {
		while (i < start-1) {
			cur = cur->next;
			i++;
		}
	}

	//开始
	while (n > 1) {//人数>m
		int k = 1;
		while (k < m) {//找待删结点的前驱
			cur = cur->next;
			k++;
		}
		//此时k=m
		Node* temp = cur->next;
		cur->next = temp->next;
		printf("淘汰编号：%d\n", temp->data);
		free(temp);
		n--;
	}

	printf("最后幸存者：%d\n", cur->data);
	free(cur);

}



int main() {
	int n= 5;
	Node*head=create_circle_list(n);
	print_circle_list(head);
	int start = 2;
	int m = 4;
	Josephus(head, n, start,m)；
    return 0;
}