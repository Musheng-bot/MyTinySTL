//
// Created by meish on 25-5-24.
//

#ifndef ATOMIC_H
#define ATOMIC_H
#include <mutex>

template<class T>
class Atomic {
    public:
        Atomic(const T &val);
        ~Atomic();
        Atomic(const Atomic<T> &other);
        Atomic& operator=(const Atomic<T> &other);
        Atomic& operator=(const T &val);
        Atomic(Atomic &&other) noexcept ;
        Atomic& operator=(Atomic<T> &&other) noexcept;

        operator T() const;
        operator bool() const;

        void store(const T &val);
        const T& load() const;
        T &load();

        T operator++();
        T &operator++(int);
        T operator--();
        T &operator--(int);

        T operator+(const T &other) const;
        T operator-(const T &other) const;
        T operator*(const T &other) const;
        T operator/(const T &other) const;
        T operator%(const T &other) const;
        T operator&(const T &other) const;
        T operator|(const T &other) const;
        T operator^(const T &other) const;
        T operator~() const;
        bool operator==(const T &other) const;
        bool operator!=(const T &other) const;
        bool operator<(const T &other) const;
        bool operator>(const T &other) const;

    private:
        T value_;
        std::mutex mutex_;
};



#endif //ATOMIC_H
