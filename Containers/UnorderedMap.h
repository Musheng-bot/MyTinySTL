//
// Created by meish on 25-5-27.
//

#ifndef UNORDEREDMAP_H
#define UNORDEREDMAP_H

#include <bits/locale_facets_nonio.h>

#include "Pair.h"
#include "../DataStructures/HashTable.h"
namespace sdf {

    template<class Key, class Value>
    class UnorderedMap {
        public:
            UnorderedMap() = default;
            ~UnorderedMap() = default;

            void insert(const Key& key, const Value& value) {
                hash_table_.insert(Pair<Key, Value>{key, value});
            }
            void remove(const Key& key) {
                hash_table_.remove(Pair<Key, Value>{key, Value()});
            }
            bool find(const Key& key) const {
                return hash_table_.find(Pair<Key, Value>{key, Value()});
            }


        private:
            HashTable<Pair<Key, Value>> hash_table_ = HashTable<Pair<Key, Value>>(
                [](const Pair<Key, Value>& pair) -> size_t{
                    std::function<size_t(Key)> func = std::hash<Key>();
                    auto &key = pair.first();
                    return func(key);
                }
            );
    };

} // sdf

#endif //UNORDEREDMAP_H
