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

int main()
{
    test_array_reverse();
    return 0;
}