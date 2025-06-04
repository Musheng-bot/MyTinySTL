#ifndef PAIR_H
#define PAIR_H

namespace sdf {

template <class KeyType, class ValueType>
class Pair {
    public:
        explicit Pair(const KeyType &key = KeyType(), const ValueType &value = KeyType()) : key_(key), value_(value) {}
        ~Pair() {}

        KeyType &first() { return key_; }
        ValueType &second() { return value_; }

        bool operator==(const Pair<KeyType, ValueType> &other) const {
            return key_ == other.key_;
        }
        bool operator<(const Pair<KeyType, ValueType> &other) const {
            return key_ < other.key_;
        }
        bool operator>(const Pair<KeyType, ValueType> &other) const {
            return key_ > other.key_;
        }
        bool operator<=(const Pair<KeyType, ValueType> &other) const {
            return key_ <= other.key_;
        }
        bool operator>=(const Pair<KeyType, ValueType> &other) const {
            return key_ >= other.key_;
        }
        bool operator!=(const Pair<KeyType, ValueType> &other) const {
            return key_ != other.key_;
        }

    private:
        KeyType key_;
        ValueType value_;
};

} // sdf

#endif //PAIR_H
