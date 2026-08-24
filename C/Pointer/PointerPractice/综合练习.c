#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>

//输出两个字符串长度
int my_strlen(char* dest) {
	int i = 0;
	while (*dest != 0) {
		i++;
		dest++;
	}//不包括'\0'
}



int main() {
	//输入两个字符串
	char* dest = "hello";
	char* src = "world";
	char* str;
    //输出两个字符串长度
	printf("字符串长度分别是%zu,%zu", strlen(dest),strlen(src);
	int length1 = my_strlen(dest);
	int length2 = my_strlen(src);
	printf("字符串长度分别是%d,%d", length1, length2);

   //复制第一个字符串
    
比较两个字符串
↓
把两个字符串拼接起来
↓
输出最终结果
void 
	