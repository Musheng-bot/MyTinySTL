#ifndef UNIQUEPTR_H
#define UNIQUEPTR_H

#include "../Algorithms/Algorithm.h"

namespace sdf {

//UniquePtr本身只允许一个对象去管理资源，故而不需要互斥锁
template<class T>
class UniquePtr {
    public:
        explicit UniquePtr(T *ptr = nullptr);
        ~UniquePtr();
        UniquePtr(const UniquePtr<T> &) = delete;
        UniquePtr &operator=(const UniquePtr<T> &) = delete;
        UniquePtr &operator=(UniquePtr<T> &&) noexcept;
        UniquePtr(UniquePtr &&) noexcept;

        T *get() const;
        T &operator*() const;
        T *operator->() const;
        void swap(UniquePtr<T> &) noexcept;
        void reset(T *ptr = nullptr);

        bool operator==(std::nullptr_t) const;
        bool operator!=(std::nullptr_t) const;

    private:
        T *ptr_;
};

template<class T>
UniquePtr<T>::UniquePtr(T *ptr):
    ptr_(ptr)
{
}

template<class T>
UniquePtr<T>::~UniquePtr() {
    delete ptr_;
}

template<class T>
UniquePtr<T> & UniquePtr<T>::operator=(UniquePtr<T> &&ptr) noexcept {
    delete ptr_;
    ptr_ = ptr.ptr_;
    ptr.ptr_ = nullptr;
    return *this;
}

template<class T>
UniquePtr<T>::UniquePtr(UniquePtr<T> &&ptr) noexcept {
    ptr_ = ptr.ptr_;
    ptr.ptr_ = nullptr;
}

template<class T>
T *UniquePtr<T>::get() const {
    return ptr_;
}

template<class T>
T & UniquePtr<T>::operator*() const {
    return *ptr_;
}

template<class T>
T * UniquePtr<T>::operator->() const {
    return ptr_;
}

template<class T>
void UniquePtr<T>::swap(UniquePtr<T> &other) noexcept {
    sdf::swap(ptr_, other.ptr_);
}

template<class T>
void UniquePtr<T>::reset(T *ptr) {
    delete ptr_;
    ptr_ = ptr;
}

template<class T>
bool UniquePtr<T>::operator==(std::nullptr_t) const {
    return ptr_ == nullptr;
}

template<class T>
bool UniquePtr<T>::operator!=(std::nullptr_t) const {
    return ptr_ != nullptr;
}
}
#endif //UNIQUEPTR_H
