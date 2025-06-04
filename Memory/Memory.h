//
// Created by meish on 25-5-24.
//

#ifndef MEMORY_H
#define MEMORY_H

#include "SharedPtr.h"
#include "UniquePtr.h"
#include "WeakPtr.h"

namespace sdf {

    template<class T, class... Args>
    UniquePtr<T> makeUnique(Args ...args) {
        return UniquePtr<T>(new T(args...));
    }

    template<class T,class ... Args>
    SharedPtr<T> makeShared(Args ...args) {
        return SharedPtr<T>(new T(args...));
    }
}

#endif //MEMORY_H
