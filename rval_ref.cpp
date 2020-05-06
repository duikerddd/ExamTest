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

//完美转发: 让参数安按照原来的类型转发到另一个函数,因为参数默认情况下都会转换成左值引用类型.
void Fun(int& x){ cout << "lvalue ref" << endl; }
void Fun(int&& x){ cout << "rvalue ref" << endl; }
void Fun(const int& x){ cout << "const lvalue ref" << endl; }
void Fun(const int&& x){ cout << "const rvalue ref" << endl; }

template<typename T>
void PerfectForword(T&& t){ Fun(forward<T>(t)); }

int main()
{
	PerfectForword(10);  //rvalue ref

	int a = 2;
	PerfectForword(a);     //lvalue ref
	PerfectForword(move(a));   //rvalue ref

	const int b = 2;
	PerfectForword(b);   //const lvalue ref
	PerfectForword(move(b)); //const rvalue ref

	return 0;
}
