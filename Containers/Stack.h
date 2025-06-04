#ifndef STACK_H
#define STACK_H
#include "Vector.h"

namespace sdf
{
    template<class T>
    class Stack
    {
    public:
        Stack() = default;
        ~Stack() = default;
        void push(const T& val)
        {
            vec.push_back(val);
        }
        void pop()
        {
            vec.pop_back();
        }
        bool empty() const
        {
            return vec.empty();
        }
        T& top()
        {
            return vec.back();
        }
        std::size_t size() const
        {
            return vec.size();
        }

    private:
        Vector<T> vec;
    };
}
#endif // STACK_H
