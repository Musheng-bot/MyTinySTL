//
// Created by meish on 25-5-27.
//

#ifndef FORWARDLIST_H
#define FORWARDLIST_H

#include <memory>
namespace sdf
{
    template<class T>
    class ForwardList
    {
        public:
            struct ForwardListNode
            {
                T data_{};
                std::unique_ptr<ForwardListNode> next;
                ForwardListNode() :next(nullptr) {}
                explicit ForwardListNode(const T& data) :data_(data), next(nullptr) {}
            };
            ForwardList() = default;
            ~ForwardList() = default;

            void push_front(const T& data)
            {
                std::unique_ptr<ForwardListNode> new_node = std::make_unique<ForwardListNode>(data);
                new_node->next = std::move(head_->next);
                head_->next = std::move(new_node);
                ++length_;
            }

            void pop_front()
            {
                if (head_ == nullptr)
                {
                    return;
                }
                head_->next = std::move(head_->next->next);
                --length_;
            }

            void clear()
            {
                head_->next = nullptr;
                length_ = 0;
            }

            [[nodiscard]] std::size_t size() const
            {
                return length_;
            }

            [[nodiscard]] bool find(const T& data) const
            {
                const ForwardListNode* p = head_.get();
                while (p != nullptr)
                {
                    if (p->data_ == data)
                    {
                        return true;
                    }
                    p = p->next.get();
                }
                return false;
            }

            class Iterator {
                public:
                    explicit Iterator(ForwardListNode *p);
                    ~Iterator() = default;
                    T *operator->();
                    T &operator*();
                    Iterator& operator++();
                    bool operator==(const Iterator& other);
                    bool operator!=(const Iterator& other);

                private:
                    ForwardListNode *val_;
            };

            Iterator begin() const;
            Iterator end() const;

        private:
            std::unique_ptr<ForwardListNode> head_ = std::make_unique<ForwardListNode>();
            size_t length_ = 0;
    };


    template<class T>
    ForwardList<T>::Iterator::Iterator(ForwardListNode *p) {
        val_ = p;
    }

    template<class T>
    T * ForwardList<T>::Iterator::operator->() {
        return &val_->data_;
    }

    template<class T>
    T & ForwardList<T>::Iterator::operator*() {
        return val_->data_;
    }

    template<class T>
    typename ForwardList<T>::Iterator & ForwardList<T>::Iterator::operator++() {
        val_ = val_->next.get();
        return *this;
    }

    template<class T>
    bool ForwardList<T>::Iterator::operator==(const Iterator &other) {
        return val_ == other.val_;
    }

    template<class T>
    bool ForwardList<T>::Iterator::operator!=(const Iterator &other) {
        return val_ != other.val_;
    }

    template<class T>
    typename ForwardList<T>::Iterator ForwardList<T>::begin() const {
        return Iterator(head_.get());
    }

    template<class T>
    typename ForwardList<T>::Iterator ForwardList<T>::end() const {
        return Iterator(nullptr);
    }
}

#endif //FORWARDLIST_H
