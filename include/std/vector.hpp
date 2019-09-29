#ifndef FILE_VECTOR_HPP
#define FILE_VECTOR_HPP
#include <stdexcept>
#include <cstring>
template<class T>
class Vector {
public:
    Vector(T* buffer, size_t n) : used(n), capacity(n) {
        this->buffer = new T[n];
        std::copy_n(buffer, n, this->buffer);
    };
    Vector(size_t n) : used(0), capacity(n) {
        buffer = new T[n];
    };
    ~Vector() {
        delete[] buffer;
    }
    T& operator[](size_t i) const {
        if (i > used) throw std::out_of_range("Please supply a valid range");
        return buffer[i];
    }
    T& get(size_t i) const {
        if (i > used) throw std::out_of_range("Please supply a valid range");
        return buffer[i];
    }
    void append(T v) {
        if (capacity == used) {
            size_t newCapacity = capacity + 1;
            auto newBuffer = new T[newCapacity];
            std::copy_n(buffer, used, newBuffer);
            delete[] buffer;
            buffer = newBuffer;
            capacity = newCapacity;
            used++;
        }
        else {
            buffer[used] = v;
            used++;
        }
    }
    // By index
    T remove_index(size_t index) {
        if (index > used) throw std::out_of_range("Please supply a valid range");
        T e = buffer[index];
        std::copy_n(buffer + index + 1, used - index - 1, buffer + index);
        used--;
        return e;
    }
    // Searches
    void remove(T v) {
        for (size_t i = 0; i < used; i++) {
            if (buffer[i] == v)
                remove_index(i); break;
        }
    }
    // todo rule of five
private:
    T* buffer;
    size_t capacity;
    size_t used;
    bool valuesAreOwned;
};
#endif