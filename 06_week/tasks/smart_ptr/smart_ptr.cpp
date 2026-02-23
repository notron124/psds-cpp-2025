#include <cstddef>
#include <string>

struct ControlBlock {
    size_t refCount = 1;
    size_t weakRefCount = 0;
};

class SharedPtr {
public:
    SharedPtr() = default;
    
    SharedPtr(std::string* str) : ptr_(str), ctrlBlock_(str ? new ControlBlock : nullptr) {}

    SharedPtr(const SharedPtr& other) : ptr_(other.ptr_), ctrlBlock_(other.ctrlBlock_) {
        IncRefCount();
    };

    SharedPtr(SharedPtr&& other) : ptr_(other.ptr_), ctrlBlock_(other.ctrlBlock_) {
        other.ptr_ = nullptr;
        other.ctrlBlock_ = nullptr;
    }
    
    ~SharedPtr() {
        Release();
    }
    
    SharedPtr& operator=(const SharedPtr& other) {
        if (this == &other) {
            return *this;
        }

        Release();
        ptr_ = other.ptr_;
        ctrlBlock_ = other.ctrlBlock_;
        IncRefCount();
        return *this;
    }

    SharedPtr& operator=(SharedPtr&& other) {
        if (this == &other) {
            return *this;
        }

        Release();
        ptr_ = other.ptr_;
        ctrlBlock_ = other.ctrlBlock_;
        other.ptr_ = nullptr;
        other.ctrlBlock_ = nullptr;                
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

    std::string* Get() const noexcept;
    void Reset(std::string* other);
    void Swap(SharedPtr& other);
    size_t UseCount() const noexcept;
    
private:
    std::string* ptr_ = nullptr;
    ControlBlock* ctrlBlock_ = nullptr;
    
    void Release();
    void IncRefCount();

    SharedPtr(std::string* ptr, ControlBlock* ctrl) : ptr_(ptr), ctrlBlock_(ctrl) {
        IncRefCount();
    } 
  
    friend class WeakPtr;
};

void SharedPtr::Release() {
    if (!ctrlBlock_) {
        return;
    }

    if (--ctrlBlock_->refCount == 0) {
        delete ptr_;
        ptr_ = nullptr;    
        if (ctrlBlock_->weakRefCount == 0) {
            delete ctrlBlock_;
            ctrlBlock_ = nullptr;
        }
    }
}

void SharedPtr::IncRefCount() {
    if (ctrlBlock_) {
        ++ctrlBlock_->refCount;
    }
} 

std::string * SharedPtr::Get() const noexcept{
    return ptr_;
}

void SharedPtr::Reset(std::string* ptr = nullptr) {
    Release();
    ptr_ = ptr;
    ctrlBlock_ = ptr_ ? new ControlBlock : nullptr;
}

void SharedPtr::Swap(SharedPtr& other) {
    std::swap(ptr_, other.ptr_);
    std::swap(ctrlBlock_, other.ctrlBlock_);
}

size_t SharedPtr::UseCount() const noexcept {
    if (!ctrlBlock_) {
        return 0;
    }

    return ctrlBlock_->refCount;
}

// Можно было сделать одну функцию через шаблон и forward,
// но оставим это на потом
SharedPtr MakeShared(const std::string& str) {
    std::string* strCopy = new std::string(str);
    return SharedPtr(strCopy);
}

SharedPtr MakeShared(std::string&& str) {
    std::string* movedStr = new std::string(std::move(str));
    return SharedPtr(movedStr);
}

class WeakPtr {
public:
    WeakPtr() = default;

    WeakPtr(const SharedPtr& sPtr) : ptr_(sPtr.ptr_), ctrlBlock_(sPtr.ctrlBlock_) {
        IncWeakCount();
    }

    WeakPtr(const WeakPtr& other) : ptr_(other.ptr_), ctrlBlock_(other.ctrlBlock_) {
        IncWeakCount();
    }

    WeakPtr(WeakPtr&& other) : ptr_(other.ptr_), ctrlBlock_(other.ctrlBlock_) {
        other.ptr_ = nullptr;
        other.ctrlBlock_ = nullptr;
    }

    ~WeakPtr() {
        Release();
    }

    WeakPtr& operator=(const SharedPtr& sPtr) {
        Release();
        ptr_ = sPtr.ptr_;
        ctrlBlock_ = sPtr.ctrlBlock_;
        IncWeakCount();
        return *this;
    }

    WeakPtr& operator=(const WeakPtr& other) {
        if (this == &other) {
            return *this;
        }

        Release();
        ptr_ = other.ptr_;
        ctrlBlock_ = other.ctrlBlock_;
        IncWeakCount();
        return *this;  
    }

    WeakPtr& operator=(WeakPtr&& other) {
        if (this == &other) {
            return *this;
        }

        Release();
        ptr_ = other.ptr_;
        ctrlBlock_ = other.ctrlBlock_;
        other.ptr_ = nullptr;
        other.ctrlBlock_ = nullptr;
        return *this;  
    }
    
    void Reset() noexcept;
    void Swap(WeakPtr& other);
    size_t UseCount() const noexcept; 
    bool Expired() const noexcept;
    SharedPtr Lock();
        
private:
    std::string* ptr_ = nullptr;
    ControlBlock* ctrlBlock_ = nullptr;

    void Release();
    void IncWeakCount();
    
    friend class SharedPtr;
};

void WeakPtr::Release() {
    if (!ctrlBlock_) {
        return;
    }

    if (--ctrlBlock_->weakRefCount == 0 && ctrlBlock_->refCount == 0) {
        delete ctrlBlock_;
    }
    ptr_ = nullptr;
    ctrlBlock_ = nullptr;
}

void WeakPtr::IncWeakCount() {
    if (ctrlBlock_) {
        ++ctrlBlock_->weakRefCount;
    }
}

void WeakPtr::Reset() noexcept {
    Release();
}

void WeakPtr::Swap(WeakPtr& other) {
    std::swap(ptr_, other.ptr_);
    std::swap(ctrlBlock_, other.ctrlBlock_);
}

size_t WeakPtr::UseCount() const noexcept {
    if (!ctrlBlock_) {
        return 0;
    }

    return ctrlBlock_->refCount;
}

bool WeakPtr::Expired() const noexcept {
    return !ctrlBlock_ || ctrlBlock_->refCount == 0;
}

SharedPtr WeakPtr::Lock() {
    if (Expired()) {
        return SharedPtr();
    }

    return SharedPtr(ptr_, ctrlBlock_);
} 

template<typename T>
void Swap(T& ptr1, T& ptr2) {
    ptr1.Swap(ptr2);
}
