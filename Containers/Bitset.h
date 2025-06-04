//
// Created by meish on 25-5-27.
//

#ifndef BITSET_H
#define BITSET_H
#include <functional>
#include <vector>

namespace sdf
{
    template<class T = int>
    class Bitset
    {
        public:
            using cmp = std::function<int(T)>;

            explicit Bitset(cmp Cmp = [](T x) { return x; }) : cmp_(std::move(Cmp))
            {
                set_.resize(100);
            }
            ~Bitset() = default;

            void insert(T val)
            {
                int x = cmp_(val);
                int offset = x / unit_size;
                int pos = x % unit_size;
                set_[offset] |= 1 << pos;
            }

            bool remove(T val)
            {
                int x = cmp_(val);
                int offset = x / unit_size;
                int pos = x % unit_size;
                if (set_[offset] & (1 << pos) == 0)
                {
                    return false;
                }
                set_[offset] &= ~(1 << pos);
                return true;
            }

            bool find(T val) const
            {
                int x = cmp_(val);
                int offset = x / unit_size;
                int pos = x % unit_size;

                return (set_[offset] & (1 << pos)) != 0;

            }


        private:
            std::vector<int> set_;
            cmp cmp_;
            const int unit_size = sizeof(int) * 8;
    };


}


#endif //BITSET_H
