#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>

//1.动态申请一个整数
void dynamic_mal() {
	int* p = malloc(sizeof(int));
	//判断是否申请成功
	if (p == NULL) {
		printf("动态内存申请失败");
			return;//结束该void函数
	}
	*p = 100;
	printf("%d", *p);
	free(p);
	p = NULL;//不让p指向已释放的空间
}

//2.动态申请5个整数
void dynamic_mal5() {
	int* p = malloc(5 * sizeof(int));

	if (p == NULL) {
		printf("动态内存申请失败");
		return;
	}
	*p = 10;
	*(p + 1) = 20;
	*(p + 2) = 30;
	*(p + 3) = 40;
	*(p + 4) = 50;
	int i = 0;
	int* cur = p;
	while (i < 5) {
		printf("%d ", *cur);
		i++;
		cur++;
	}
	free(p);
	p = NULL;
}

//3.修改动态内存
void dynamic_revise() {
	int* p = malloc(5 * sizeof(int));

	if (p == NULL) {
		printf("动态内存申请失败");
		return;
	}
	*p = 10;
	*(p + 1) = 20;
	*(p + 2) = 30;//要求：改为100
	*(p + 3) = 40;
	*(p + 4) = 50;
	*(p +2) = 100;
	int i = 0;
	int* cur = p;
	while (i < 5) {
		printf("%d ", *cur);
		i++;
		cur++;
	}
	free(p);
	p = NULL;
}

//动态数组
//1.动态输入数组
void dynamic_array() {
	int n=0;
	printf("请输入n值：\n");
	scanf("%d", &n);
	if (n <= 0)
	{
		printf("n必须大于0\n");
		return;
	}

	int* p = malloc(n * sizeof(int));
	if (p == NULL)//
	{
		printf("动态内存申请失败\n");
		return;
	}

	printf("请输入%d个整数：\n",n);
	for (int i = 0; i < n; i++) 
	{
		scanf("%d", p + i);
	}

	printf("数组内容：");
	for (int i = 0; i < n; i++)
	{
		printf("%d ", *(p + i));
	}
	free(p);
	p = NULL;
}

//2.动态数组求最大值
int dynamic_array_max(int* arr, int size) {
	int max = *arr;//使用第一个元素初始化
	for (int i = 0; i < size; i++) {
		if (*(arr + i) > max) {
			max = *(arr + i);
		}
	}
	return max;
}

//3.动态数组排序
void dynamic_array_sort(int* arr, int size) {
	for (int i = 1; i < size; i++) {
		for (int j = 0; j < size - 1-i; j++) {
			if (*(arr + j) > *(arr + j + 1)) {
				int temp = *(arr + j);
				*(arr + j) = *(arr + j + 1);
				*(arr + j + 1) = temp;
			}
		}
	}
}
void result1() {
	int size = 0;
	printf("请输入元素数量：\n");
	scanf("%d", &size);
	if (size <= 0)
	{
		printf("元素数量必须大于0\n");
		return;
	}

	int* arr = malloc(size * sizeof(int));//申请
	if (arr == NULL) {
		printf("动态内存申请失败\n");
		return;
	}

	printf("请输入%d个整数：\n", size);
	for (int i = 0; i < size; i++) {
		scanf("%d", arr + i);
	}
	int result = dynamic_array_max(arr, size);
	printf("最大值为：%d\n", result);


	dynamic_array_sort(arr, size);
	printf("排序后：");
	for (int i = 0; i < size; i++) {
		printf("%d ", *(arr + i));
	}

	free(arr);//释放
	arr = NULL;
}
//4.调整动态数组内存
void my_realloc() {
	int size = 5;
	int* arr = malloc(size * sizeof(int));
	if (arr == NULL) {//检查1
		printf("动态内存申请失败\n");
		return;
	}
	printf("请输入%d个整数:\n", size);
	for (int i = 0; i < size; i++) {
		scanf("%d", arr + i);
	}

	int size2 = 10;
	int* temp = realloc(arr, size2* sizeof(int));
	if (temp == NULL) {//检查2
		printf("扩容失败\n");
		free(arr);
		return;
	}
	arr = temp;

	printf("请输入新增的%d个整数:\n",(size2 - size));
	for (int i = size; i < size2; i++) {
		scanf("%d", arr + i);
	}

	printf("新增后的动态数组为：\n");
	for (int i = 0; i < size2; i++) {
		printf("%d ", *(arr + i));
	}

	free(arr);
	arr = NULL;
}

//5.测试内存泄漏
void test_memory_leak() {
	int* p = malloc(5 * sizeof(int));
	if (p == NULL) {
		printf("动态内存申请失败\n");
		return;
	}

	printf("请输入5个整数:\n");
	for (int i = 0; i < 5; i++) {
		scanf("%d", p + i);
	}
	//故意不free(p);
}

//6.测试野指针
void test_wild_pointer() {
	//int* p;
	//*p = 100;
}

//7.测试double free
void test_double_free() {
	int* p = malloc(5 * sizeof(int));
	if (p == NULL) {
		printf("动态内存申请失败\n");
		return;
	}
	printf("输入5个整数：\n");
	for (int i = 0; i < 5; i++) {
		scanf("%d", p + i);
	}
	free(p);
	p = NULL;
	free(p);
}
int main() {
	test_double_free();
	return 0;
}