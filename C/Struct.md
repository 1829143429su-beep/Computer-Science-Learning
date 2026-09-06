### 结构体

学习：

struct Student
{
    char name[20];
    int age;
    double score;
};

然后：

struct Student s;

继续：

struct Student* p = &s;

重点：

s.age

和

p->age

之间的关系。
