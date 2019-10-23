#ifndef FILE_SMART_PTR_HPP
#define FILE_SMART_PTR_HPP

template<typename T>
class smart_ptr {
public:
    smart_ptr() : t(nullptr) {}
    smart_ptr(T* t) : t(t) {}
    virtual ~smart_ptr() = default;
    bool operator==(T* t) {
        return this->t == t;
    }
    bool operator!=(T* t) {
        return this->t != t;
    }
    T* operator->() {
        return t;
    }
    T& operator*() {
        return *t;
    }
    explicit operator bool() const noexcept {
        return t != nullptr;
    }
    T* get() {
        return t;
    }
    T* release() noexcept {
        T* tmp = t;
        t = nullptr;
        return tmp;
    }
protected:
    T* t;
};

#endif // FILE_SMART_PTR_HPP