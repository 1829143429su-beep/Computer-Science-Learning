#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

//输出变量和地址
void test_address()
{
    int a = 4;
    int* p = &a;
    printf("a = %d\n", a);//变量a
    printf("*p = %d\n", *p);//*p是解引用，获取指针p指向的值，即a
    printf("a的地址是%p",p);//指针变量p，保存a的地址
    printf("a的地址是%p", &a);//&a取a的地址
}

//用指针修改变量
void test_modify() 
{
    int a = 4;
    int* p = &a;
    printf("输入想要修改的值：");
     scanf("%d", p);
   // *p = 10;
  
    printf("a=%d", a);
}

//使用指针交换两个变量
void test_swap()
{
    int a = 4;
    int b = 5;
    int* p1 = &a;
    int* p2 = &b;
    int temp = *p1;

    *p1=*p2;
    *p2=temp;
   
    printf("交换后，a=%d,b=%d", a, b);
}

//使用指针遍历数组
void test_array()
{
    int arr[5] = { 1,2,3,4,5 };
    int* p = arr;
    int i = 0;
    while (i < 5) {
        printf("%d\n", *p);
        i++;
        p++;
    }
}

//使用函数和指针修改变量
void test_modify1(int* p)
{
    int b=0;
    printf("输入修改后的值:");
    scanf("%d",&b);
    *p = b;
}
void test_modify_with_function()
{
    int a = 4;
    int* p = &a;
    printf("修改前a=%d\n", a);
    test_modify1(&a);//p也可以
    printf("修改后a=%d", a);
}

//NULL
void test_null()
{
    int* p = NULL;
    if (p == NULL) {
        printf("p没有指向任何对象\n");
    }
    int a = 10;
    p = &a;
    if (p != NULL) {
        printf("%d", *p);
    }
}


//指针遍历数组
void test_array_with_pointer()
{
    int arr[5] = { 1,2,3,4,5 };
    int* p = arr;
   
    while (p < arr + 5) {
        printf("%d\n", *p);
        p++;
    }
}

//使用指针求数组最大值
void test_array_max()
{
    int arr[5] = { 3,8,2,10,5 };
    int* p = arr;
    int max = *p;
    p++;
    while (p < arr + 5) {
        if (*p > max) {
            max = *p;
        }
        p++;
    }
    printf("数组中的最大值是：%d", max);
}

//指针求数组最小值
void test_array_min()
{
    int arr[5] = { 3,8,2,10,5 };
    int* p = arr;
    int min = *p;
    p++;
    while (p < arr + 5) {
        if (*p < min) {
            min = *p;
        }
        p++;
    }
    printf("数组中的最小值是：%d",min);
}

//使用指针求数组平局值
void test_array_average()
{
    int arr[5] = { 3,8,2,10,5 };
    int* p = arr;
    int sum = 0;
    while (p < arr + 5) {
        sum += *p;
        p++;
    }
    float average = sum * 1.0 / 5;
    //float average = (float)sum / 5;
    printf("数组的平均数是%f", average);
}

//使用指针进行数组元素位置查找:10
void test_array_search() {
    int arr[5] = { 3, 8, 2, 10, 5 };
    int* p = arr;
    int target = 10;
    int i = 0;
    int found = 0;//添加标志变量
    while (p < arr + 5) {
        if (*p != target) {
            p++;
            i++;
        }
        else {
            printf("位置在%d", i);
            found = 1;
            break;
        }
    }
    if (found == 0) {
        printf("没有找到\n");
    }
}

//数组逆序遍历
void test_array_re()
{
    int arr[5] = { 3, 8, 2, 10, 5 };
    int* p = arr;
    int* p2 = arr + 4;
    while (p < arr + 5) {
        printf("%d ", *p2);
        p2--;
        p++;
    }
}
//数组逆序输出（改变数组）
void test_array_reverse()
{
    int arr[5] = { 3, 8, 2, 10, 5 };
    int* p = arr;
    int* p2 = arr + 4;
    int temp;
    while (p < p2) {//奇偶都适用
        temp = *p;
        *p = *p2;
        *p2 = temp;
        p++;
        p2--;
    }
    for (int i = 0; i < 5; i++) {
        printf("%d ", arr[i]);
    }   
}

//数组实现冒泡排序(升序)
void test_array_buuble_sort()
{
    int arr[5] = { 3,8,2,10,5 };
   
    for (int i = 0; i < 4; i++) {//4轮
        for (int j = 0; j < 4-i; j++) {//4项 有下一项
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j+ 1] = temp;
            }
        }
    }
    for (int k = 0; k < 5; k++) {
        printf("%d ", arr[k]);
    }
}
//指针实现冒泡排序(升序)
void test_pointer_buuble_sort()
{
    int arr[5] = { 3,8,2,10,5 };
    for (int i = 0; i < 4; i++) {//4轮
        int* p = arr;
        while(p<arr+4-i) {//4项 有下一项
            if (*p > *(p+1) ){
                int temp = *p;
                *p = *(p+1);
                *(p+1)= temp;
            }
            p++;
        }
    }
    int* p = arr;
    while (p < arr + 5) {
        printf("%d", *p);
        p++;
    }
}

//指针与函数：
//1.传值交换
void value_swap(int a, int b) {
    int temp = a;
    a = b;
    b = temp;
    printf("a=%d,b=%d\n", a, b);
}
void result1()
{
    int x = 5, y = 10;
    value_swap(x, y);
    printf("x=%d,y=%d\n", x, y);
}
//传址交换（指针）
void address_swap(int* a,int*b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
    printf("*a=%d,*b=%d\n", *a, *b);
}
void result2()
{ 
    int x = 5, y = 10;
    address_swap(&x, &y);
    printf("x=%d,y=%d\n", x, y);
}

//2.指针作为函数参数求数组最大值
int array_max(int* arr, int size) {
    int max = *arr;
    for (int i = 1; i < size; i++) {
        if (*(arr+i) > max) {
            max = *(arr+i);
        }
    }
    return max;
}
//最小值
int array_min(int* arr, int size)
{
    int min = *arr;
    for (int i = 1; i < size; i++) {
        if (*(arr + i) < min) {
            min = *(arr + i);
        }
    }
    return min;
}
void result() {
    int arr[5] = { 3,2,10,5,8 };
    int size = 5;
    int result3 = array_max(arr, 5);
    int result4 = array_min(arr, 5);
    printf("最大值为：%d\n最小值是：%d", result3,result4);
}

//3.排序
void array_sort(int* arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i-1; j++) {
            if (*(arr + j) > *(arr + j + 1)) {
                int temp = *(arr+j);
                *(arr + j) = *(arr + j + 1);
                *(arr + j + 1) = temp;
            }
        }
    }
}
void result3() {
    int arr[5] = { 3,2,10,5,8 };
    int size = 5;
    array_sort(arr, 5);//排序
    for (int i = 0; i < size; i++) {
        printf("%d ", *(arr + i));//输出
    }
}

//4.数组逆序
void array_reverse(int* arr, int size) {
    for (int i = 0; i < size / 2 ; i++) {
        int temp = *(arr + i);
        *(arr + i) = *(arr + size-i-1);
        *(arr + size-i-1) = temp;
    }
}
void result4() {
    int arr[5] = { 3,2,10,5,8 };
    int size = 5;
    array_reverse(arr, 5);//逆序
    for(int i = 0; i < size; i++) {
        printf("%d ", *(arr + i));//输出
    }
}


//指针与函数
//1.自定义字符串长度函数
int my_strlen(char* str)
{
    int count = 0;
    while (*str !='\0')/* 字符不是 \0 */
    {
        count++;
        str++;
    }
    return count;
}
int result5() {
    char str[] = "hello";
    int len = my_strlen(str);
    printf("长度：%d\n", len);
}

//2.字符串复制函数
void my_strcpy(char*dest,char*src)
{
    while (*src!='\0')
    {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
}
void result6() {
    char* dest[20];//初始化
    char* src = "hello";
    my_strcpy(dest, src);
    printf("复制后的字符串：%s\n", dest);
}

//3.字符串比较函数
int my_strcmp(char* str1, char* str2)
{
    while (*str1 != '\0' && *str2 != '\0') {
        if (*str1 == *str2) {
            str1++;
            str2++;
        }
        else {
            break;
        }
        
    }
    if (*str1 == *str2) {
        return 0;
    }
    else if (*str1 > *str2) {
        return 1;//不输出，只比较
       //return已经结束函数了，不需要break
    }
    else {
        return -1;
    }
}
void result7() {
    char* str1 = "abe";
    char* str2 = "abd";
    int result = my_strcmp(str1, str2);
    if (result == 0) {
        printf("字符串相等\n");
    }else if (result == 1) {
        printf("str1>str2\n");
    }else if (result == -1) {
        printf("str1<str2\n");
    }
}

//4.字符串连接函数
void my_strcat(char* dest, char* src)
{
    while (*dest != '\0') {
        dest++;
    }
    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
}
void result8() {
    char dest[20] = "hello";
    char* src = "world";
    my_strcat(dest, src);//void
    printf("拼接后的函数是：%s\n", dest);
}
int main()
{
    result8();
    return 0;
}