#ifndef WEAKPTR_H
#define WEAKPTR_H
#include "SharedPtr.h"

namespace sdf {
    template<class T>
    class WeakPtr {
        public:
            explicit WeakPtr(const SharedPtr<T> &sp);
            WeakPtr() = delete;
            ~WeakPtr();
            WeakPtr(const WeakPtr& other);
            WeakPtr& operator=(const WeakPtr& other);
            WeakPtr& operator=(WeakPtr&& other) noexcept;
            WeakPtr(WeakPtr&& other) noexcept;

            SharedPtr<T> lock() const;
            void reset(const SharedPtr<T> &sp = nullptr);

        private:
            const SharedPtr<T> *sp_;
            unsigned int *weak_count_;
            std::mutex *mutex_;

            void addWeakCount();
            void subWeakCount();
    };

    template<class T>
    WeakPtr<T>::WeakPtr(const SharedPtr<T> &sp) {
        sp_ = &sp;
        if (sp != nullptr) {
            weak_count_ = new unsigned int(1);
        }
        mutex_ = new std::mutex();
    }

    template<class T>
    WeakPtr<T>::~WeakPtr() {
        subWeakCount();
    }

    template<class T>
    WeakPtr<T>::WeakPtr(const WeakPtr &other) {
        sp_ = other.sp_;
        weak_count_ = other.weak_count_;
        mutex_ = other.mutex_;
        addWeakCount();
    }

    template<class T>
    WeakPtr<T> & WeakPtr<T>::operator=(const WeakPtr &other) {
        if (this == &other) {
            return *this;
        }
        subWeakCount();
        sp_ = other.sp_;
        weak_count_ = other.weak_count_;
        mutex_ = other.mutex_;
        addWeakCount();
        return *this;
    }

    template<class T>
    WeakPtr<T> & WeakPtr<T>::operator=(WeakPtr &&other) noexcept {
        subWeakCount();
        sp_ = other.sp_;
        weak_count_ = other.weak_count_;
        mutex_ = other.mutex_;
        other.weak_count_ = nullptr;
        other.mutex_ = nullptr;
        addWeakCount();
        return *this;
    }

    template<class T>
    WeakPtr<T>::WeakPtr(WeakPtr &&other) noexcept {
        sp_ = other.sp_;
        weak_count_ = other.weak_count_;
        mutex_ = other.mutex_;
        addWeakCount();
    }

    template<class T>
    SharedPtr<T> WeakPtr<T>::lock() const {
        return SharedPtr<T>(*sp_);
    }

    template<class T>
    void WeakPtr<T>::reset(const SharedPtr<T> &sp) {
        subWeakCount();
        *this = WeakPtr<T>(sp);
    }

    template<class T>
    void WeakPtr<T>::addWeakCount() {
        if (mutex_)
        {
            std::unique_lock<std::mutex> lock(*mutex_);
            if (weak_count_) {
                ++(*weak_count_);
            }
        }
    }

    template<class T>
    void WeakPtr<T>::subWeakCount() {
        bool flag = false;
        if (mutex_)
        {
            std::unique_lock<std::mutex> lock(*mutex_);
            if (weak_count_) {
                --(*weak_count_);
                if (*weak_count_ == 0) {
                    sp_ = nullptr;
                    delete weak_count_;
                    weak_count_ = nullptr;
                    flag = true;
                }
            }
        }
        if (flag) {
            delete mutex_;
        }
    }
}

#endif //WEAKPTR_H
