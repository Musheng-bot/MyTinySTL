//
// Created by meish on 25-5-27.
//

#ifndef UNORDEREDSET_H
#define UNORDEREDSET_H
#include "../DataStructures/HashTable.h"

namespace sdf {

    template<class Key>
    class UnorderedSet {
        public:
            UnorderedSet() = default;
            ~UnorderedSet() = default;
            void insert(const Key& key) {
                table.insert(key);
            }
            void remove(const Key& key) {
                table.remove(key);
            }
            bool find(const Key& key) const {
                return table.find(key);
            }

        private:
            HashTable<Key> table;
    };

} // sdf

#endif //UNORDEREDSET_H
