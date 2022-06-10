#ifndef SINGLETON_H
#define SINGLETON_H

#include "platform.h"

template <class T>
class singleton {
    singleton(const singleton<T> &) = delete;
    singleton(singleton<T> &&) = delete;
    singleton<T> &operator=(const singleton<T> &) = delete;
    singleton<T> &operator=(singleton<T> &&) = delete;

protected:
    virtual ~singleton() {}
    singleton() = default;

public:

    template<class... Args>
    static T &instance(Args... arguments) {
        static T single(arguments...);
        return single;
    }
    static std::shared_ptr<T> instancePtr() {
        static std::shared_ptr<T> single(new T());
        return single;
    }
};

#define SINGLETON_IMPL(classname) \
    public: friend class singleton<classname>;  \
    private:                                    \
    classname(const classname &);               \
    classname(classname &&);                    \
    classname& operator=(const classname &);    \
    classname& operator=(classname &&)

#endif // SINGLETON_H
