#ifndef SHAREDPTR_H
#define SHAREDPTR_H
#include <mutex>
namespace sdf {

template<class T>
class SharedPtr {
    public:
        explicit SharedPtr(T *pointer = nullptr);
        ~SharedPtr();
        SharedPtr(const SharedPtr<T> &other);
        SharedPtr &operator=(const SharedPtr<T> &other);
        SharedPtr(SharedPtr<T> &&other) noexcept;
        SharedPtr<T> &operator=(SharedPtr<T> &&other) noexcept;
        [[nodiscard]] unsigned int useCount() const;

        T &operator*() const;
        T *operator->() const;
        T *get() const;

        operator bool() const;
        void reset(T *pointer = nullptr);
        void swap(SharedPtr<T> &other) noexcept;

        bool operator==(const SharedPtr<T> &other) const;
        bool operator==(std::nullptr_t) const;
        bool operator!=(const SharedPtr<T> &other) const;
        bool operator!=(std::nullptr_t) const;

    private:
        T *pointer_;
        unsigned int *ref_count_;
        std::mutex *mutex_;

        void addRefCount();
        void subRefCount();
};

template<class T>
SharedPtr<T>::SharedPtr(T *pointer) :
    pointer_(pointer),
    mutex_(new std::mutex())
{
    if (pointer_) {
        ref_count_ = new unsigned int(0);
    }
    else {
        ref_count_ = nullptr;
    }
    addRefCount();
}

template<class T>
SharedPtr<T>::~SharedPtr() {
    subRefCount();
}

template<class T>
SharedPtr<T>::SharedPtr(const SharedPtr &other) {
    pointer_ = other.pointer_;
    ref_count_ = other.ref_count_;
    mutex_ = other.mutex_;
    addRefCount();
}

template<class T>
SharedPtr<T> & SharedPtr<T>::operator=(const SharedPtr<T> &other) {
    if (&other == this) {
        return *this;
    }

    subRefCount();
    pointer_ = other.pointer_;
    ref_count_ = other.ref_count_;
    mutex_ = other.mutex_;
    addRefCount();

    return *this;
}

template<class T>
SharedPtr<T>::SharedPtr(SharedPtr<T> &&other) noexcept {
    pointer_ = other.pointer_;
    ref_count_ = other.ref_count_;
    mutex_ = other.mutex_;
    other.pointer_ = nullptr;
    other.ref_count_ = nullptr;
    other.mutex_ = nullptr;
}

template<class T>
SharedPtr<T> & SharedPtr<T>::operator=(SharedPtr<T> &&other) noexcept {
    subRefCount();
    pointer_ = other.pointer_;
    ref_count_ = other.ref_count_;
    mutex_ = other.mutex_;
    other.pointer_ = nullptr;
    other.ref_count_ = nullptr;
    other.mutex_ = nullptr;

    return *this;
}

template<class T>
unsigned int SharedPtr<T>::useCount() const {
    return *ref_count_;
}

template<class T>
T & SharedPtr<T>::operator*() const {
    return *pointer_;
}

template<class T>
T * SharedPtr<T>::operator->() const {
    return pointer_;
}

template<class T>
T * SharedPtr<T>::get() const {
    return pointer_;
}

template<class T>
SharedPtr<T>::operator bool() const {
    return pointer_ != nullptr;
}

template<class T>
void SharedPtr<T>::reset(T *pointer) {
    subRefCount();
    mutex_ = new std::mutex();
    pointer_ = pointer;
    if (pointer_) {
        ref_count_ = new unsigned int(0);
    }
    else {
        ref_count_ = nullptr;
    }
    addRefCount();
}

template<class T>
void SharedPtr<T>::swap(SharedPtr<T> &other) noexcept {
    if (other.pointer_ == pointer_) {
        return;
    }
    std::swap(pointer_, other.pointer_);
    std::swap(ref_count_, other.ref_count_);
    std::swap(mutex_, other.mutex_);
}

template<class T>
bool SharedPtr<T>::operator==(const SharedPtr<T> &other) const {
    return pointer_ == other.pointer_;
}

template<class T>
bool SharedPtr<T>::operator==(std::nullptr_t) const {
    return pointer_ == nullptr;
}

template<class T>
bool SharedPtr<T>::operator!=(const SharedPtr<T> &other) const {
    return pointer_ != other.pointer_;
}

template<class T>
bool SharedPtr<T>::operator!=(std::nullptr_t) const {
    return pointer_ != nullptr;
}

template<class T>
void SharedPtr<T>::addRefCount() {
    if (mutex_)
    {
        std::unique_lock<std::mutex> lock(*mutex_);
        if (ref_count_) {
            (*ref_count_)++;
        }
    }
}

template<class T>
void SharedPtr<T>::subRefCount() {
    auto flag = false;
    if (mutex_)
    {
        std::unique_lock<std::mutex> lock(*mutex_);
        if (ref_count_) {
            (*ref_count_)--;
            if (*ref_count_ == 0) {
                delete pointer_;
                delete ref_count_;
                pointer_ = nullptr;
                ref_count_ = nullptr;
                flag = true;
            }
        }
    }
    if (flag) {
        delete mutex_;
    }
}
} // sdf

#endif //SHAREDPTR_H
