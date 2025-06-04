#ifndef LIST_H
#define LIST_H

#include <cstddef>
#include <iostream>

namespace sdf
{
    template <class T>
    struct ListNode
    {
        T data;
        ListNode* prev;
        ListNode* next;
        explicit ListNode(const T& data_) : data(data_), prev(nullptr), next(nullptr) {}
        ListNode() : prev(nullptr), next(nullptr) {}
    };

    template<class T>
    class List
    {
    private:
        ListNode<T>* head;
        std::size_t length{};
    public:
        List();
        List(const List<T>& list);
        ~List();
        void push_front(const T& data_);
        void push_back(const T& data_);
        void pop_front();
        void pop_back();
        void clear();
        bool find(const T& data_);
        void show() const;
        [[nodiscard]] bool empty() const;
        [[nodiscard]] std::size_t size() const;
        void reverse();
        void merge(List& list);
        List& operator= (const List<T>& list);
        void erase(const T& data_);
        void eraseAll(const T& data_);

        class Iterator {
            public:
                explicit Iterator(ListNode<T> *p);
                ~Iterator();
                Iterator& operator++();
                Iterator& operator--();
                T& operator*() const;
                T* operator->() const;
                bool operator==(const Iterator& rhs) const;
                bool operator!=(const Iterator& rhs) const;

            private:
                ListNode<T> *val_;
        };

        Iterator begin() const;
        Iterator end() const;
    };

    template<class T>
    List<T>::List() {
        head = new ListNode<T>();
        head->prev = head;
        head->next = head;
        length = 0;
    }

    template <class T>
    List<T>::List(const List<T>& list)
    {
        head = new ListNode<T>();
        head->prev = head;
        head->next = head;
        auto ptr = list.head->next;
        while (ptr != list.head) {
            push_back(ptr->data);
            ptr = ptr->next;
        }
        length = list.length;
    }

    template<class T>
    List<T>::~List() {
        auto p = head->next;
        while (p != head) {
            p->next->prev = head;
            head->next = p->next;
            delete p;
            p = head->next;
        }
        delete head;
        head = nullptr;
        length = 0;
    }

    template<class T>
    void List<T>::push_front(const T& data_) {
        auto ptr = new ListNode<T>(data_);
        ptr->next = head->next;
        ptr->prev = head;
        head->next->prev = ptr;
        head->next = ptr;
        ++length;
    }

    template<class T>
    void List<T>::show() const {
        auto ptr = head->next;
        while (ptr != head) {
            std::cout << ptr->data << " ";
            ptr = ptr->next;
        }
        std::cout << std::endl;
    }

    template<class T>
    void List<T>::push_back(const T& data_) {
        auto* p = new ListNode<T>(data_);
        p->prev = head->prev;
        p->next = head;
        head->prev->next = p;
        head->prev = p;
        ++length;
    }

    template<class T>
    void List<T>::clear() {
        auto p = head->next;
        while (p != head) {
            p->next->prev = head;
            head->next = p->next;
            delete p;
            p = head->next;
        }
        head->next = head;
        head->prev = head;
        length = 0;
    }

    template<class T>
    void List<T>::pop_front() {
        if (head->next == head)
            return;
        head->next = head->next->next;
        delete head->next->prev;
        head->next->prev = head;
        --length;
    }

    template<class T>
    void List<T>::pop_back() {
        if (head->prev == head)
            return;
        head->prev = head->prev->prev;
        delete head->prev->next;
        head->prev->next = head;
        --length;
    }

    template<class T>
    bool List<T>::find(const T& data_) {
        auto p = head->next;
        while (p != head) {
            if (p->data == data_)
                return true;
        }
        return false;
    }

    template<class T>
    bool List<T>::empty() const {
        return length == 0;
    }

    template<class T>
    std::size_t List<T>::size() const {
        return length;
    }

    template<class T>
    void List<T>::reverse() {
        auto p = head->next;
        while (p != head) {
            std::swap(p->prev, p->next);
            p = p->prev;
        }
        std::swap(head->prev, head->next);
    }

    template <class T>
    void List<T>::merge(List<T>& list)
    {
        if (list.empty())
            return;
        auto p = list.head->next;
        while (p != list.head) {
            this->push_back(p->data);
            p = p->next;
        }
    }

    template <class T>
    List<T>& List<T>::operator=(const List<T>& list)
    {
        if (&list == this)
            return *this;
        clear();
        auto ptr = list.head->next;
        while (ptr != list.head) {
            push_back(ptr->data);
            ptr = ptr->next;
        }
        return *this;
    }

    template <class T>
    void List<T>::erase(const T& data_)
    {
        auto p = head->next;
        while (p != head)
        {
            if (p->data == data_)
            {
                p->next->prev = p->prev;
                p->prev->next = p->next;
                delete p;
                return;
            }
        }
    }

    template <class T>
    void List<T>::eraseAll(const T& data_)
    {
        auto p = head->next;
        while (p != head)
        {
            if (p->data == data_)
            {
                auto temp = p->next;
                p->next->prev = p->prev;
                p->prev->next = p->next;
                delete p;
                p = temp;
            }
        }
    }

    template<class T>
    List<T>::Iterator::Iterator(ListNode<T> *p):val_(p) {
    }

    template<class T>
    List<T>::Iterator::~Iterator() = default;

    template<class T>
    typename List<T>::Iterator & List<T>::Iterator::operator++() {
        this->val_ = val_->next;
        return *this;
    }

    template<class T>
    typename List<T>::Iterator & List<T>::Iterator::operator--() {
        this->val_ = val_->prev;
        return *this;
    }

    template<class T>
    T & List<T>::Iterator::operator*() const {
        return this->val_->data;
    }

    template<class T>
    T * List<T>::Iterator::operator->() const {
        return &(this->val_->data);
    }

    template<class T>
    bool List<T>::Iterator::operator==(const Iterator &rhs) const {
        return val_ == rhs.val_;
    }

    template<class T>
    bool List<T>::Iterator::operator!=(const Iterator &rhs) const {
        return val_ != rhs.val_;
    }

    template<class T>
    typename List<T>::Iterator List<T>::begin() const {
        return Iterator(head->next);
    }

    template<class T>
    typename List<T>::Iterator List<T>::end() const {
        return Iterator(head);
    }
}


#endif //LIST_H
