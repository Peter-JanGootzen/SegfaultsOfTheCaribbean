#ifndef FILE_SMART_PTR_HPP
#define FILE_SMART_PTR_HPP

template<typename T>
class smart_ptr {
public:
    smart_ptr() noexcept : t(nullptr) {}
    smart_ptr(T* t) noexcept : t(t) {}
    virtual ~smart_ptr() = default;
    bool operator==(T* t) const noexcept {
        return this->t == t;
    }
    bool operator!=(T* t) const noexcept {
        return this->t != t;
    }
    T* operator->() const noexcept {
        return t;
    }
    T& operator*() const {
        return *t;
    }
    explicit operator bool() const noexcept {
        return t != nullptr;
    }
    T* get() const noexcept {
        return t;
    }
    T* release() noexcept {
        T* tmp { t };
        t = nullptr;
        return tmp;
    }
protected:
    T* t;
};

#endif // FILE_SMART_PTR_HPP