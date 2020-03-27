
class Point{
 public:
    //显示生成默认函数
    Point()=defalut;
    Point& operator=(const Point& p);
 private:
    int _x;
    int _y;
};


//显示删除默认函数
Point& Point::operator=(const Point& p) = delete;


int main()
{
Point p1;
Point p2(2, 2);
p1.Print();
p2.Print();

 
getchar();
return 0;
}

