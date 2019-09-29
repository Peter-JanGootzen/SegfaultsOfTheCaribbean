#ifndef FILE_VECTOR_HPP
#define FILE_VECTOR_HPP
#include <stdexcept>
#include <algorithm>
template<class T>
class Vector {
public:
    Vector(T* buffer, size_t n, bool valuesAreOwned) : size(n), valuesAreOwned(valuesAreOwned) {
        this->buffer = new T[n];
        std::copy_n(buffer, n, this->buffer);
    };
    Vector(bool valuesAreOwned) : valuesAreOwned(valuesAreOwned) {
        size = 0;
        buffer = nullptr;
    };
    ~Vector() {
        if (valuesAreOwned) {
            for (int i = 0; i < size; i++) {
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
        if (i > size || !buffer) throw std::out_of_range("Please supply a valid range");
        return buffer[i];
    }
    T& get(size_t i) const {
        if (i > size || !buffer) throw std::out_of_range("Please supply a valid range");
        return buffer[i];
    }
    void append(T v) {
        auto newBuffer = new T[size + 1];
        if (buffer) {
            std::copy_n(buffer, size, newBuffer);
            delete[] buffer;
        }
        buffer = newBuffer;
        buffer[size] = v;
        size++;
    }
    // By index
    T remove_index(size_t index) {
        if (index > size || !buffer) throw std::out_of_range("Please supply a valid range");
        T e = buffer[index];

        auto newBuffer = new T[size];
        std::copy_n(buffer, index, newBuffer);
        std::copy_n(buffer + index, size - index - 1, newBuffer + index);
        size--;
        return e;
    }
    // Searches
    void remove(T v) {
        for (size_t i = 0; i < size; i++) {
            if (buffer[i] == v) {
                remove_index(i); break;
            }
        }
    }
    size_t getSize() const {
        return size;
    }
    // todo rule of five
private:
    T* buffer;
    size_t size;
    bool valuesAreOwned;
};
#endif