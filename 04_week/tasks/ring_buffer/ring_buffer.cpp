#include <algorithm>
#include <initializer_list>
#include <vector>

class RingBuffer {
public:
    RingBuffer() : ringBuff(1), head(0), tail(0), size(0) {}
    
    RingBuffer(size_t capacity) : head(0), tail(0), size(0) {
        if (capacity == 0) {
            ++capacity;
        }
        ringBuff.reserve(capacity);
    }

    RingBuffer(size_t capacity, int iVal) : head(capacity), tail(0),
                                            isFull(true), isEmpty(false) {
                                                    
        if (capacity == 0) {
            ++capacity;
        }
        size = capacity;
        ringBuff.resize(capacity);
        std::fill(ringBuff.begin(), ringBuff.end(), iVal);
    }

    RingBuffer(std::initializer_list<int> list) : tail(0), isFull(true), isEmpty(false) {        
        if (list.size() != 0) {
            size = list.size();
            head = size;
            ringBuff.resize(size);
            std::copy(list.begin(), list.end(), ringBuff.begin());
            return;
        }
        
        size = 0;
        head = 0;
        ringBuff.resize(1);
        ringBuff[0] = 0;
        isFull = false;
        isEmpty = true;        
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
        return ringBuff[(tail + idx) % ringBuff.size()];
    }

    const int& operator[](size_t idx) const {
        return ringBuff[(tail + idx) % ringBuff.size()];
    }

private:
    std::vector<int> ringBuff{};
    size_t head  = 0;
    size_t tail  = 0;
    size_t size  = 0;
    bool isFull  = false;
    bool isEmpty = true;
};

void RingBuffer::Push(int val) {
    size_t cap = ringBuff.capacity();
    
    isEmpty = false;
    ringBuff[head] = val;
    // при head = buff.capacity(), head снова станет = 0
    head = (head + 1) % cap;

    if (size < cap) {
        ++size;
    } else {
        // аналогично head
        tail = (tail + 1) % ringBuff.capacity();
    }

    if (size == cap) {
        isFull = true;
    }
}

bool RingBuffer::TryPush(int val) {
    size_t cap = ringBuff.capacity();

    if (isFull) {
        return false;
    }
    
    isEmpty = false;
    ringBuff[head] = val;
    // при head = buff.capacity(), head снова станет = 0
    head = (head + 1) % cap;

    ++size;

    if (size == cap) {
        isFull = true;
    }

    return true;
}

void RingBuffer::Pop() {
    isFull = false;
    
    if (size > 0) {
        tail = (tail + 1) % ringBuff.capacity();
        --size;
    } else {
        isEmpty = true;
    }
}

bool RingBuffer::TryPop(int& val) {    
    isFull = false;

    if (size > 0) {
        val = ringBuff[tail];
        tail = (tail + 1) % ringBuff.capacity();
        --size;
        return true;
    }
    
    isEmpty = true;
    return false; 
}

int& RingBuffer::Front() {
    return ringBuff[head - 1];
}

const int& RingBuffer::Front() const {
    return ringBuff[head - 1];
}
    
int& RingBuffer::Back() {
    return ringBuff[tail];
}

const int& RingBuffer::Back() const {
    return ringBuff[tail];
}

bool RingBuffer::Empty() const {
    return isEmpty;
}


bool RingBuffer::Full() const {
    return isFull;
}

size_t RingBuffer::Size() const {
    return size;
}

size_t RingBuffer::Capacity() const {
    return ringBuff.capacity();
}

void RingBuffer::Clear() {
    head = 0;
    tail = 0;
    size = 0;
    isFull = false;
    isEmpty = true;
}

void RingBuffer::Resize(size_t newSize) {
    if (newSize == ringBuff.capacity()) {
        return;
    }

    size_t sz = std::min(size, newSize);

    if (sz == 0) {
        ++sz;
    }

    std::vector<int> tempV;
    tempV.reserve(sz);

    for (size_t i = 0; i < sz; ++i) {
        tempV.push_back(ringBuff[(tail + i) % ringBuff.size()]);
    }

    ringBuff.resize(newSize);

    for (size_t i = 0; i < sz; ++i) {
        ringBuff[i] = std::move(tempV[i]);
    }

    tail = 0;
    head = sz;
    size = sz;
}

std::vector<int> RingBuffer::Vector() const {
    std::vector<int> v;
    v.reserve(size);
    for (size_t i = 0; i < size; ++i) {
        v.push_back(ringBuff[(tail + i) % ringBuff.size()]);
    }

    return v;
 } 
