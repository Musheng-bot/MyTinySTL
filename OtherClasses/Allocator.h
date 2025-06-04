//
// Created by meish on 25-5-22.
//

#ifndef ALLOCATOR_H
#define ALLOCATOR_H
#include <utility>
namespace sdf {
//定义了自己的内存分配器类
template<class T>
class Allocator
{
    public:
        //内存分配
        static T* allocate(const size_t size = 1)
        {
            return static_cast<T*>(malloc(size * sizeof(T)));
        }

        //内存释放
        static void deallocate(T* p)
        {
            free(p);
        }

        // //负责构造对象
        // static void construct(T *p,const T &val)
        // {
        //     new (p) T(val);
        // }
        //
        // //负责移动构造对象
        // static void constrcut(T *p,T &&val)
        // {
        //     new (p) T(std::move(val));
        // }
        template<class T2>
        static void construct(T* p, T2&& val)
        {
            new (p) T(std::forward<T2>(val));
        }
        //用转发代替两个函数

        //负责析构对象
        static void destroy(T* p, const int size = 1)
        {
            for (int i = 0; i < size;++i)
            {
                p->~T();
                ++p;
            }
        }


};

} // sdf

#endif //ALLOCATOR_H
