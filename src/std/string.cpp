#include <iostream>
#include <stdexcept>
#include <cstring>
#include "std/string.hpp"

String::String() {
    n = 0;
    a = nullptr;
}
// C-String as parameter
String::String(const char* buffer) {
    n = 1;
    const char* temp = buffer;
    while(*buffer++)
        n++;
    if (n == 1) {
        n = 0;
        a = nullptr;
    }
    else {
        n--;
        a = new char[n];
        std::memcpy(a, temp, n);
    }
}
String::String(unsigned int size, const char* buffer) {
    n = size;
    a = new char[size];
    std::memcpy(a, buffer, size);
}

size_t String::size() const {
    return n;
}

char* String::c_str() const {
    char* c_str = new char[n + 1];
    std::memcpy(c_str, a, n);
    c_str[n] = '\0';
    return c_str;
}

String String::operator+(const String& s) {
    int newSize = n + s.size();
    auto newBuffer = new char[newSize];
    std::memcpy(newBuffer, a, n);
    std::memcpy(newBuffer + n, s.a, s.n);
    String newString = String(newSize, newBuffer);
    return newString;
}
char& String::operator[](unsigned int i) const {
    if (i > this->size())
        throw std::out_of_range("Please supply a valid range");
    return a[i];
}
bool String::operator==(const String& s) const noexcept {
    if (s.size() != this->size()) return false;

    for(size_t i = 0; i < this->n; i++) {
        if (s[i] != this->a[i]) return false;
    }

    return true;
}

std::ostream& operator<<(std::ostream& os, const String& s)
{
    for(size_t i = 0; i < s.size(); i++)
    {
        os << s[i];
    }
    return os;
}

String operator<<(const String& s, int i) {
    int l = 1;
    int c = i;
    while(c /= 10)
        l++;
    int sSize = 0;
    if (s.a)
        sSize = s.size();
    char* buffer = new char[sSize + l + 1];
    char* bff_ptr = buffer;
    if(s.a) {
        std::memcpy(buffer, s.a, s.size());
        bff_ptr+=s.size() - 1;
    }
    sprintf(bff_ptr,"%d", i);
    String input = String(buffer);
    delete[] buffer;
    return input;
}

String operator<<(const String& r, const String& s)
{
    int sSize = 0;
    if (s.a)
        sSize = s.size();
    int rSize = 0;
    if (r.a)
        rSize = r.size();
    char* buffer = new char[sSize + rSize];
    char* bff_ptr = buffer;
    std::memcpy(buffer, r.a, rSize);
    bff_ptr+=rSize;
    std::memcpy(bff_ptr, s.a, sSize);
    String string = String(sSize + rSize, buffer);
    delete[] buffer;
    return string;
}

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
    if (a)
        delete[] a;
}


void String::append(char x) {
    int newSize = n + 1;
    auto newBuffer = new char[newSize];
    if (a != nullptr) {
        std::memcpy(newBuffer, a, n);
        delete[] a;
    }
    newBuffer[newSize - 1] = x;
    n = newSize;
    a = newBuffer;
}

String String::substr(size_t from, size_t to) {
    int size = to - from;
    char* buffer = new char[size];
    std::memcpy(buffer, a + from, size);
    auto string = String(size, buffer);
    delete[] buffer;
    return string;
}

size_t String::find(char delim) {
    if (!a) return -1;

    size_t i = 0;
    while(a[i] != delim) {
        i++;
        if (i > n - 1)
            return -1;
    }
    return i;
}