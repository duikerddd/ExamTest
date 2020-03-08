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

//本质上是先将共同部分完成,再对不同处调整
class Info{
public:
Info() :_num(1), _c('a'){}

Info(int num) :Info()
{
_num = num;
}
Info(char c) :Info(), _c(2)
{
_c = c;
}
int _num = 1;
char _c = 'a';
};


int main()
{
Info t1;
Info t2{ 2 };
Info t3{ 'b' };
cout << t1._c << " " << t1._num << endl;
cout << t2._c << " " << t2._num << endl;
cout << t3._c << " " << t3._num << endl;

getchar();
return 0;
}
*/
/*

//类内声明,类外定义显示缺省赋值运算符重载
Point& Point::operator=(const Point& p) = default;


int main()
{
Point p1;
Point p2(2, 2);
p1.Print();
p2.Print();

getchar();
return 0;
}


class String{
public:

private:
int _left = 0;
int _right = 0;
};
*/


//int main()
//{
//	int a = 10;
//	//左值引用
//	int& left_ref = a;
//	//右值引用
//	int&& right_ref;
//	int&& right_ref = a;
//
//
//	////左值引用不能引用右值  但const&可以
//	//const int& left_ref2 = 10;
//	////右值引用不能引用左值  但std::move(左值)可以
//	//int&& right_ref2 = move(a);
//
//
//
//	return 0;
//}
//
//class Point{
//public:
//	Point(int x, int y) :_x(x), _y(y){}
//
//	Point(const Point& p) :_x(p._x), _y(p._y){}
//
//	//不好的写法
//	Point(Point&& p) :_x(p._x), _y(p._y){}
//	
//	//移动构造引用的是右值,将右值内容move来提高效率
//	Point(Point&& p) :_x(move(p._x)), _y(move(p._y)){}
//
//	void Print()
//	{
//		cout << _x << " " << _y << endl;
//	}
//private:
//	int _x = 2;
//	int _y = 3;
//};
//
//Point GetTempPoint()
//{
//	Point p(1, 1);
//	return p;
//}
//
//int main()
//{
//	Point p(GetTempPoint());
//
//	getchar();
//	return 0;
//}

int main()
{
	string A("abc");
	string&& Rval = std::move(A);
	string B(Rval);    // this is a copy , not move.
	cout << A << endl;   // output "abc"
	string C(std::forward<string>(Rval));  // move.
	cout << A << endl;       /* output "" */

	getchar();
	return 0;
}
