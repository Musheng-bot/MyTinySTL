#ifndef ALGORITHM_H
#define ALGORITHM_H
#include <utility>

namespace sdf {
    template<class T>
    void swap(T &a,T &b) noexcept {
        T temp = std::move(a);
        a = std::move(b);
        b = std::move(temp);
    }

    template<class T, class V>
    T find(T begin, T end, V &&value) {
        for (auto it = begin; it != end; ++it) {
            if (*it == value) {
                return it;
            }
        }
        return end;
    }
}

#endif //ALGORITHM_H
