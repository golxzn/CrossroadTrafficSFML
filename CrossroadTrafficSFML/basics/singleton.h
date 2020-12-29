#ifndef SINGLETON_H
#define SINGLETON_H

template <class T>
class singleton {
    singleton(const singleton<T> &) = delete;
    singleton(singleton<T> &&) = delete;
    singleton<T> &operator=(const singleton<T> &) = delete;
    singleton<T> &operator=(singleton<T> &&) = delete;

public:
    singleton() = default;

    T &instance() {
        static T single;
        return single;
    }
    T *instancePtr() {
        static T *single = new T();
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
