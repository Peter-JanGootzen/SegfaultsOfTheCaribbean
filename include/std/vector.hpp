#ifndef FILE_VECTOR_HPP
#define FILE_VECTOR_HPP
#include <stdexcept>
#include <algorithm>
#include <functional>
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
            for (size_t i = 0; i < size; i++) {
                delete buffer[i];
            }
        }
        delete[] buffer;
    }
    // copy constructor, should not kill the other value
    Vector(const Vector& other) = delete;
    // copy assignment operator, should not kill the other value
    Vector& operator=(const Vector& other) = delete;
    // move constructor, should kill the other value
    Vector(Vector&& other) {
        size = other.size;

        buffer = other.buffer;
        other.buffer = nullptr;
    }
    // move assignment operator, should kill the other value
    Vector& operator=(Vector&& other) {
        if (this != &other) {
            size = other.size;

            if (valuesAreOwned) {
                for (size_t i = 0; i < size; i++) {
                    delete buffer[i];
                }
            }
            delete[] buffer;
            this->buffer = other.buffer;
            other.buffer = nullptr;
        }
        return *this;
    }
    T& operator[](size_t i) const {
        if (i > size || !buffer) throw std::out_of_range("Please supply a valid range");
        return buffer[i];
    }
    T& get(size_t i) const {
        if (i > size || !buffer) throw std::out_of_range("Please supply a valid range");
        return buffer[i];
    }
    T get_filter(std::function<bool (T)> filter) const {
        for (size_t i = 0; i < size; i++) {
            if (filter(buffer[i])) {
                return buffer[i];
            }
        }
        return nullptr;
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

        auto newBuffer = new T[size - 1];
        std::copy_n(buffer, index, newBuffer);
        std::copy_n(buffer + index + 1, size - index - 1, newBuffer + index);
        delete[] buffer;
        buffer = newBuffer;
        size--;
        return e;
    }
    // Searches
    T remove(T v) {
        for (size_t i = 0; i < size; i++) {
            if (buffer[i] == v)
                return remove_index(i);
        }
        return nullptr;
    }
    T remove_filter(std::function<bool (T)> filter) {
        for (size_t i = 0; i < size; i++) {
            if (filter(buffer[i]))
                return remove_index(i);
        }
        return nullptr;
    }
    bool has_filter(std::function<bool (T)> filter) const {
        for (size_t i = 0; i < size; i++) {
            if (filter(buffer[i]))
                return true;
        }
        return false;
    }
    size_t count_filter(std::function<int  (T)> filter) {
        size_t total = 0;
        for (size_t i = 0; i < size; i++) {
            if (filter(buffer[i])) {
                total++;
            }
        }
        return total;
    }
    size_t getSize() const {
        return size;
    }
    bool empty() const {
        return size == 0;
    }
    // todo rule of five
private:
    T* buffer;
    size_t size;
    bool valuesAreOwned;
};
#endif
