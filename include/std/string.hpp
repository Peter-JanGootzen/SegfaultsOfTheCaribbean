#ifndef FILE_STRING_HPP
#define FILE_STRING_HPP

class String {
public:
    String();
    String(unsigned int size, char* buffer);
    ~String();
    int size() const;
    
    String operator+(const String& s);
    char& operator[](unsigned int i) const;
    bool operator==(const String& s) const noexcept;
    friend std::ostream& operator<<(std::ostream& os, const String& s);
private:
    int n;
    char* a;
};

#endif