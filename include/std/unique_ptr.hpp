#ifndef FILE_UNIQUE_PTR_HPP
#define FILE_UNIQUE_PTR_HPP

#include "std/smart_ptr.hpp"

template<typename T>
class unique_ptr : public smart_ptr<T> {
public:
    unique_ptr() : smart_ptr<T>(nullptr) {}
    unique_ptr(T* t) : smart_ptr<T>(t) {}
    ~unique_ptr() {
        if (this->t)
            delete this->t;
    }
    // copy constructor, should not kill the other value
    unique_ptr(const unique_ptr<T>& other) = delete;
    // copy assignment operator, should not kill the other value
    unique_ptr<T>& operator=(const unique_ptr<T>& other) = delete;
    // move constructor, should kill the other value
    unique_ptr(unique_ptr<T>&& other) {
        this->t = other.t;
        other.t = nullptr;
    }
    // move assignment operator, should kill the other value
    unique_ptr<T>& operator=(unique_ptr<T>&& other) {
        if (this != &other) {
            if (this->t)
                delete this->t;
            this->t = other.t;
            other.t = nullptr;
        }
        return *this;
    }
};

#endif // FILE_UNIQUE_PTR_HPP