#ifndef FILE_STRING_HPP
#define FILE_STRING_HPP

#include <ostream>

class String {
public:
    String();
    String(const char* buffer);
    String(unsigned int size, const char* buffer);
    // copy constructor, should not kill the other value
    String(const String& other);
    // copy assignment operator, should not kill the other value
    String& operator=(const String& other);
    // move constructor, should kill the other value
    String(String&& other);
    // move assignment operator, should kill the other value
    String& operator=(String&& other);
    String operator+(const String& s);
    char& operator[](unsigned int i) const;
    bool operator==(const String& s) const noexcept;
    friend std::ostream& operator<<(std::ostream& os, const String& s);
    friend String operator<<(const String& r, const String& s);
    ~String();
    int size() const;
    char* c_str() const;
private:
    int n;
    char* a;
};

#endif