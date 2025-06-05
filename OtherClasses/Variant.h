//
// Created by meish on 25-5-27.
//

#ifndef VARIANT_H
#define VARIANT_H

#include <iostream>

namespace sdf {

template<class ... Args>
class Variant {
    public:
        explicit Variant(Args ... args) {}
        ~Variant() {}
        void show() const {
            std::cout << args << std::endl;
        }

    private:
        Args args...;
};

} // sdf

#endif //VARIANT_H
