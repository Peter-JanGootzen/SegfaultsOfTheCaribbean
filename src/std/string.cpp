#include <iostream>
#include <stdexcept>
#include <cstring>
#include "std/string.hpp"

String::String() {
    n = 0;
    a = nullptr;
};
String::String(const char* buffer) {
    n = 0;
    const char* temp = buffer;
    while(*buffer++)
        n++;
    a = new char[n];
    std::memcpy(a, temp, n);
};
String::String(unsigned int size, const char* buffer) {
    n = size;
    a = new char[size];
    std::memcpy(a, buffer, size);
};

int String::size() const {
    return n;
};

char* String::c_str() const {
    return a;
};

String String::operator+(const String& s) {
    int newSize = n + s.size();
    auto newBuffer = new char[newSize];
    std::strcpy(newBuffer, a);
    std::strcat(newBuffer, s.a);
    String newString = String(newSize, newBuffer);
    return newString;
};
char& String::operator[](unsigned int i) const {
    if (i > this->size())
        throw std::out_of_range("Please supply a valid range");
    return a[i];
}
bool String::operator==(const String& s) const noexcept {
    if (s.size() != this->size()) return false;

    for(int i = 0; i < this->n; i++) {
        if (s[i] != this->a[i]) return false;
    }

    return true;
}

std::ostream& operator<<(std::ostream& os, const String& s)
{
    for(int i = 0; i < s.size(); i++)
    {
        os << s[i];
    }
    return os;
}

String operator<<(const String& r, const String& s)
{
    char* buffer = new char[s.size() + r.size() + 1];
    char* bff_ptr = buffer;
    std::memcpy(buffer, r.a, r.size());
    bff_ptr+=r.size();
    std::memcpy(bff_ptr, s.a, s.size());
    bff_ptr+=s.size();
    *bff_ptr = '\0';
    String string = String(buffer);
    delete[] buffer;
    return string;
};

/// Rule of Five
// copy constructor, should not kill the other value
String::String(const String& other) {
    // stack
    n = other.n;
    // heap
    a = new char[other.n];
    std::memcpy(a, other.a, n);
}

// copy assignment operator, should not kill the other value
String& String::operator=(const String& other) {
    if (this != &other) {
        // stack
        this->n = other.n;
        // heap
        if (this->a != nullptr)
            delete[] this->a;
        this->a = new char[other.n];
        std::memcpy(this->a, other.a, this->n);
    }
    return *this;
}

// move constructor, should kill the other value
String::String(String&& other) {
    // stack
    n = other.n;
    // heap
    a = other.a;
    other.a = nullptr;
}

// move assignment operator, should kill the other value
String& String::operator=(String&& other) {
    if (this != &other) {
        // stack
        n = other.n;
        // heap
        if (this->a != nullptr)
            delete[] a;
        a = other.a;
        other.a = nullptr;
    }
    return *this;
}
String::~String() {
    delete[] a;
};
