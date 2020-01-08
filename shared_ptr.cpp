#include<thread>
#include<mutex>
template <class T>
class SharedPtr
{
    public:
        //构造
        SharedPtr(T* ptr = nullptr)
        : _ptr(ptr)
        , _pRefCount(new int(1))
        , _pMutex(new mutex)
        {
            // 如果是一个空指针对象，则引用计数给0
            if (_ptr == nullptr)
                *_pRefCount = 0;
        }
        
        //析构
        ~SharedPtr() {Release();}
        
        //拷贝构造
        SharedPtr(const SharedPtr<T>& sp)
        : _ptr(sp._ptr)
        , _pRefCount(sp._pRefCount)
        , _pMutex(sp._pMutex)
        {
            // 如果是一个空指针对象，则不加引用计数，否则才加引用计数
            if (_ptr)
                AddRefCount();
        }
        
        // sp1 = sp2
        SharedPtr<T>& operator=(const SharedPtr<T>& sp)
        {
            //if (this != &sp)等同于下面
            if (_ptr != sp._ptr)
            {
                // 释放管理的旧资源
                Release();
                // 共享管理新对象的资源，并增加引用计数
               _ptr = sp._ptr;
               _pRefCount = sp._pRefCount; 
               _pMutex = sp._pMutex;
               if (_ptr){
                   AddRefCount();
            }
            return *this;
       }
        
        //指针操作
        T& operator*() {return *_ptr;}
        T* operator->() {return _ptr;}
        int UseCount() {return *_pRefCount;}
        T* Get() { return _ptr; }

        //原子计数: ++操作    
        int AddRefCount()
        {
            // 加锁或者使用加1的原子操作
            _pMutex->lock();
            ++(*_pRefCount);
            _pMutex->unlock();
            return *_pRefCount;
        }
        //原子计数: --操作
        int SubRefCount()
        {
            // 加锁或者使用减1的原子操作
            _pMutex->lock();
            --(*_pRefCount);
            _pMutex->unlock();
            return *_pRefCount;
        }
        
    private:
        //--与判断释放操作
        void Release()
        {
            // 引用计数减1，如果减到0，则释放资源
            if (_ptr && SubRefCount() == 0)
            {
                delete _ptr;
                delete _pRefCount;
            }
        }
        
    private:
        int* _pRefCount; // 引用计数,用指针让所有对象共享该值
        T* _ptr; // 指向管理资源的指针
        mutex* _pMutex; // 互斥锁
 };
