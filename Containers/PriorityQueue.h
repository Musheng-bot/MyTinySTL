#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <functional>
#include <stdexcept>
namespace sdf
{
    template<class T>
    class PriorityQueue
    {
    public:
        using Cmp = std::function<bool(T, T)>;

    private:
        T* head;
        unsigned long long size_;
        unsigned long long capacity_;
        Cmp cmp;

        void expand();
        void siftUp(const T& val);
        void siftDown();
    public:
        PriorityQueue();
        PriorityQueue(const int& size_, Cmp cmp_);
        ~PriorityQueue();
        void push(const T& val);
        void pop();
        T top();
        [[nodiscard]] unsigned long long size() const;
        [[nodiscard]] bool empty() const;

        class Iterator {
            public:
                explicit Iterator(T *p);
                ~Iterator();
                Iterator& operator++();
                Iterator& operator--();
                T& operator*() const;
                T* operator->() const;
                bool operator==(const Iterator& other) const;
                bool operator!=(const Iterator& other) const;

            private:
                T *value_;
        };

        Iterator begin() const;
        Iterator end() const;
    };

    template <class T>
    void PriorityQueue<T>::expand()
    {
        auto temp = new T[2 * capacity_];
        memcpy(temp, head, sizeof(T) * size_);
        head = temp;
        capacity_ *= 2;
    }

    template <class T>
    void PriorityQueue<T>::siftUp(const T& val)
    {
        unsigned i = size_;
        while (i > 0)
        {
            unsigned father = (i - 1) / 2;
            if (cmp(val, head[father]))
            {
                head[i] = head[father];
                i = father;
            }
            else
            {
                break;
            }
        }
        head[i] = val;
    }

    template <class T>
    void PriorityQueue<T>::siftDown()
    {
        T val = head[size_];
        unsigned i = 0;
        while (i <= (size_ - 2) / 2)
        {
            unsigned child = 2 * i + 1;
            if (child + 1 < size_ && cmp(head[child + 1], head[child]))
            {
                child += 1;
            }
            if (cmp(head[child], val))
            {
                head[i] = head[child];
                i = child;
            }
            else
            {
                break;
            }
        }
        head[i] = val;
    }

    template <class T>
    PriorityQueue<T>::PriorityQueue() :size_(0), capacity_(10), cmp(std::greater<T>())
    {
        head = new T[capacity_];
    }

    template <class T>
    PriorityQueue<T>::PriorityQueue(const int& size_in, Cmp cmp_) :size_(0), capacity_(size_in), cmp(cmp_)
    {
        head = new T[capacity_];
    }

    template <class T>
    PriorityQueue<T>::~PriorityQueue()
    {
        delete[] head;
        head = nullptr;
    }

    template <class T>
    void PriorityQueue<T>::push(const T& val)
    {
        if (empty())
        {
            head[size_] = val;
        }
        else
        {
            siftUp(val);
        }
        ++size_;
    }

    template <class T>
    void PriorityQueue<T>::pop()
    {
        if (size_ == 0)
            throw std::runtime_error("The quene is empty!");
        --size_;
        if (size_ > 0)
        {
            siftDown();
        }

    }

    template <class T>
    T PriorityQueue<T>::top()
    {
        if (size_ == 0)
            throw std::runtime_error("The quene is empty!");
        return head[0];
    }

    template <class T>
    unsigned long long PriorityQueue<T>::size() const
    {
        return size_;
    }

    template <class T>
    bool PriorityQueue<T>::empty() const
    {
        return size_ == 0;
    }

    template<class T>
    PriorityQueue<T>::Iterator::Iterator(T *p) {
        value_ = p;
    }

    template<class T>
    PriorityQueue<T>::Iterator::~Iterator() = default;

    template<class T>
    typename PriorityQueue<T>::Iterator & PriorityQueue<T>::Iterator::operator++() {
        ++value_;
        return *this;
    }

    template<class T>
    typename PriorityQueue<T>::Iterator & PriorityQueue<T>::Iterator::operator--() {
        --value_;
        return *this;
    }

    template<class T>
    T & PriorityQueue<T>::Iterator::operator*() const {
        return *value_;
    }

    template<class T>
    T * PriorityQueue<T>::Iterator::operator->() const {
        return value_;
    }

    template<class T>
    bool PriorityQueue<T>::Iterator::operator==(const Iterator &other) const {
        return value_ == other.value_;
    }

    template<class T>
    bool PriorityQueue<T>::Iterator::operator!=(const Iterator &other) const {
        return value_ != other.value_;
    }

    template<class T>
    typename PriorityQueue<T>::Iterator PriorityQueue<T>::begin() const {
        return PriorityQueue<T>::Iterator(head);
    }

    template<class T>
    typename PriorityQueue<T>::Iterator PriorityQueue<T>::end() const {
        return PriorityQueue<T>::Iterator(head + size_);
    }
}

#endif // PRIORITYQUEUE_H
