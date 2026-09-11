#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//结构体写在函数外
struct Student {
	char name[20];
	int age;
	double score;
};
void create_st() {
	struct Student s;
	strcpy(s.name, "Tom");
	s.age = 20;
	s.score = 90.5;
	printf("姓名：%s;年龄：%d;分数：%.1f\n", s.name, s.age, s.score);//输出double对应%f

	struct Student* p = &s;
	p->age = 21;
	p->score = 92;
	printf("姓名：%s;年龄：%d;分数：%.1f\n", p->name, p->age,p->score);
	printf("\n");
}

void init_st() {
	struct Student s2 = { "Tom",20,90.5 };
	printf("姓名：%s;年龄：%d;分数：%.1f\n", s2.name, s2.age, s2.score);
	printf("\n");
}

void st_array() {
	//直接初始化
	struct Student students[3] =
	{
		{"Tom",20,90.5},
		{"Jack",21,85.0},
		{"Lucy",19,95.5}
	};
	for (int i = 0; i < 3; i++) {
		printf("姓名：%s;年龄：%d;分数：%f\n", 
			students[i].name, 
			students[i].age, 
			students[i].score);
	}
	printf("\n");
}

void user_scanf() {
	struct Student students[3];
	for (int i = 0; i < 3; i++) {
		printf("请输入第%d个学生的姓名，年龄，分数：", i+1);
		scanf("%s %d %lf", 
			students[i].name, &students[i].age, &students[i].score);
	}

	for (int i = 0; i < 3; i++) {
		printf("姓名：%s;年龄：%d;分数：%.1f\n",
			students[i].name,
			students[i].age,
			students[i].score);
	}
	printf("\n");
}

//法一
void user_scanf_max() {
	struct Student students[3];
	for (int i = 0; i < 3; i++) {
		printf("请输入第%d个学生的姓名，年龄，分数：", i + 1);
		scanf("%s %d %lf",
			students[i].name, &students[i].age, &students[i].score);
	}

	double max = students[0].score;
	for (int i = 0; i < 3; i++) {
		if (students[i].score > max) {
			max = students[i].score;
		}
	}

	for (int i = 0; i < 3; i++) {
		if (students[i].score == max) {
			printf("%s是最高分", students[i].name);
		}
	}
}
//法二：保存最高分的下标
void user_scanf_max2() {
	struct Student students[3];
	for (int i = 0; i < 3; i++) {
		printf("请输入第%d个学生的姓名，年龄，分数：", i + 1);
		scanf("%s %d %lf",
			students[i].name, &students[i].age, &students[i].score);
	}

	int max_index = 0;
	for (int i = 1; i < 3; i++) {
		if (students[i].score > students[max_index].score) {
			max_index = i + 1;
		}
	}
	printf("%s是最高分", students[max_index].name);
	printf("\n");
}

//用结构体指针 + 函数，同时修改学生的姓名、年龄和分数
void change_student(struct Student* p) {
	strcpy(p->name, "Tom");
	p->age = 21;
	p->score = 99;
}
void result() {
	struct Student s = { "Jack",20,90.0 };
	change_student(&s);
	printf("\n修改后：\n");
	printf("姓名：%s\n", s.name);
	printf("年龄：%d\n", s.age);
	printf("分数：%.1f\n", s.score);
}

//结构体数组 + 结构体指针 + 函数
//① 输入函数
void input_students(struct Student* p, int size)
{
	
	for (int i = 0; i < size; i++) {
		printf("请输入学生信息：");
		scanf("%s %d %lf", 
			(p + i)->name, 
			&(p + i)->age, 
			&(p + i)->score);
	}
}

//② 输出函数
void print_students(struct Student* p, int size)
{
	for (int i = 0; i < size; i++) {
		printf("姓名：%s; 年龄：%d; 分数：%.1f",
			(p + i)->name,
			(p + i)->age,
			(p + i)->score);
	}
}
void result2() {
	int size = 3;
	struct Student s[3];//是结构体数组；
	input_students(s, size);
	print_students(s, size);
}

//6.
int find_max_student(struct Student* p, int size)
{
	int max_index=0;
	for (int i = 1; i < size; i++) {
		if ((p + i )->score > (p + max_index)->score) {//逻辑梳理
			max_index = i+1;
		}
	}
	return max_index;
}
void result3() {
	int size=3;
	struct Student s[3];
	input_students(s, size);
	int result = find_max_student(s,size);
	//result3里面没有p,不能写(p + result)->name
	printf("分数最高的学生是：%s",s[result].name );
}

//7.批量修改信息：每个学生加5分
void change_students(struct Student*p,int size)
{
	for (int i = 0; i < size; i++) {
		(p + i)->score += 5;
	}
}
void result4() {
	int size = 3;
	struct Student s[3];
	input_students(s, size);
	change_students(s, size);
	print_students(s,size);
}

//8.修改指定学生的分数(加5分)
void change_astudent(struct Student* p,int index) 
{
	(p+index)->score += 5;
}
void result5() {
	int size = 3;
	int index = 1;
	struct Student s[3];
	input_students(s, size);
	change_astudent(s,index);
	print_students(s, size);
}

//9.查找指定学生的信息,根据姓名查找学生
int find_student(struct Student* p, int size,const char* name) {
	for (int i = 0; i < size; i++) {
		if (strcmp((p + i)->name, name) == 0)
			return i;
	}
	return -1;
}
void result6() {
	int size = 3;
	int index = 1;
	const char* name= "Tom";
	struct Student s[3];
	input_students(s, size);
	int result=find_student(s, size,name);
	if (result == -1) {
		printf("Not found");
	}
	else {
		printf("%s找到了", s[result].name);
	}
}

//10.查找分数最高的学生并修改他的分数
void change_student_score(struct Student* p, int index,double new_score) {
	
	(p+index)->score = new_score;
}
void result7() {
	int size = 3;
	struct Student s[3];
	input_students(s, size);
	int index = find_max_student(s, size);
	printf("最高分的学生是：%s", s[index].name);
	printf("原来的分数：%.1f\n", s[index].score);

	double new_score;
	printf("请输入修改后的分数：");
	scanf("%lf", &new_score);

	change_student_score(s,index,new_score);
	printf("\n修改后的学生信息：\n");
	print_students(s, size);
}

//01.按分数从高到低排序
void sort_student_score(struct Student*p,int size) {
	//冒泡
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size - i - 1; j++) {
			struct Student temp;//交换的是学生
			if ((p + j + 1)->score > (p + j)->score) {
				temp = *(p + j + 1);
				*(p + j + 1) = *(p + j);
				*(p + j) = temp;
			}
		}
	}
}
void result8() {
	int size = 3;
	struct Student s[3];
	input_students(s, size);
	sort_student_score(s, size);
	print_students(s, size);
}

int main() {
	result8();
	return 0;
}