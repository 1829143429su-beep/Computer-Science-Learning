#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>

void practice3() {
	int capacity = 5;
	int size = 0;
	int* p = malloc(capacity * sizeof(int));
	if (p == NULL) {
		printf("动态内存分配失败\n");
		return;
	}
	while (1) {
		int value;
		scanf("%d", &value);
		if (value == -1) {
			break;
		}
		if (size==capacity) {
			capacity *= 2;//扩容
			int* temp = realloc(p, capacity * sizeof(int));
			if (temp == NULL) {
				printf("扩容失败\n");
				free(p);//
				return;//
			}
			p = temp;
		}
		*(p + size)=value;//不用scanf,直接赋值
		size++;
	}
	for (int i = 0; i < size; i++) {
		printf("%d", *(p + i));
	}
	printf("\n");
	free(p);
	p = NULL;
}

void dynamic_max() {
	int size = 5;
	int* p = malloc(size * sizeof(int));
	if (p == NULL) {
		printf("动态内存分配失败\n");
		return;
	}
	for (int i = 0; i < size; i++) {
		scanf("%d", p + i);
	}
	
	int max = *(p);
	for (int i = 0; i < size; i++) {
		if (*(p + i) > max) {
			max = *(p + i);
		}
	}
	printf("%d", max);
	free(p);
	p = NULL;
}

void dynamic_sort() {
	int size = 5;
	int* p = malloc(size * sizeof(int));
	if (p == NULL) {
		printf("动态内存申请失败\n");
		return;
	}
	for (int i = 0; i < size; i++) {
		scanf("%d", p + i);
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size - i-1; j++) {
			if (*(p + j) > *(p + j + 1)) {
				int temp = *(p + j);
				*(p + j) = *(p + j + 1);
				*(p + j + 1) = temp;
			}
		}
	}
	for (int i = 0; i < size; i++) {
		printf("%d", *(p + i));
	}
	free(p);
	p = NULL;
}

int main() {
	practice3();
	dynamic_max();
	dynamic_sort();
}