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
