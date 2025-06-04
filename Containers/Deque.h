#ifndef DEQUE_H
#define DEQUE_H
#include "List.h"


namespace sdf
{
    template<class T>
    class Deque
    {
    public:
        Deque() = default;
        ~Deque() = default;
        void push_back(const T& data)
        {
            l.push_back(data);
        }
        void pop_back()
        {
            l.pop_back();
        }
        void push_front(const T& data)
        {
            l.push_front(data);
        }
        void pop_front()
        {
            l.pop_front();
        }
        [[nodiscard]] std::size_t size() const
        {
            return l.size();
        }
        [[nodiscard]] bool empty() const
        {
            return l.empty();
        }
        void clear() {
            l.clear();
        }
        auto begin() {
            return l.begin();
        }
        auto end() {
            return l.end();
        }


    private:
        List<T> l;
    };
}
#endif // DEQUE_H
