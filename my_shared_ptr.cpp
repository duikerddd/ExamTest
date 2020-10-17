#include<iostream>
#include<mutex>
#include<string>
using namespace std;


template<class T>
class SharedPtr{
public:
	//构造 --- 初始化资源,++操作.和计数
	SharedPtr(T* ptr) 
	  :	_ptr(ptr),
		_cnt(new int(1)),
		_mtx(new mutex)
	{
			if (_ptr == nullptr)
				*_cnt = 0;
	}

	//析构 --- --,为0释放资源
	~SharedPtr()
	{
		Realase();
	}

	//拷贝构造 --- ++操作
	SharedPtr(const SharedPtr<T>& tmp)
		: _ptr(tmp._ptr),
		  _cnt(tmp._cnt),
		  _mtx(tmp._mtx)
	{
		if (_ptr)
			AddRefCount();
	}

	//赋值
	SharedPtr<T>& operator=(const SharedPtr<T>& tmp)
	{
		//不给自己赋值
		if (_ptr != tmp._ptr)
		{
			// 释放管理的旧资源
			Release();
			// 共享管理新对象的资源，并增加引用计数
			_ptr = tmp._ptr;
			_cnt = tmp._cnt;
			_mtx = tmp._mtx;
			if (_ptr){
				AddRefCount();
			}

			//返回引用
			return *this;
		}
	}

	T& operator*()
	{
		return *_ptr;
	}

	T* operator->()
	{
		return _ptr;
	}

	int Count()
	{
		return *_cnt;
	}

	T* Get()
	{
		return _ptr;
	}
	
	

private:
	T* _ptr;
	int* _cnt;
	mutex* _mtx;

	//引用计数 ++
	int AddRefCount()
	{
		_mtx->lock();
		(*_cnt)++;
		_mtx->unlock();
		return *_cnt;
	}

	//--
	int SubRefCount()
	{
		_mtx->lock();
		(*_cnt)--;
		_mtx->unlock();
		return *_cnt;
	}

	void Realase()
	{
		if (_ptr && SubRefCount() == 0)
		{
			delete _ptr;
			delete _cnt;
		}
	}
};

int main()
{
	int* n = new int(2);
	
	{
		SharedPtr<int> sp(n);
		cout << sp.Count() << endl;

		SharedPtr<int> sp2(sp);
		cout << sp.Count() << endl;
	}
	cout << *n << endl;

	return 0;
}
