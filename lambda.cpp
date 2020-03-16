//struct Good{
//	string _name;
//	int _val;
//};
//
//struct Compare{
//	bool operator()(const Good& g1,const Good& g2)
//	{
//		return g1._val <= g2._val;
//	}
//};
//
//int main()
//{
//	Good gs[] = {{ "苹果", 2 }, { "香蕉", 3 }, { "西瓜", 1 }};
//	//lambda表达式实际上是一个匿名函数
//	sort(gs, gs + sizeof(gs) / sizeof(gs[0]), [](const Good& g1, const Good& g2)
//												{
//													return g1._val <= g2._val;
//												});
//
//	return 0;
//}
using namespace std;


int main(){
	// 最简单的lambda表达式, 该lambda表达式没有任何意义    
	[]{};

	// 省略参数列表和返回值类型，返回值类型由编译器推导为int
	int a=3, b=4; 
	[=]{ return a+3; }; 

	// 省略了返回值类型，无返回值类型
	auto fun1 = [&](int c){b = a+c; };  
	fun1(10);
	cout << a <<" "<< b <<endl;    //a=3 b=13

	// 各部分都很完善的lambda函数
	auto fun2= [=, &b](int c)->int{return b+=a+c; }; 
	cout<<fun2(10)<<endl;    //b=26

	// 复制捕捉x
	int x=10;
	auto add_x = [x](int a) mutable { x*=2; return a+x; }; 
	cout<< add_x(10) <<endl;   //x=30
	
	return 0;
}

/*
void(*PF)();
int main(){
	auto f1 = []{cout << "hello world" << endl; }; 
	auto f2 = []{cout << "hello world" << endl; };
	
	//f1 = f2; 
	// 编译失败--->提示找不到operator=(),因为lambda表达式底层上就是一个重载()的匿名类
	// 允许使用一个lambda表达式拷贝构造一个新的副本
	auto f3(f2);
	f3();

	// 可以将lambda表达式赋值给相同类型的函数指针
	PF=f2;
	PF();
	
	return 0;
}



class Rate{
public:
	Rate(double rate) : _rate(rate){}

	double operator()(double money, int year)
	{
		return money* _rate * year;
	}

private:
	double _rate;
};

int main()
{
	// 函数对象
	double rate=0.49;
	Rate r1(rate);
	r1(10000, 2);

	// 仿函数
	auto r2= [=](double monty, int year)->double{return monty*rate*year; };
	r2(10000, 2);

	return 0;
}
*/
