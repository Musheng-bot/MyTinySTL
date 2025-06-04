#ifndef VECTOR_H
#define VECTOR_H
#include <stdexcept>
#include <initializer_list>
#include "../OtherClasses/Allocator.h"

namespace sdf {
    template<class T, class Alloc = Allocator<T>>
    class Vector
    {
    public:
        Vector();
        ~Vector();
        Vector(const Vector& vec);
        Vector(Vector&& vec) noexcept;
        Vector(std::initializer_list<T> lst);
        Vector& operator=(const Vector& vec);
        Vector& operator=(Vector&& vec) noexcept;
        explicit Vector(std::size_t n);
        Vector(std::size_t n, const T& val);

        [[nodiscard]] bool empty() const;
        [[nodiscard]] std::size_t size() const;
        const T& front() const;
        const T& back() const;

        [[nodiscard]] bool operator==(const Vector&) const;
        [[nodiscard]] bool operator!=(const Vector&) const;
        T& operator[](std::size_t n);
        const T& operator[](std::size_t n) const;

        void push_back(const T& val);
        void pop_back();
        void sort();//排序，快排，堆排，插排混合使用
        void unique();//删除重复元素
        void reverse() noexcept;//改为逆序
        void swap(Vector& vec) noexcept;

        class Iterator;
        Iterator insert(const Iterator&, size_t, const T&);//在Iterator it前插入n个val元素，返回插入的第一个元素的迭代器
        Iterator erase(const Iterator&);//删除迭代器指定位子的元素，并返回后一个元素的迭代器

        const Iterator& begin();
        const Iterator& end();

    private:
        std::size_t length;
        std::size_t capacity;
        Iterator begin_{};

        void expand();
        void insertSort(int begin, int end);
        void heapSiftDown(int, int, int);
        void heapSort(int begin, int end);
        void sort(int begin, int end, int depth);
    };

    template <class T, class Alloc>
    Vector<T, Alloc>::Vector() :length(0), capacity(1), begin_(Alloc::allocate(1))
    {
    }

    template <class T, class Alloc>
    Vector<T, Alloc>::~Vector()
    {
        Alloc::destroy(&*begin_, length);
        Alloc::deallocate(&*begin_);
        length = 0;
        capacity = 0;
        begin_ = Iterator(nullptr);
        begin_ + length = Iterator(nullptr);
        begin_ + capacity = Iterator(nullptr);
    }

    template <class T, class Alloc>
    Vector<T, Alloc>::Vector(const Vector& vec) :
        length(vec.length),
        capacity(vec.capacity),
        begin_(Alloc::allocate(capacity))
    {
        auto it1 = begin_;
        auto it2 = vec.begin_;
        for (; it1 != begin_ + length; ++it1)
        {
            Alloc::construct(&*it1, *it2);
        }
    }

    template <class T, class Alloc>
    Vector<T, Alloc>::Vector(Vector&& vec) noexcept :
        length(vec.length),
        capacity(vec.capacity),
        begin_(vec.begin_)
    {
        vec.length = 0;
        vec.capacity = 0;
        vec.begin_ = Iterator();
    }

    template <class T, class Alloc>
    Vector<T, Alloc>::Vector(std::initializer_list<T> lst) :
        length(lst.size()),
        capacity(length),
        begin_(Alloc::allocate(capacity))
    {
        auto it1 = lst.begin();
        auto it2 = begin_;
        for (; it1 != lst.end(); ++it1)
        {
            Alloc::construct(&*it2, *it1);
            ++it2;
        }
    }

    template <class T, class Alloc>
    Vector<T, Alloc>& Vector<T, Alloc>::operator=(const Vector& vec)
    {
        if (&vec == this)
        {
            return *this;
        }
        Alloc::destroy(&*begin_, length);
        Alloc::deallocate(&*begin_);
        length = vec.length;
        capacity = vec.capacity;
        begin_ = Iterator(Alloc::allocate(capacity));
        begin_ + length = begin_ + length;
        begin_ + capacity = begin_ + capacity;
        auto it1 = begin_;
        auto it2 = vec.begin_;
        for (; it1 != begin_ + length; ++it1)
        {
            Alloc::construct(&*it1, std::move(*it2));
        }
        return *this;
    }

    template <class T, class Alloc>
    Vector<T, Alloc>& Vector<T, Alloc>::operator=(Vector&& vec) noexcept
    {
        Alloc::destroy(&*begin_, length);
        Alloc::deallocate(&*begin_);
        length = vec.length;
        capacity = vec.capacity;
        begin_ = vec.begin_;
        begin_ + length = vec.begin_ + length;
        begin_ + capacity = vec.begin_ + capacity;
        vec.length = 0;
        vec.capacity = 0;
        vec.begin_ = Iterator(nullptr);
        vec.begin_ + length = Iterator(nullptr);
        vec.begin_ + capacity = Iterator(nullptr);


        return *this;
    }

    template <class T, class Alloc>
    Vector<T, Alloc>::Vector(std::size_t n) :
        length(0),
        capacity(n),
        begin_(Alloc::allocate(n))
    {
    }

    template <class T, class Alloc>
    Vector<T, Alloc>::Vector(std::size_t n, const T& val) :
        length(n),
        capacity(n),
        begin_(Alloc::allocate(n))
    {
        for (auto it = begin_; it != begin_ + length; ++it)
        {
            *it = val;
        }
    }

    template <class T, class Alloc>
    bool Vector<T, Alloc>::empty() const
    {
        return length == 0;
    }

    template <class T, class Alloc>
    std::size_t Vector<T, Alloc>::size() const
    {
        return length;
    }

    template <class T, class Alloc>
    const T& Vector<T, Alloc>::front() const
    {
        return *begin_;
    }

    template <class T, class Alloc>
    const T& Vector<T, Alloc>::back() const
    {
        return *(begin_ + length - 1);
    }

    template <class T, class Alloc>
    bool Vector<T, Alloc>::operator==(const Vector& vec) const
    {
        if (length != vec.length)
        {
            return false;
        }
        auto it1 = begin_;
        auto it2 = vec.begin_;
        for (; it1 != begin_ + capacity; ++it1)
        {
            if (*it1 != *it2)
            {
                return false;
            }
        }
        return true;
    }

    template <class T, class Alloc>
    bool Vector<T, Alloc>::operator!=(const Vector& vec) const
    {
        return !(*this == vec);
    }

    template <class T, class Alloc>
    T& Vector<T, Alloc>::operator[](std::size_t n)
    {
        if (n >= length)
        {
            throw std::out_of_range("Not in the range");
        }
        return *(begin_ + n);
    }

    template <class T, class Alloc>
    const T& Vector<T, Alloc>::operator[](std::size_t n) const
    {
        if (n >= length)
        {
            throw std::out_of_range("Not in the range");
        }
        return *(begin_ + n);
    }

    template <class T, class Alloc>
    void Vector<T, Alloc>::push_back(const T& val)
    {
        if (length == capacity)
        {
            expand();
        }
        Alloc::construct(&*begin_ + length, val);
        ++length;
    }

    template <class T, class Alloc>
    void Vector<T, Alloc>::pop_back()
    {
        Alloc::destroy(&*(begin_ + length - 1));
        --length;
    }

    template <class T, class Alloc>
    void Vector<T, Alloc>::sort()
    {
        sort(0, length - 1, 0);
    }

    template <class T, class Alloc>
    void Vector<T, Alloc>::unique()
    {
        if (length == 0 || length == 1)
        {
            return;
        }
        auto result = begin_;
        auto first = begin_;
        while (++first != begin_ + length)
        {
            if (*result != *first)
            {
                *++result = *first;
            }
        }
        ++result;
        auto last = begin_ + length;
        begin_ + length = result;
        for (; result != last; ++result)
        {
            Alloc::destroy(&*result);
            --length;
        }
    }

    template <class T, class Alloc>
    void Vector<T, Alloc>::reverse() noexcept
    {
        auto it1 = begin_;
        auto it2 = begin_ + length - 1;
        while (it2 - it1 > 0)
        {
            std::swap(*it1, *it2);
            ++it1;
            --it2;
        }
    }

    template <class T, class Alloc>
    void Vector<T, Alloc>::swap(Vector& vec) noexcept
    {
        std::swap(length, vec.length);
        std::swap(capacity, vec.capacity);
        std::swap(begin_, vec.begin_);
        std::swap(begin_ + length, vec.begin_ + length);
        std::swap(begin_ + capacity, vec.begin_ + capacity);
    }

    template <class T, class Alloc>
    typename Vector<T, Alloc>::Iterator Vector<T, Alloc>::insert(const Iterator& it, size_t n, const T& val)
    {
        if (n <= 0)
        {
            return it;
        }
        const int idx = it - begin_;
        auto new_begin = Alloc::allocate(capacity + n);
        for (int k = 0; k < idx; ++k)
        {
            Alloc::construct(&*(new_begin + k), *(begin_ + k));
        }
        for (int i = 0; i < n; ++i)
        {
            Alloc::construct(&*(new_begin + idx + i), val);
        }
        for (int i = idx; i < length; ++i)
        {
            Alloc::construct(&*(new_begin + idx + n - 1 + i), *(begin_ + i));
        }
        Alloc::destroy(&*begin_, length);
        Alloc::deallocate(&*begin_);
        begin_ = Iterator(new_begin);
        new_begin = nullptr;
        Iterator res = begin_ + idx;
        length += n;
        capacity += n;

        return res;
    }

    template <class T, class Alloc>
    typename Vector<T, Alloc>::Iterator Vector<T, Alloc>::erase(const Iterator& it)
    {
        --begin_ + length;
        for (auto iter = it; iter != begin_ + length; ++iter)
        {
            *iter = *(iter + 1);
        }
        --length;
        Alloc::destroy(&*begin_ + length);
        return it;
    }

    template <class T, class Alloc>
    const typename Vector<T, Alloc>::Iterator& Vector<T, Alloc>::begin()
    {
        return begin_;
    }

    template <class T, class Alloc>
    const typename Vector<T, Alloc>::Iterator& Vector<T, Alloc>::end()
    {
        return begin_ + length;
    }

    template <class T, class Alloc>
    void Vector<T, Alloc>::expand()
    {
        Iterator new_begin(Alloc::allocate(2 * capacity));
        for (int i = 0; i < length; ++i)
        {
            Alloc::construct(&*(new_begin + i), *(begin_ + i));
        }
        Alloc::destroy(&*begin_, length);
        Alloc::deallocate(&*begin_);
        begin_ = new_begin;
        capacity *= 2;
    }

    template <class T, class Alloc>
    void Vector<T, Alloc>::insertSort(const int begin, const int end)
    {
        for (int i = begin + 1;i <= end; ++i)
        {
            int val = *(begin_ + i);
            int j = i - 1;
            for (; j >= 0; --j)
            {
                if (*(begin_ + j) < val)
                {
                    break;
                }
                *(begin_ + j + 1) = *(begin_ + j);
            }
            *(begin_ + j + 1) = val;
        }
    }

    template <class T, class Alloc>
    void Vector<T, Alloc>::heapSiftDown(const int begin, const int end, const int i)
    {
        //begin，end是要调整到大根堆的部分，而i是要调整的元素
        int parent = i;
        int child = 2 * parent + 1;
        do
        {
            if (child + 1 <= end - begin && *(begin_ + begin + child + 1) > *(begin_ + begin + child))
            {
                child += 1;
            }
            if (*(begin_ + begin + parent) < *(begin_ + begin + child))
            {
                std::swap(*(begin_ + begin + parent), *(begin_ + begin + child));
                parent = child;
                child = 2 * parent + 1;
            }
            else
            {
                break;
            }
        } while (child <= end - begin);

    }

    template <class T, class Alloc>
    void Vector<T, Alloc>::heapSort(const int begin, const int end)
    {
        for (int i = (end - begin - 1) / 2; i >= 0; --i)
        {
            heapSiftDown(begin, end, i);
        }
        for (int i = end - begin; i >= 1; --i)
        {
            heapSiftDown(begin, begin + i, 0);
            std::swap(*(begin_ + begin), *(begin_ + begin + i));
        }
    }

    template <class T, class Alloc>
    void Vector<T, Alloc>::sort(const int begin, const int end, const int depth)
    {
        if (begin >= end)
        {
            return;
        }
        if (length <= 50)
        {
            insertSort(begin, end);
        }
        if (depth >= 20)
        {
            heapSort(begin, end);
        }
        int left = begin;
        int right = end;
        int val = *(begin_ + begin);
        while (left < right)
        {
            while (left < right && *(begin_ + right) >= val)
            {
                --right;
            }
            *(begin_ + left) = *(begin_ + right);
            while (left < right && *(begin_ + left) <= val)
            {
                ++left;
            }
            *(begin_ + right) = *(begin_ + left);
        }
        *(begin_ + left) = val;
        sort(begin, left - 1, depth + 1);
        sort(left + 1, end, depth + 1);
    }

    //迭代器
    template<class T, class Alloc>
    class Vector<T, Alloc>::Iterator
    {
    public:
        friend class const_Interator;
        explicit Iterator(T* ptr = nullptr) :data_ptr_(ptr) {}
        ~Iterator() = default;
        Iterator(const Iterator& it) = default;
        Iterator& operator=(const Iterator& it) = default;
        Iterator(Iterator&& it) = default;
        Iterator& operator=(Iterator&& it) = default;
        T& operator*() const
        {
            return *data_ptr_;
        }
        T* operator->() const
        {
            return data_ptr_;
        }
        bool operator==(const Iterator& it) const
        {
            return data_ptr_ == it.data_ptr_;
        }
        bool operator!=(const Iterator& it) const
        {
            return data_ptr_ != it.data_ptr_;
        }
        Iterator& operator++()
        {
            ++data_ptr_;
            return *this;
        }
        Iterator& operator--()
        {
            --data_ptr_;
            return *this;
        }
        Iterator operator+(const std::size_t a) const
        {
            return Iterator(data_ptr_ + a);
        }
        Iterator operator-(const std::size_t a) const
        {
            return Iterator(data_ptr_ - a);
        }
        int operator-(const Iterator& it) const
        {
            return data_ptr_ - it.data_ptr_;
        }


    private:
        T* data_ptr_;
    };

} // sdf

#endif //VECTOR_H
