

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

