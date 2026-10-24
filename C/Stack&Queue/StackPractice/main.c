#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>

#include<stdbool.h>

typedef int SElemType;//定义栈元素类型
//结构体定义
#define MAXSIZE 100
typedef struct {
	int data[MAXSIZE];
	int top;//栈顶元素的下标（不是指针）
}SqStack;

//1.初始化栈
void init_stack(SqStack *s) {
	s->top = -1;//初始化栈顶指针
	printf("初始化成功！\n");
}

//2.入栈
bool Push(SqStack*s,int data) {
	if (s->top == MAXSIZE-1) {
		printf("栈已满,入栈失败\n");
		return false;
	}
	s->top++;
	s->data[s->top] = data;

	printf("入栈成功\n");
	return true;
}

//3.出栈
bool Pop(SqStack* s,int *data) {
	if (s->top == -1) {
		printf("栈空，出栈失败\n");
		return false;
	}
	*data = s->data[s->top];
	s->top--;

	return true;
}

// 4.获取栈顶元素
bool GetTop(SqStack* s, SElemType* e)
{
	if (s->top == -1) {
		printf("栈空\n");
		return false;
	}
	*e = s->data[s->top];
	return true;
}

// 5.获取当前栈中有多少个元素
int StackLength(SqStack s) {
	return s.top + 1;
}

//6.判断栈是否为空
bool StackEmpty(SqStack s) {
	if (s.top == -1) return true;//空
	else return false;
}
/*bool StackEmpty(SqStack s) {
    return s.top == -1;
}*/

//7.清空栈
void ClearStack(SqStack* s) {
		s->top = -1;
		printf("栈已清空！\n");
}

//8.销毁栈
void DestroyStack(SqStack* s) {
	s->top = -1;
	printf("栈已销毁！\n");
}






//练习

//1.遍历
void TraverseStack(SqStack s) {
	if (s.top == -1) {
		printf("栈空\n");
		return;
	}

	int k = 0;
	while (k <= s.top) {
		printf("%d ", s.data[k]);
		k++;
	}

	printf("\n");
}

//2.查找元素
bool FindStack(SqStack s, SElemType target) {
	if (s.top == -1) {
		printf("空栈\n");
		return false;
	}
	int k = 0;
	while (k <= s.top && s.data[k] != target) {
		k++;
	}
	if (k <= s.top) {
		printf("target下标为%d\n", k);
		return true;
	}
	else {
		return false;
	}
}

//3.计算指定元素出现次数
int CountElement(SqStack s, SElemType target){
	if (s.top == -1) {
		printf("空栈\n");
		return 0;
	}

	int k = 0;
	int count = 0;
	while (k <= s.top ) {
		if ((s.data[k]) == target) {
			count++;
		}
		k++;
	}
	
	return count;
}

//4. 获取栈顶元素并出栈
void PopTop(SqStack* s) {
	if (s->top == -1) {
		printf("空栈\n");
		return ;
	}

	int e = s->data[s->top];
	s->top--;
	printf("原栈顶元素：%d", e);

}
/*
void PopTop(SqStack* s) {
	SElemType e;

	if (Pop(s, &e)) {
		printf("出栈元素：%d\n", e);
	}
}*/


//5.菜单式顺序栈
void Menu(SqStack* s) {
	int choice;
	SElemType data;
	SElemType e;
	do {
		//菜单每次都会出来
		printf("\n===== 顺序栈菜单 =====\n"
			"1. 入栈\n"
			"2. 出栈\n"
			"3. 查看栈顶\n"
			"4. 查看栈长度\n"
			"5. 判断栈是否为空\n"
			"6. 遍历栈\n"
			"7. 清空栈\n"
			"0. 退出\n"
			"请选择：");
		if (scanf("%d", &choice) != 1) {//未成功读取
			printf("输入无效！\n");
			return;
		}

		switch (choice) {
		case 1: {
			printf("请输入入栈元素：\n");
			if (scanf("%d", &data) != 1) {
				printf("输入无效！\n");
				return;
			}

			Push(s, data);
			break;
		}

		case 2: {
			if (Pop(s, &e)) {
				printf("出栈元素：%d\n", e);
			}
			break;
		}

		case 3:
			if (GetTop(s, &e)) {
				printf("栈顶元素：%d\n", e);
			}
			break;

		case 4:
			printf("栈长度：%d\n", StackLength(*s));
			break;

		case 5:
			printf("%s\n", StackEmpty(*s) ? "栈为空" : "栈不为空");
			break;

		case 6:
			TraverseStack(*s);
			break;

		case 7:
			ClearStack(s);
			break;

		case 0:
			printf("退出菜单！\n");
			break;

		default:
			printf("无效选项，请重新输入！\n");
		}
	}while (choice != 0);

}

//6. 利用栈实现字符串反转
bool ReverseString(char str[]) {
	SqStack s;
	init_stack(&s);

	int i = 0;
	while (str[i]) {
		if (!Push(&s, str[i])) {
			printf("字符串太长，反转失败！\n");
			return false;
		}
		else {
			i++;
		}
	}

	SElemType e;
	int k = 0;
	while (k<i) {
		if (!Pop(&s, &e)) {
			printf("出栈失败，反转失败\n");
			return false;
		}
		str[k] = e;
		k++;
	}

	printf("字符串反转成功！\n");
	return true;
}


//7. 括号（）匹配检查
bool BracketMatch(char str[])
{
	SqStack s;
	init_stack(&s);

	//遍历，遇到左括号（，入栈；
	// 遇到）且栈不为空，（出栈
	int i = 0;
	SElemType e;

	while (str[i]) {
		if (str[i] == '(') {
			if (!Push(&s, str[i])) {
				printf("入栈失败！\n");
				return false;
			}
		}
		else if (str[i] == ')') {
			if (StackEmpty(s)) {
				printf("右括号多了\n");
				return false;
			}
			Pop(&s, &e);
		}
		i++;
	}
	if (StackEmpty(s)){
		return true;
	}
	else {
		printf("有剩余左括号\n");
		return false;
	}
}

bool BracketCheck(char str[], int length) {
	SqStack s;
	init_stack(&s);

	for (int i = 0; i < length; i++) {
		//遇到左括号，入栈
		if (str[i] == '(' || str[i] == '[' || str[i] == '{') {
			if (!Push(&s, str[i])) {
				return false;
			}
		}
		else if (str[i] == ')' || str[i] == ']' || str[i] == '}') {//遇到右括号
			//如果栈空，说明右括号多了
			if (StackEmpty(s)) {
				return false;
			}
			//如果栈非空，弹出左括号(栈顶元素)
			char topElem;
			if (!Pop(&s, &topElem)) {
				return false;
			}

			//判断左右括号是否一致
			if (str[i] == ')' && topElem != '(') {
				return false;
			}
			if (str[i] == ']' && topElem != '[') {
				return false;
			}
			if (str[i] == '}' && topElem != '{') {
				return false;
			}
		}
	}

	//检查完全部括号后，看栈中还有没有元素
	// 如果有，说明左括号多了
	return StackEmpty(s);
}




//8. 用栈实现十进制转二进制
//余数入栈
void binary(int data) {
	SqStack s;
	init_stack(&s);

	//除法取余
	if (data == 0) {
		printf("0\n");
		return;
	}
	int i = 1;
	int count = 0;
	while (data != 0) {
		i = data % 2;
		data/=2;
		Push(&s, i);
		count++;
	}

	while (count > 0) {
		Pop(&s, &data);
		printf("%d", data);
		count--;
	}
	printf("\n");
}



int main() {
	SqStack s;
	init_stack(&s);

	//菜单
	Menu(&s);

	//反转
	char str[MAXSIZE + 1];
	printf("请输入一个字符串（最多 %d 个字符）：", MAXSIZE);
	if (scanf("%100s", str) != 1) {
		printf("输入失败！\n");
		return 1;
	}
	/*
	printf("反转前：%s\n", str);
	if (ReverseString(str)) {
		printf("反转后：%s\n", str);
	}
	*/

	//括号
	if (BracketMatch(str)) {
		printf("括号匹配成功！\n");
	}
	else {
		printf("括号匹配失败！\n");
	}
	printf("\n");

	//进制转换
	int data = 6;
	printf("输入要转换的十进制\n");
	scanf("%d", &data);
	binary(data);

	return 0;
}