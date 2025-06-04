# Memory

和内存相关的类
有一个总的头文件[Memory.h](./Memory.h)

## UniquePtr
UniquePtr保证的是只有一个对象在管理相应的资源，并且能做到RAII机制，可以有效且安全地管理堆资源，保证在智能指针对象销毁时，分配在堆上的资源会同时被销毁。以下是接口介绍：

### get

返回对应的裸指针，但是不建议裸指针和智能指针混合使用，示例如下：
```C++
    UniquePtr<int> p(new int(1));
    needPointerNaked(p.get());
```

### swap

和另外一个UniquePtr交换管理的对象，示例如下：
```c++
    UniquePtr<int> p(new int(1));
    UniquePtr<int> p2(new int(1));
    p.swap(p2);
```

### reset

重置管理的资源，不传入参数默认为释放当前资源，否则为释放原有资源，接管新的资源。
```c++
    UniquePtr<int> p(new int(1));
    p.reset();
    p == nullptr; //true
    p.reset(new int(2));
    *p; //2
```

### 重载*和->运算符

允许你和使用裸指针一样的使用智能指针。

## SharedPtr

SharedPtr对应的是shared_ptr智能指针，内存空间使用较大，因为要保证线程安全，我们引入了引用计数和锁，确保它是线程安全的。  
SharedPtr允许多个对象同时管理一个资源，这个资源只有在最后一个智能指针放弃管理资源时才会被释放。  
以下时接口介绍：

### get

返回管理的裸指针

### useCount

返回当前的引用计数

### reset

用法同UniquePtr，重置对那个资源进行管理，不传入参数或者传入nullptr则只释放当前资源。

### swap

交换两个SharedPtr管理的对象

## WeakPtr

使用SharedPtr很难避免一个问题，就是循环引用，WeakPtr就是来解决这个问题的

### 构造函数

要求显式调用，并且传入一个SharedPtr对象

### reset

重置资源管理的对象

### lock

返回绑定的SharedPtr智能指针对象，会拷贝一份，如果管理的资源已经引用计数清零，那么就返回空对象。
