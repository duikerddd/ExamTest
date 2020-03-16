
#include<thread>

/*
void fun()
{
cout << "A new thread ------" << endl;
}

int main()
{
thread t(fun);
t.join();
cout << "Main thread -------" << endl;
return 0;
}


//使用lambda表达式创建线程
int main()
{
int n1 = 100;
int n2 = 200;
thread t([&](int addNum){
n1 += addNum;
n2 += addNum;
}, 500);

return 0;
}


void foo()
{
this_thread::sleep_for(std::chrono::seconds(1));
}

int main()
{
thread t(foo);
cout << "before join, joinable =" << t.joinable() << endl;

t.join();
cout << "after join,joinable =" << t.joinable() << endl;

return 0;
}


long sum = 0;

void fun(size_t num)
{
for (size_t i = 0; i < num; ++i)
{
++sum;
}
}

int main()
{
cout << "Before joining,sum = " << sum << std::endl;

thread t1(fun, 10000000);
thread t2(fun, 10000000);
t1.join();
t2.join();

cout << "After joining,sum = " << sum << std::endl;
return 0;
}


#include<mutex>
long sum = 0;
mutex m;

void fun(size_t num)
{
for (size_t i = 0; i < num; ++i)
{
m.lock();
++sum;
m.unlock();
}
}

int main()
{
cout << "Before joining,sum = " << sum << std::endl;

thread t1(fun, 10000000);
thread t2(fun, 10000000);
t1.join();
t2.join();

cout << "After joining,sum = " << sum << std::endl;
return 0;
}
*/

#include<mutex>
#include<atomic>

atomic_long sum{ 0 };

void fun(size_t num)
{
	for (size_t i = 0; i < num; ++i)
		++sum;
}

int main()
{
	cout << "Before joining,sum = " << sum << std::endl;

	thread t1(fun, 10000000);
	thread t2(fun, 10000000);
	t1.join();
	t2.join();

	cout << "After joining,sum = " << sum << std::endl;
	return 0;
}
