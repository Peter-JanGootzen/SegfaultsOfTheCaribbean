#ifndef FILE_STRING_HPP
#define FILE_STRING_HPP

#include <ostream>

class String {
public:
    String();
    String(const char* buffer);
    String(size_t size, const char* buffer);
    // copy constructor, should not kill the other value
    String(const String& other);
    // move constructor, should kill the other value
    String(String&& other) noexcept;
    // move assignment operator, should kill the other value
    String& operator=(String&& other);
    // copy assignment operator, should not kill the other value
    String& operator=(const String& other);
    String operator+(const String& s);
    char& operator[](size_t i) const;
    bool operator==(const String& s) const noexcept;
    friend std::ostream& operator<<(std::ostream& os, const String& s);
    friend String operator<<(const String& r, const String& s);
    friend String operator<<(const String& s, int i);
    ~String();
    void append(char x);
    size_t size() const noexcept;
    char* c_str() const noexcept;
    String substr(size_t from, size_t to);
    size_t find(char delim);
private:
    size_t n;
    char* a;
};

#endif
