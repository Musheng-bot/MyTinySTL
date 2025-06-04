//
// Created by meish on 25-5-27.
//

#ifndef SET_H
#define SET_H

#include "../DataStructures/RedBlackTree.h"
namespace sdf {

template<class T>
class Set {
    public:
        Set() = default;
        ~Set() = default;

        void insert(const T &value);
        void remove(const T &value);
        [[nodiscard]] auto find(const T &value) const;
        [[nodiscard]] auto empty() const;
        [[nodiscard]] unsigned size() const;
        [[nodiscard]] auto begin() const;
        [[nodiscard]] auto end() const;




    private:
        RedBlackTree<T> tree;
};

template<class T>
void Set<T>::insert(const T &value) {
    tree.insert(value);
}

template<class T>
void Set<T>::remove(const T &value) {
    tree.remove(value);
}

template<class T>
auto Set<T>::find(const T &value) const {
    return tree.find(value);
}

template<class T>
auto Set<T>::empty() const {
    return tree.empty();
}

template<class T>
unsigned Set<T>::size() const {
    return tree.size();
}

template<class T>
auto Set<T>::begin() const {
    return tree.begin();
}

template<class T>
auto Set<T>::end() const {
    return tree.end();
}
} // sdf

#endif //SET_H
