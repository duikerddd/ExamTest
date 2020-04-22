//1.基本用法
auto i=0,*p=&i; //√,i是整数、p是整型指针
auto sz=0,pi=3.14; //x,sz和pi类型不一致


//2.与const结合
const int i=2;
auto j=i;        //int auto会过滤const
auto& j=i;       //const int & 厉害
const auto j=i;  //const int   因为过滤了


//3.与指针结合---可推算
//4.与引用结合---可推算出引用原有类型
