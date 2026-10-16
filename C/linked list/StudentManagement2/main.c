#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>

//定义学生
typedef struct Student{
	int id;//学号
	char name[20];
	int age;
	double score;
}Student;

//定义结点
typedef struct Node {
	Student data;//节点里存储的是学生
	struct Node* next;//Node未定义完成，仍需struct
}Node;

//1.创建结点(我已经有一个 Student 了，你帮我把它包装成一个 Node。)
Node* create_node(Student s) {
	Node* newNode = malloc(sizeof(Node));//申请Node空间

	newNode->data = s;
	newNode->next = NULL;

	return newNode;
}

//2.添加学生
void add_student(Node**pp) {
	Node* cur = *pp;//头结点

	Student s;
	printf("请输入添加学生的学号、姓名、年龄、分数：");
	scanf("%d %s %d %lf", &s.id, s.name, &s.age, &s.score);

	Node*newNode=create_node(s);

	if (cur == NULL) {
		*pp = newNode;
		return;
	}
	
	while (cur->next != NULL) {
		cur = cur->next;
	}
	cur->next = newNode;
}

//3.显示所有链表
void show_studens(Node*p) {
	Node* cur = p;

	while (cur != NULL) {
		Student s = cur->data;
	    printf("%d %s %d %.1f\n",s.id, s.name, s.age, s.score);

		cur = cur->next;
	}
}

//4.查找学生（根据学号查找学生，返回对应节点）
Node* search_student(Node* p, int id) {
	Node* cur = p;
	while (cur != NULL) {
		if (cur->data.id == id) {
			return cur;
		}
		cur = cur->next;
	}

	return NULL;
}

//5.修改学生信息（根据学号找到学生，然后修改他的姓名、年龄、成绩）
void change_student(Node* p, int id) {
	//Node* cur = p;没有使用cur

	Node* result = search_student(p, id);
	if (result == NULL) {
		printf("查找失败\n");
		return;
	}
	printf("修改学生%s的信息：姓名、年龄、分数\n", result->data.name);
	scanf("%s %d %lf",result->data.name, &result->data.age, &result->data.score);

}

//6.删除学生(根据学号)
void delete_student(Node**pp,int id) {
	Node* cur = *pp;
	Node* temp = NULL;

	//空链表会出错
	if (cur == NULL)
	{
		printf("链表为空\n");
		return;
	}

	//第一个
	if (cur->data.id == id) {
		temp = cur;
		*pp= cur->next;//直接修改头指针
		free(temp);
		return;
	}
	cur = cur->next;

	//找到待删除结点的前一个
	while (cur->next!=NULL) {
		if (cur->next->data.id == id) {
			temp = cur->next;
			cur->next = cur->next->next;
			free(temp);
			return;
		}
		cur = cur->next;
	}

	//边界：不存在
	printf("没有找到该学生\n");

}

//7.统计学生数量
int get_student_count(Node* p) {
	Node* cur = p;
	int count = 0;

	while (cur) {
		count++;
		cur = cur->next;
	}

	return count;
}

//8.释放整个链表
void free_list(Node** pp) {

	Node* temp = NULL;

	while (*pp) {
		temp = *pp;
		*pp = temp->next;
		free(temp);
	}
}


//组装菜单程序
void menu(Node**pp) {
	int open = 1;
	while (open) {
		printf("========== 学生管理系统 ==========\n"
			"1. 添加学生\n"
			"2. 显示所有学生\n"
			"3. 查找学生\n"
			"4. 修改学生\n"
			"5. 删除学生\n"
			"6. 统计学生数量\n"
			"0. 退出\n"
			"==================================\n");
		printf("请选择：\n");

		int choice;
		scanf("%d", &choice);

		switch (choice)
		{
		case 1:
			add_student(pp);
			break;
			
		case 2:
			show_studens(*pp);
			break;

		case 3: {
			int id;
			printf("请输入要查找学生的学号：\n");
			scanf("%d", &id);
			Node* result = search_student(*pp, id);
			if (result == NULL)
			{
				printf("查找失败\n");
			}
			else
			{
				printf("%d %s %d %.1f\n", result->data.id, result->data.name, result->data.age, result->data.score);
			}
			break;
		}

		case 4: {
			int id;
			printf("请输入要修改学生的学号：\n");
			scanf("%d", &id);
			change_student(*pp, id);
			break;
		}

		case 5: {
			int id;
			printf("请输入要删除学生的学号：\n");
			scanf("%d", &id);
			delete_student(pp, id);
			break;
		}

		case 6: {
			int result = get_student_count(*pp);
			printf("当前学生数量：%d\n", result);
			break;
		}

		case 0: {
			free_list(pp);
			open = 0;
			break;
		}

		default:
			printf("输入无效\n");
			break;

		}
	}

}

//1.删除链表中所有分数低于 60 的学生。
void delete_failed_students(Node** pp) {
	Node* cur = *pp;
	Node* temp = NULL;

	while (cur && cur->data.score < 60) {
		temp = *pp;
		*pp = cur->next;
		cur = *pp;
		free(temp);
	}
	//cur = cur->next; 多余，此时cur已经移到新的头结点了

	//找前一个结点,遍历时需要判断next而不是cur本身
	while (cur->next!=NULL) {
		if (cur->next->data.score < 60) {
			temp = cur->next;
			cur->next = cur->next->next;
			free(temp);
			//删除成功，cur不动
		}
		else {
			cur = cur->next;//没删除 → cur 往后走
		}
	}

}

//2.插入一个学生，位置按照分数高低(默认原链表按照分数从低到高排序)
void insert_sorted(Node** pp, Student s) {
	Node* cur = *pp;
	Node* newNode = create_node(s);

	//空链表
	if (cur == NULL)
	{
		*pp = newNode;
		return;
	}

	//第一个
	if (cur->data.score > newNode->data.score) {
		*pp = newNode;
		newNode->next = cur;
		return;
	}
	
	//cur = cur->next;不需要，因为while（）判断条件是next；加上会跳过头结点
	while (cur->next!=NULL) {
		//考虑分数相同（相同分数时，新学生放在原来相同分数的前面）
		if (cur->data.score<=newNode->data.score && cur->next->data.score>=newNode->data.score) {
			newNode->next = cur->next;
			cur->next = newNode;
			return;
		}
		cur = cur->next;
	}

	//cur是最后一个元素
	if (cur->data.score < newNode->data.score) {
		cur->next = newNode;
	}
}

//3.查找分数最高的学生
//如果有多个学生分数相同，返回第一个出现的学生
Node* find_top_student(Node* p) {
	Node* cur = p;

	//链表为空
	if (cur == NULL) {
		printf("链表为空\n");
		return NULL;
	}

	//遍历
	Node* max = cur;
	while (cur != NULL) {
		//cur->next可能是NULL
		if (cur->data.score > max->data.score) {
			max = cur;
		}
		cur = cur->next;
	}
	return max;
}

//4.计算平均分
double get_average(Node*p) {
	Node* cur = p;
	double sum = 0.0;
	int count = 0;

	//链表为空，count作为分母不能等于0，需要单独判断
	if (p == NULL) {
		return 0;
	}


	while (cur) {
		sum += cur->data.score;
		count++;
		cur = cur->next;
	}

	double result = sum / count;
	return result;

}

int main() {
	Node* p = NULL;//初始化链表


	menu(&p);

	return 0;
}