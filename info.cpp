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
