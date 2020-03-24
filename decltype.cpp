#include <initializer_list> // This header is required
#include <iostream>
#include<string>
using namespace std;


/*
// 如果没有带参数,推导函数的类型
cout << typeid(decltype(GetMemory)).name() << endl;


// 如果带参数列表,推导的是函数返回值的类型
// ps: 只是推演,不会调用函数
cout << typeid(decltype(GetMemory(2))).name() << endl;


//1.推演表达式类型作为变量的定义类型
int a = 10;
int b = 20;

decltype(a + b) c;
cout << typeid(c).name() << endl;



template <class Tp>
void print_ilist(const initializer_list<Tp> &ilist)
{
for (auto it = ilist.begin(); it != ilist.end(); ++it)
cout << *it << endl;
}

struct Foo
{
int vals[10];
int n = 0;

Foo(const initializer_list<int> &ilist) {
for (int v : ilist)
vals[n++] = v;
}
};

//2.推演函数返回值类型
void *GetMemory(size_t size)
{
return malloc(size);
}


