#ifndef CLIENT_SINGLETON_HPP
#define CLIENT_SINGLETON_HPP

#include<type_traits>

template<class Type>
concept is_singleton = !std::is_copy_constructible_v<Type> &&
                       !std::is_move_constructible_v<Type> &&
                       !std::is_copy_assignable_v<Type> &&
                       !std::is_move_assignable_v<Type>;

template<is_singleton Type>
class Singleton {
public:

    Singleton(Singleton &&) = delete;

    Singleton(const Singleton &) = delete;

    static Type &GetInstance() {
        static Singleton singleton;
        return *(singleton.instance_);
    }

private:

    Singleton() { instance_ = new Type; };

    ~Singleton() { delete instance_; }

    Type *instance_ = nullptr;
};


#endif