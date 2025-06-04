//
// Created by meish on 25-5-27.
//

#ifndef MAP_H
#define MAP_H
#include "Pair.h"
#include "../DataStructures/RedBlackTree.h"

namespace sdf {

template <class K, class V>
class Map {
    public:
        Map() = default;
        ~Map() = default;

        void insert(const K& key, const V& value = V());
        void remove(const K& key);
        auto find(const K& key) const;
        unsigned size() const;
        bool empty() const;

        auto begin() const;
        auto end() const;

    private:
        RedBlackTree<Pair<K,V>> map_;
};

template<class K, class V>
void Map<K, V>::insert(const K &key, const V &value) {
    Pair<K,V> pair = Pair<K,V>(key, value);
    map_.insert(pair);
}

template<class K, class V>
void Map<K, V>::remove(const K &key) {
    map_.remove(Pair<K,V>(key, V()));
}

template<class K, class V>
auto Map<K, V>::find(const K &key) const {
    return map_.find(Pair<K,V>(key, V()));
}

template<class K, class V>
unsigned Map<K, V>::size() const {
    return map_.size();
}

template<class K, class V>
bool Map<K, V>::empty() const {
    return map_.empty();
}

template<class K, class V>
auto Map<K, V>::begin() const {
    return map_.begin();
}

template<class K, class V>
auto Map<K, V>::end() const {
    return map_.end();
}
} // sdf

#endif //MAP_H
