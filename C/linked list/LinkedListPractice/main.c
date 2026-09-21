#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>//malloc

typedef struct Node {
	int data;
	struct Node* next;
}Node;

//1.创建结点
void create_list(Node**pp){//希望在函数内部修改 main 里的那个指针 p，所以要把 p 的地址传进去。
	Node* p = malloc(sizeof(Node));//和main里的p不一样
	//初始化
	p->data = 10;
	p->next = NULL;
	
	//创建第二个结点
	Node* p2 = malloc(sizeof(Node));
	p2->data = 20;
	p2->next = NULL;
	p->next = p2;

	//将扩容后的p赋给main中的p，即*pp
	*pp = p;//pp=&p;
}

//2.遍历结点
void transverse_list(Node*p) {
	Node* cur = p;
	while (cur!=NULL) {
		printf("%d", cur->data);
		cur = cur->next;//更新
	}
}

//3.插入结点 :
// 10\20\30\40\50:在 10 和 20 中间插入一个 15
void insert_node(Node*p) {
	//已知：p->data = 10;

	Node* newNode = malloc(sizeof(Node));
	newNode->data = 15;

	newNode->next = p->next;//先连后面
	p ->next = newNode;//再连前面
}

//3.2 在指定位置 pos（下标） 插入一个节点
//头插：新节点先指向旧头，再让头指针指向新节点。
void insert_node2(Node**pp,int pos,int value) {
	
	Node* newNode = malloc(sizeof(Node));
	if (newNode == NULL) {
		printf("内存申请失败\n");
		return;
	}
	newNode->data = value;//newNode里面现在有一个结点存放value

	//插入头结点
	if (pos == 0) {
		newNode->next=*pp;//*pp是p指向的首元素地址,即newNode指向旧的头结点
		//此时p还是指向 10
		*pp = newNode;   //把newNode里面保存的地址，复制给 p，即让头指针指向新节点
		return;
	}

	// 找到插入位置的前一个节点pos-1
	Node* cur = *pp; //cur指向p的头结点
	//遍历pos-1次cur，判断是否有位置
	for (int i = 0; i < pos - 1; i++) {
		if (cur == NULL) {
			printf("位置无效\n");
			return;
		}
		cur = cur->next;
	}

	//pos-1处单独进行判断
	if (cur == NULL) {
		printf("位置无效\n");
		free(newNode);
		return;
	}

	//插入
	newNode->next = cur->next;
	cur->next = newNode;
}

//4.删除指定位置的结点
void delete_node(Node**pp,int pos) {
	Node* cur = *pp;

	//删除头结点，pos=0
	if (pos == 0) {
		Node* temp = *pp;//保存要删除的节点
		*pp = (*pp)->next;
		free(temp);//释放结点
		return;
	}
	//停留在pos-1处
	for (int i = 0; i < pos - 1; i++) {
		if (cur == NULL) {
			printf("位置无效\n");
			return;
		}
		cur = cur->next;//最后一次循环，cur在pos-1处
	}

	//检查位置是否有效
	if (cur == NULL || cur->next == NULL) {
		printf("位置无效\n");
		return;
	}


	Node* temp2 = cur->next;
	//删除操作
	cur->next = cur->next->next;
	free(temp2);
	temp2 = NULL;
}

//5.查找结点(根据值找下标)
Node* search_node_by_value(Node* p,int target){
	Node* cur = p;
	
	while (cur != NULL) {
		if (cur->data == target) {
			return cur;
		}
		cur = cur->next;
	}
	return NULL;
}

//6.修改结点
void change_node(Node* p) {
	Node* result = search_node_by_value(p,20);
	if (result != NULL) {
		result->data = 30;
	}
}

//7.链表长度
int get_length(Node*p) {
	int count = 0;
	Node* cur = p;
	while (cur != NULL) {
		count++;
		cur = cur->next;
	}
	return count;
}

//8.链表逆序！！！
void reverse_list(Node**pp) {
	Node* cur = *pp;
	Node* prev = NULL;
	Node* next;

	while (cur != NULL) {
		next = cur->next;
		cur->next = prev;

		prev = cur;
		cur = next;
	}
	*pp = prev;

}

//综合练习1
//1.在链表中找到 target，把它修改成 newValue。
void change_node(Node* p, int target, int newValue) {
	Node* cur = p;
	while (cur != NULL) {
		if (cur->data == target) {
			cur->data = newValue;
			return;
		}
		cur = cur->next;
	}
	printf("查找失败\n");
}

//2.统计链表中 target 出现了多少次
int count_value(Node* p, int target) {
	Node* cur = p;
	int count = 0;
	while (cur != NULL) {
		if (cur->data == target) {
			count++;
		}
		cur = cur->next;
	}

	return count;
}

//3.返回链表中最大值所在节点的地址
Node* find_max(Node*p) {
	//边界判断：空链表
	if (p == NULL)
	{
		return NULL;
	}

	Node* cur = p;
	Node* max = cur;
	cur = cur->next;

	while (cur != NULL) {
		if (max->data < cur->data) {
			max = cur;
		}
		cur = cur->next;
	}
	return max;
}

//4.删除链表中第一个值等于 target 的节点
void delete_first(Node** pp, int target) {
	Node* cur = *pp;
	Node* temp = NULL;

	//判空
	if (*pp == NULL)
	{
		printf("链表为空\n");
		return;
	}
	//头结点判断
	if (cur->data == target) {
		temp = *pp;
		*pp = cur->next;
		free(temp);
		return;
	}
	
	while (cur->next != NULL) {//寻找：“目标节点的前一个节点”
		if ((cur->next)->data == target) {
			temp = cur->next;
			cur->next = cur->next->next;
			free(temp);

			return;
		}
		cur = cur->next;
	}

	printf("删除失败\n");
}


//5.找到第一个值为 target 的节点，在它后面插入一个新节点。
void insert_after_value(Node*p,int target,int value) {
	Node* cur =p;
	Node* newNode = malloc(sizeof(Node));
	newNode->data = value;

	while (cur != NULL) {
		if (cur->data == target) {
			newNode->next = cur->next;
			cur->next = newNode;
			return;
		}
		cur = cur->next;
	}

	//如若跳出while，说明没查找到，需要释放newNode
	free(newNode);
	printf("查找失败\n");
}

//6.删除所有值为 target 的节点
void delete_all(Node** pp, int target) {
	Node* cur = *pp;
	Node* temp = NULL;
	//判空
	if (*pp == NULL)
	{
		printf("链表为空\n");
		return;
	}

	//头结点判断
	while (cur != NULL && cur->data == target){//从左到右判断
		temp = *pp;
		*pp = cur->next;
		free(temp);
		cur = *pp;//更新头结点
	}
	//其余结点
	while (cur->next != NULL) {//找target的前一个结点
		if (cur->next->data == target) {
			temp = cur->next;//暂存要删除的节点
			cur->next = cur->next->next;
			free(temp);
		}
		else {
			cur = cur->next;//没有进行删除操作，才需要更新cur
		}
	}
}

//综合练习2
//练习 1：统计偶数节点
int count_value(Node*p) {
	Node* cur = p;
	int count = 0;
	while (cur != NULL) {
		if ((cur->data) % 2 == 0) {
			count++;
		}
		cur = cur->next;
	}

	return count;
}

//练习 2：查找最小值节点。
Node* find_min(Node*p){
	Node* cur = p;
	Node* min = cur;

	//边界
	if (p == NULL)
	{
		return NULL;
	}

	cur = cur->next;
	while (cur != NULL) {
		if (min->data > cur->data) {
			min =cur;
		}
		cur = cur->next;
	}

	return min;
}

//练习 3：删除最后一个节点
void delete_last(Node**pp) {//考虑只有一个结点
	Node* cur = *pp;

	//边界
	if (cur == NULL)
	{
		return NULL;//返回类型
	}
	//只有一个结点,改变头指针，需要*pp
	if (cur->next == NULL) {
		*pp = NULL;
		return;
	}
	//遍历
	while (cur->next->next!= NULL) {
		cur = cur->next;
	}
	Node* temp = cur->next;//暂存终结点
	cur->next = NULL;//断开
	free(temp);
}


//练习 4：在链表末尾插入节点
void insert_last(Node**pp,int value) {
	Node* cur = *pp;
	Node* newNode = malloc(sizeof(Node));//确实判断：内存是否分配成功
	newNode->data = value;
	newNode->next = NULL;//初始化

	if (cur == NULL)
	{
		*pp = newNode;
		return;
	}
	//遍历
	while (cur->next != NULL) {
		cur = cur->next;
	}
	cur->next = newNode;

}

//练习 5：在指定值前插入
void insert_before(Node**pp,int target,int value) {
	Node* cur = *pp;
	Node* newNode = malloc(sizeof(Node));//确实判断：内存是否分配成功
	newNode->data = value;
	newNode->next = NULL;//初始化

	//边界
	if (cur == NULL)
	{
		printf("链表为空\n");
		return;//返回类型
	}
	//1个
	if (cur->data == target) {
		newNode->next = cur;
		*pp = newNode;
		return;
	}
	
	//遍历
	while (cur->next != NULL) {
		if (cur->next->data == target) {
			newNode->next = cur->next;
			cur->next = newNode;
			return;
		}
		cur = cur->next;
	}

	printf("没有找到\n");
}

//练习6：删除链表中所有 target（处理连续节点）
void delete_all(Node**pp,int target) {
	Node* cur = *pp;
	Node* temp = NULL;

	//边界
	if (cur == NULL)
	{
		printf("链表为空\n");
		return;//返回类型
	}

	//头结点连续删除
	while (cur != NULL && cur->data == target) {//
		temp = cur;
		*pp=cur->next;//可能为空
		cur = *pp;
		free(temp);
	}

	while (cur != NULL && cur->next != NULL) {
		if (cur->next->data==target) {
			temp = cur->next;
			cur->next = cur->next->next;
			free(temp);
		}
		else {
			cur = cur->next;
		}
	}

}





int main() {
	Node* p = NULL;
	create_list(&p);
	// 此时 p 应该指向第一个节点

	return 0;
}