#include <iostream>
#include <stdexcept>
#include <cstring>
#include "std/string.hpp"

String::String() {
    n = 0;
    a = nullptr;
};
String::String(unsigned int size, char* buffer) {
    n = size;
    a = buffer;
};
String::~String() {
    // Someone is doing memory management for us. Thanks I guess?...
    //delete[] a;
};
int String::size() const {
    return n;
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

}

std::ostream& operator<<(std::ostream& os, const String& s)
{
    for(int i = 0; i < s.size(); i++)
    {
        os << s[i];
    }
    return os;
}