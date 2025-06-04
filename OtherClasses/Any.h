#ifndef ANY_H
#define ANY_H

#include <memory>
#include <stdexcept>

namespace sdf
{
    class Any
    {
        public:
            Any() :data_(std::make_unique<Base>()) {}

            template<class T>
            Any(T&& val) : data_(std::make_unique<Derived<T>>(std::forward<T>(val))) {}

            template<class T>
            T& get()
            {
                auto data = dynamic_cast<Derived<T>*>(data_.get());
                if (data == nullptr)
                {
                    throw std::runtime_error("Error! The dynamic_cast failed!");
                }
                return data->get();
            }


        private:
            class Base
            {
                public:
                    Base() = default;
                    virtual ~Base() = default;
            };

            template<class T>
            class Derived final : public Base
            {
                public:
                    Derived() = default;
                    Derived(T&& val) : val_(std::forward<T>(val)) {}
                    ~Derived() override = default;
                    T& get()
                    {
                        return val_;
                    }
                private:
                    T val_;
            };

            std::unique_ptr<Base> data_;
    };
}



#endif //ANY_H
