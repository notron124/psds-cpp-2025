#include <algorithm>
#include <initializer_list>
#include <vector>

class RingBuffer {
public:
    RingBuffer() : ringBuff_(1), head_(0), tail_(0), size_(0) {}
    
    RingBuffer(size_t capacity) : ringBuff_(capacity > 0 ? capacity : 1), head_(0), tail_(0), size_(0) {}

    RingBuffer(size_t capacity, const int iVal) : ringBuff_(capacity > 0 ? capacity : 1, iVal), head_(capacity), tail_(0),
                                             size_(capacity > 0 ? capacity : 1) {}

    RingBuffer(std::initializer_list<int> list) : ringBuff_(list), head_(0), tail_(0), size_(list.size()) {        
        if (list.size() == 0) {
            ringBuff_.reserve(1);
            size_ = 0;
        }
    }

    void Push(int val);
    bool TryPush(int val);
    void Pop();
    bool TryPop(int& val);
    int& Front();
    const int& Front() const;
    int& Back();
    const int& Back() const;
    bool Empty() const;
    bool Full() const;
    size_t Size() const;
    size_t Capacity() const;
    void Clear();
    void Resize(size_t newSize);
    std::vector<int> Vector() const;
    
    int& operator[](size_t idx) {
        return ringBuff_[(tail_ + idx) % ringBuff_.size()];
    }

    const int& operator[](size_t idx) const {
        return ringBuff_[(tail_ + idx) % ringBuff_.size()];
    }

private:
    std::vector<int> ringBuff_{};
    size_t head_  = 0;
    size_t tail_  = 0;
    size_t size_  = 0;
};

void RingBuffer::Push(int val) {
    size_t cap = ringBuff_.capacity();
    
    ringBuff_[head_] = val;
    // при head = buff.capacity(), head снова станет = 0
    head_ = (head_ + 1) % cap;

    if (size_ < cap) {
        ++size_;
    } else {
        // аналогично head
        tail_ = (tail_ + 1) % ringBuff_.capacity();
    }
}

bool RingBuffer::TryPush(int val) {
    size_t cap = ringBuff_.capacity();

    if (size_ == cap) {
        return false;
    }

    ringBuff_[head_] = val;
    // при head = buff.capacity(), head снова станет = 0
    head_ = (head_ + 1) % cap;

    ++size_;

    return true;
}

void RingBuffer::Pop() {
    if (size_ > 0) {
        tail_ = (tail_ + 1) % ringBuff_.capacity();
        --size_;
    }
}

bool RingBuffer::TryPop(int& val) {    
    if (size_ > 0) {
        val = ringBuff_[tail_];
        tail_ = (tail_ + 1) % ringBuff_.capacity();
        --size_;
        return true;
    }
    
    return false; 
}

int& RingBuffer::Front() {
    if (head_ == 0) {
        return ringBuff_.back();
    }
    
    return ringBuff_[head_ - 1];
}

const int& RingBuffer::Front() const {
    if (head_ == 0) {
        return ringBuff_.back();
    }
    
    return ringBuff_[head_ - 1];
}
    
int& RingBuffer::Back() {
    return ringBuff_[tail_];
}

const int& RingBuffer::Back() const {
    return ringBuff_[tail_];
}

bool RingBuffer::Empty() const {
    return size_ == 0;
}


bool RingBuffer::Full() const {
    return size_ == ringBuff_.capacity();
}

size_t RingBuffer::Size() const {
    return size_;
}

size_t RingBuffer::Capacity() const {
    return ringBuff_.capacity();
}

void RingBuffer::Clear() {
    head_ = 0;
    tail_ = 0;
    size_ = 0;
}

void RingBuffer::Resize(size_t newSize) {
    if (newSize == 0) {
        ++newSize;
    }   
    
    if (newSize == ringBuff_.size()) {
        return;
    }

    size_t sz = std::min(size_, newSize);

    std::vector<int> tempV;
    tempV.reserve(sz);

    for (size_t i = 0; i < sz; ++i) {
        tempV.push_back(ringBuff_[(head_ - 1 - i + ringBuff_.size()) % ringBuff_.size()]);
    }

    std::reverse(tempV.begin(), tempV.end());
    ringBuff_.resize(newSize);

    for (size_t i = 0; i < sz; ++i) {
        ringBuff_[i] = tempV[i];
    }

    ringBuff_.shrink_to_fit();
    
    tail_ = 0;
    head_ = sz;
    size_ = sz;
}

std::vector<int> RingBuffer::Vector() const {
    std::vector<int> v;
    v.reserve(size_);
    
    for (size_t i = 0; i < size_; ++i) {
        v.push_back(ringBuff_[(tail_ + i) % ringBuff_.size()]);
    }

    return v;
 } 
