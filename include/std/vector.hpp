#ifndef FILE_VECTOR_HPP
#define FILE_VECTOR_HPP
#include <stdexcept>
template<class T>
class Vector {
public:
    Vector(T* buffer, unsigned int n) : n(n), buffer(buffer) {};
    ~Vector() {
        for (int i = 0; i < n; i++) {
            buffer[i].~T();
        }
    }
    T& operator[](unsigned int i) const {
        if (i > n) throw std::out_of_range("Please supply a valid range");
        return buffer[i];
    }
    // todo rule of five
private:
    T* buffer;
    unsigned int n;
};
#endif