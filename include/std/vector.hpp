#ifndef FILE_VECTOR_HPP
#define FILE_VECTOR_HPP
#include <stdexcept>
#include <algorithm>
template<class T>
class Vector {
public:
    Vector(T* buffer, size_t n, bool valuesAreOwned) : used(n), capacity(n), valuesAreOwned(valuesAreOwned) {
        this->buffer = new T[n];
        std::copy_n(buffer, n, this->buffer);
    };
    Vector(size_t n, bool valuesAreOwned) : used(0), capacity(n), valuesAreOwned(valuesAreOwned) {
        buffer = new T[n];
    };
    ~Vector() {
        if (valuesAreOwned) {
            for (int i = 0; i < used; i++) {
                delete (buffer[i]);
            }
        }
        delete[] buffer;
    }
    // copy constructor, should not kill the other value
    Vector(const Vector& other) = delete;
    // copy assignment operator, should not kill the other value
    Vector& operator=(const Vector& other) = delete;
    // move constructor, should kill the other value
    Vector(Vector&& other) = delete;
    // move assignment operator, should kill the other value
    Vector& operator=(Vector&& other) = delete;
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
            buffer[used] = std::move(v);
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
    size_t getCapacity() const {
        return capacity;
    }
    size_t getUsed() const {
        return capacity;
    }
    // todo rule of five
private:
    T* buffer;
    size_t capacity;
    size_t used;
    bool valuesAreOwned;
};
#endif