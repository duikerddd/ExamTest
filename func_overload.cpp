int Add(int left, int right)
{
return left+right;
}
double Add(double left, double right)
{
return left+right;
}
long Add(long left, long right)
{
return left+right;
}


int main()
{
    Add(10, 20);       //在程序编译期间对函数的参数进行类型推演
                       //根据推演结果去选择合适的调用函数
    Add(10.0, 20.0);
    Add(10L, 20L);
    return 0;
}
