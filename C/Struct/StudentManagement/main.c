#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
	char name[20];
	int age;
	double score;
}Student;


//二级指针
//0.malloc
int create_student(Student** pp,int size) {
	*pp = malloc(sizeof(Student)*size);
	if (*pp == NULL) {
		printf("申请失败");
		return 0;
	}
	return 1;
}
//realloc练习：把数组容量调整到指定大小
void revise(Student** pp,int new_size) {
	Student* temp = realloc(*pp, sizeof(Student)*new_size);
	if (temp != NULL) {
		*pp = temp;
	}
	else
	{
		printf("扩容失败\n");
	}
}

//1.添加学生,每次加1人
void add_student(Student** pp,int* size) {
	int new_size = *size + 1;
	Student* temp = realloc(*pp, sizeof(Student) * new_size);
	if (temp != NULL) {
		*pp = temp;
		*size = new_size;
	}
	else
	{
		printf("扩容失败\n");
		return;
	}
	printf("请继续输入第%d个学生的信息：", *size);
	scanf("%s %d %lf", (*pp + *size - 1)->name, &(*pp + *size - 1)->age, &(*pp + *size - 1)->score);
}

void add_students2(Student** pp, int* size,int* capacity){
	if (*size < *capacity) {//该第*size+1个了
		printf("请继续输入第%d个学生的信息：", *size);//下标减1
		scanf("%s %d %lf", (*pp + *size )->name, &(*pp + *size)->age, &(*pp + *size )->score);
		(*size)++;//数量加1
	}
	else {
		int new_size = *size + 1;
			Student * temp = realloc(*pp, sizeof(Student) * new_size);
			if (temp != NULL) {
				printf("内存申请成功\n");
				*pp = temp;
			}
			else {
				printf("内存申请失败\n");
				return;
			}
			printf("请继续输入第%d个学生的信息：", *size);//下标减1
			scanf("%s %d %lf", (*pp + *size)->name, &(*pp + *size )->age, &(*pp + *size )->score);
			(*size)++;//数量加1
			(*capacity)++;
	}
}


//2.删除学生
void delete_student(Student* p,int* size,int index){
	if (index<0 || index>=*size) {
		printf("下标错误\n");
		return;
	}
	for (int i = index; i < *size-1; i++) {
		p[i] = p[i + 1];
	}
	(*size)--;//注意优先级，加括号
}

//4.根据姓名寻找学生下标
int find_student(Student*p,int size,const char* name) {
	for (int i = 0; i < size; i++) {
		if (strcmp((p + i)->name, name)==0) {
			return i;
		}
	}
	return -1;
}

//查找并显示学生
void find_and_print_student(Student* p, int size, char* name) {
	int index = find_student(p, size, name);
	if (index == -1) {
		printf("没有找到该学生\n");
		return;
	}
	else {
		printf("%s %d %.1f", (p + index)->name, (p + index)->age, (p + index)->score);
	}
}

//3.修改学生
//根据姓名删除学生
void delete_student_by_name(Student* p, int* size, const char* name) {
	int index = -1;
	for (int i = 0; i < *size; i++) {
		if (strcmp((p + i)->name, name) == 0) {
			index = i;
			break;//找到后跳出循环
		}
	}
	if (index == -1) {
		printf("没有找到该学生\n");
		return;
	}

	delete_student(p, size, index);
}

//根据姓名修改学生信息
void change_student_by_name(Student* p, int size, const char* name)
{
	
	int index = find_student(p, size, name);
	if (index == -1) {
		printf("没有找到该学生\n");
		return;
	}
	else {
		printf("修改%s的年龄和分数\n",(p+index)->name);
		scanf("%d %lf", &(p+index)->age, &(p + index)->score);
	}
}

//打印学生信息
void print_students(Student* p, int size) {
	if (size==0) {
		printf("当前没有学生\n");
		return;
	}
	for (int i = 0; i < size; i++) {
		printf("第%d个学生的信息：%s %d %.1f\n", i + 1, (p + i)->name, (p + i)->age, (p + i)->score);
	}
}

//按成绩从高到低排序，然后显示排序后的学生
void sort_by_score(Student* p, int size) {
	for (int i = 0; i < size-1; i++) {
		for (int j = 0; j < size - i - 1; j++) {
			if (p[j].score < p[j+1].score) {
				Student temp = p[j];
				p[j] = p[j + 1];
				p[j + 1] = temp;
			}
		}
	}
	printf("排序后\n");
	print_students(p, size);
}


//菜单
void menu() {
	printf("学生管理系统\n");
	printf("1. 添加学生\n 2. 删除学生\n 3. 修改学生\n 4. 查找学生\n 5. 显示全部学生\n 6. 按成绩排序\n 7.保存文件\n 8.读取\n 0. 退出\n");
	printf("请选择：\n");
}



//1.文件输入并保存
void save_students(Student* p, int size)
{
	// 1. 打开 students.txt
	FILE* fp = fopen("students.txt", "w");
	// 2. 判断是否打开成功
	if (fp == NULL) {
		printf("打开文件失败\n");
		return;
	}
	// 3. 循环，把所有学生写进去
	for (int i = 0; i < size; i++) {
		fprintf(fp, "%s %d %.1f\n", (p + i)->name, (p + i)->age, (p + i)->score);
	}
	// 4. 关闭文件
	fclose(fp);
}

//2.从文件读取学生，把文件中的所有学生追加到当前数组。
//先申请再读取，即使读取失败，也有一个新增的空间。最终会多出一个size
void load_students(Student**pp,int* size) {
	// 1. 打开 students.txt
	FILE* fp = fopen("students.txt", "r");
	// 2. 判断是否打开成功
	if (fp == NULL) {
		printf("打开文件失败\n");
		return;
	}
	else {
		printf("成功打开\n");
	}

	 //3.申请内存
	while (1) {
		int new_size = *size + 1;
		Student* temp = realloc(*pp, sizeof(Student) * new_size);
		if (temp != NULL) {
			*pp = temp;
		}
		else {
			printf("内存申请失败\n");
			return;
		}
		//此时还不能size++


		//4.读取新学生
		int result = fscanf(fp, "%s %d %lf", (*pp + *size)->name, &(*pp + *size)->age, &(*pp + *size)->score);
		if (result == 3)//数据项
		{
			(*size)++;
		}
		else
		{
			printf("读取完毕\n");
			break;//没有完整的数据项
		}
	}

	//5.关闭文件
	fclose(fp);

}

//2.先读取，再 realloc
void load_students2(Student**pp,int*size) {
	FILE* fp = fopen("students.txt", "r");//读取
	if (fp == NULL) {
		printf("打开失败\n");
		return;
	}
	else {
		printf("文件打开成功\n");
	}

	Student stu;  // 临时保存从文件读取的一名学生

	while (1) {
		
		// 1. 先把一名学生读取到临时变量 stu 中
		int result = fscanf(fp, "%19s %d %lf",
			stu.name,
			&stu.age,
			&stu.score);
		// 2. 当没有完整读取到一名学生，就结束
		if (result != 3) {
			printf("读取结束\n");
			break;
		}
		// 3. 读取成功，才给动态数组扩容
		int new_size = *size + 1;

		Student* temp = realloc(*pp, sizeof(Student) * new_size);
	
		if (temp != NULL) {
			printf("内存申请成功\n");
			*pp = temp;
		}
		else {
			printf("内存申请失败\n");
			fclose(fp);//关闭文件
			return;
		}

		// 4. 把临时学生复制到动态数组最后一个位置
		(*pp)[*size] = stu;

		// 5. 有效学生数量 +1
		(*size)++;
	}

	fclose(fp);
}








int main() {

	//核心
	int size = 0;
	int capacity = 0;
	Student* p = NULL;


	/*
	//malloc程序启动时先申请固定数量学生
	int result=create_student(&p,size);
	if (result == 0) {
		return 1;//内存申请失败，结束main函数
	}

	for (int i = 0; i < size; i++) {
		printf("请输入第%d个学生的信息：",i+1);
		scanf("%s %d %lf", (p + i)->name, &(p + i)->age, &(p + i)->score);

		printf("\n");
	}
	*/
	 
	while (1) {
		menu();

		int choice;
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			add_student(&p, &size);
			break;

		case 2:
			if (size == 0) {
				printf("当前没有学生，无法删除\n");
				break;
			}

			printf("输入你想删除的学生：\n");

			char name[20];
			scanf("%s", name);//数组不需要取地址符

			delete_student_by_name(p, &size, name);
			break;

		case 3:
			if (size == 0) {
				printf("当前没有学生，无法修改\n");
				break;
			}

			printf("请输入所要修改的学生：\n");

			char name1[20];
			scanf("%s", name1);

			change_student_by_name(p,size,name1);
			break;

		case 4:
			if (size == 0) {
				printf("当前没有学生，无法查找\n");
				break;
			}

			printf("请输入所要查找的学生姓名：\n");

			char name2[20];
			scanf("%s", name2);

			find_and_print_student(p, size, name2);
			break;

		case 5:
			if (size == 0) {
				printf("当前没有学生\n");
				return;
			}

			print_students(p, size);
			break;

		case 6:
			if (size == 0) {
				printf("当前没有学生，无法排序\n");
				break;
			}

			sort_by_score(p,size);
			break;

		case 7:
			save_students(p,size);
			break;

		case 8:
			free(p);//为了避免覆盖，先清空，再读取
			p = NULL;
			size = 0;
			load_students2(&p, &size);
			printf("读取到 %d 个学生\n", size);
			print_students(p, size);
			break;

		case 0:
			free(p);
			p = NULL;
			return 0;

		default:
			printf("选择错误\n");
		}
	}
	
	

	return 0;
}