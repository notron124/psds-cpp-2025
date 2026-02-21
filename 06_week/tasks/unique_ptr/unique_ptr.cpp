#include <string>

class UniquePtr {
public:
    UniquePtr() = default;
    
    UniquePtr(std::string* str) : ptr_(str) {}

    UniquePtr(const UniquePtr& ptr) = delete;

    UniquePtr(UniquePtr&& other) : ptr_(other.ptr_) {
        other.ptr_ = nullptr;
    }
    
    ~UniquePtr() {
        delete ptr_;
    }
    
    UniquePtr& operator=(const UniquePtr& other) = delete;

    UniquePtr& operator=(UniquePtr&& other) {
        if (this == &other) {
            return *this;
        }
        
        delete ptr_;
        ptr_ = other.ptr_;
        other.ptr_ = nullptr;
        return *this;
    }

    std::string& operator*() const {
        return *ptr_;
    }

    std::string* operator->() const {
        return ptr_;
    }

    explicit operator bool() const noexcept {
        return ptr_ != nullptr;
    }

    std::string* Get() const;
    std::string* Release();
    void Reset(std::string* other);
    void Swap(UniquePtr& other);
    
private:
    std::string* ptr_ = nullptr;
};

std::string* UniquePtr::Get() const {
    return ptr_;
}

std::string* UniquePtr::Release() {
    std::string* tPtr = ptr_;
    ptr_ = nullptr;
    return tPtr;
}

void UniquePtr::Reset(std::string* ptr = nullptr) {
    delete ptr_;
    ptr_ = ptr;
}

void UniquePtr::Swap(UniquePtr& other) {
    std::swap(ptr_, other.ptr_);
}

// Можно было сделать одну функцию через шаблон и forward,
// но оставим это на потом
UniquePtr MakeUnique(const std::string& str) {
    std::string* strCopy = new std::string(str);
    return UniquePtr(strCopy);
}

UniquePtr MakeUnique(std::string&& str) {
    std::string* movedStr = new std::string(std::move(str));
    return UniquePtr(movedStr);
}

void Swap(UniquePtr& ptr1, UniquePtr& ptr2) {
    ptr1.Swap(ptr2);
}
