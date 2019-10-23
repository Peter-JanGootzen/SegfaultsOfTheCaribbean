#ifndef FILE_UNIQUE_ARRAY_HPP
#define FILE_UNIQUE_ARRAY_HPP

#include "std/smart_ptr.hpp"

template<typename T>
class unique_array : public smart_ptr<T> {
public:
    unique_array() : smart_ptr<T>(nullptr) {}
    unique_array(T* t) : smart_ptr<T>(t) {}
    ~unique_array() {
        if (this->t)
            delete[] this->t;
    }
    // copy constructor, should not kill the other value
    unique_array(const unique_array<T>& other) = delete;
    // copy assignment operator, should not kill the other value
    unique_array<T>& operator=(const unique_array<T>& other) = delete;
    // move constructor, should kill the other value
    unique_array(unique_array<T>&& other) {
        this->t = other.t;
        other.t = nullptr;
    }
    // move assignment operator, should kill the other value
    unique_array<T>& operator=(unique_array<T>&& other) {
        if (this != &other) {
            if (this->t)
                delete[] this->t;
            this->t = other.t;
            other.t = nullptr;
        }
        return *this;
    }
};

#endif // FILE_UNIQUE_ARRAY_HPP