//虚继承下,最终派生类构造顺序: B-->B1/B2 ---> D
class B{
	int _b;
public:
	B(int N ) :_b(N){}
};

class B1 : virtual public B{
	int _b1;
public:
	B1(int N = 1) : B(1), _b1(N){}
};



class B2 : virtual public B{
	int _b2;
public:
	B2(int N = 1) : B(2),_b2(N){}
};

class D :  public B1,  public B2{
	int _d;
public:
	D(int N = 1) : B1(2),B2(3), _d(N){}
};

int main()
{
	D d;
	return 0;
}
