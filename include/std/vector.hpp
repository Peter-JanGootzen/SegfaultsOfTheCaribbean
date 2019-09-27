#ifndef FILE_VECTOR_HPP
#define FILE_VECTOR_HPP
#include <stdexcept>
#include <cstring>
template<class T>
class Vector {
public:
    Vector(T* buffer, unsigned int n) : used(n), buffer(buffer) {};
    ~Vector() {
        if (valuesAreOwned)
        {
            delete[] buffer;
        }
    }
    T& operator[](unsigned int i) const {
        if (i > used) throw std::out_of_range("Please supply a valid range");
        return buffer[i];
    }
    void append(T* v) {
        if (capacity == used) {
            // allocate new array and copy everything over
        }
        else {
            // Just append it
        }
    }
    // By index
    void remove(unsigned int index) {
        std::memcpy(buffer + index, buffer + index + 1, used - index - 1);
        used--;
    }
    // Searches
    void remove(T* v) {
        for (int i = 0; i < used; i++) {
            if (buffer[i] == v)
                return remove(i);
        }
    }
    void delet() {
        delete[] buffer;
    }
    // todo rule of five
private:
    T* buffer;
    unsigned int capacity;
    unsigned int used;
    bool valuesAreOwned;
};
#endif