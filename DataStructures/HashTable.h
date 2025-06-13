//
// Created by meish on 25-5-29.
//

#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <functional>
#include <iostream>
#include <list>

namespace sdf {

    template<class Key>
    class HashTable {
        public:
            using HashFunc = std::function<size_t(const Key&)>;
            explicit HashTable(HashFunc hashFunc = std::hash<Key>()) :
                buckets_(2),
                hash_func_(hashFunc)
            {
            }
            ~HashTable() = default;
            bool insert(const Key& key);
            bool remove(const Key& key);
            void clear();
            [[nodiscard]] bool find(const Key& key) const;

        private:
            std::vector<std::list<Key>> buckets_;
            HashFunc hash_func_;

            size_t use_bucket_count_ = 0;
            double load_factor = 0.75;
            int prime_idx_ = 0;
            static int primes_[];

            void expandBucket();
    };

    template<class Key>
    bool HashTable<Key>::insert(const Key &key) {
        const size_t idx = hash_func_(key) % primes_[prime_idx_];
        if (buckets_[idx].empty()) {
            buckets_[idx].push_back(key);
            ++use_bucket_count_;
            if (static_cast<double>(use_bucket_count_) / static_cast<double>(primes_[prime_idx_]) >= load_factor) {
                expandBucket();
            }
        }
        else {
            buckets_[idx].push_back(key);
        }

        return true;
    }

    template<class Key>
    bool HashTable<Key>::remove(const Key &key) {
        const size_t idx = hash_func_(key) % primes_[prime_idx_];
        auto it = buckets_[idx].begin();
        while (it != buckets_[idx].end()) {
            if (*it == key) {
                break;
            }
            ++it;
        }
        if (it == buckets_[idx].end()) {
            return false;
        }
        buckets_[idx].erase(it);
        if (buckets_[idx].empty()) {
            --use_bucket_count_;
        }
        return true;
    }

    template<class Key>
    void HashTable<Key>::clear() {
        this->use_bucket_count_ = 0;
        this->buckets_.clear();
    }

    template<class Key>
    bool HashTable<Key>::find(const Key &key) const {
        const size_t idx = hash_func_(key) % primes_[prime_idx_];
        auto it = buckets_[idx].begin();
        while (it != buckets_[idx].end()) {
            if (*it == key) {
                return true;
            }
            ++it;
        }
        return false;
    }

    template<class Key>
    void HashTable<Key>::expandBucket() {
        if (prime_idx_ < std::size(primes_) - 1) {
            ++prime_idx_;
        }
        auto new_buckets = std::vector<std::list<Key>>(primes_[prime_idx_], std::list<Key>());
        use_bucket_count_ = 0;
        for (auto &l : this->buckets_) {
            for (auto &k : l) {
                const size_t idx = hash_func_(k) % primes_[prime_idx_];
                if (new_buckets[idx].empty()) {
                    ++use_bucket_count_;
                }
                new_buckets[idx].push_back(k);
            }
        }
        this->buckets_ = std::move(new_buckets);
    }

    template<class Key>
    int HashTable<Key>::primes_[] = {2, 3, 11, 23, 37, 53, 97, 193, 389, 769};

} // sdf

#endif //HASHTABLE_H
