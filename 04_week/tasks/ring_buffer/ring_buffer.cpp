#include <initializer_list>
#include <vector>

class RingBuffer {
public:
    RingBuffer() {
        ringBuff.reserve(1);
        frontIt = ringBuff.begin();
        backIt = ringBuff.begin();
    }
    
    RingBuffer(size_t size) {
        ringBuff.reserve(size);        
        frontIt = ringBuff.begin();
        backIt = ringBuff.begin();
    };

    RingBuffer(size_t size, int iVal) : ringBuff(size, iVal), \
            frontIt(ringBuff.end() - 1), backIt(ringBuff.begin() - 1) {};

    RingBuffer(std::initializer_list<int> list) : ringBuff(list), frontIt(ringBuff.end() - 1), backIt(ringBuff.begin()) {};

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
    void Resize();
    std::vector<int> Vector() const;

    int oldestElement = 0;
    
    
private:
    std::vector<int> ringBuff{};
    std::vector<int>::iterator frontIt;
    std::vector<int>::iterator backIt;
};

void RingBuffer::Push(int val) {
    ++frontIt;

    if (frontIt == ringBuff.end()) {
        frontIt = ringBuff.begin();
    }

    if (frontIt == backIt) {
        ++backIt;
    }

    if (backIt == ringBuff.end()) {
        backIt = ringBuff.begin();
    }

    *frontIt = val;
}

bool RingBuffer::TryPush(int val) {
    ++frontIt;

    if (frontIt == ringBuff.end()) {
        frontIt = ringBuff.begin();
    }

    if (frontIt == backIt) {
        --frontIt;
        return false; 
    }

    *frontIt = val;
    
    return true;   
}

void RingBuffer::Pop() {
    if (backIt == frontIt) {
        return;
    }

    ++backIt;
    
    if (backIt == ringBuff.end()) {
        backIt = ringBuff.begin();
    }
}

bool RingBuffer::TryPop(int& val) {    
    if (backIt == frontIt) {
        return false;
    }

    val = *backIt;

    ++backIt;
    
    if (backIt == ringBuff.end()) {
        backIt = ringBuff.begin();
    }

    return true;
}

int& RingBuffer::Front() {
    return *frontIt;
}

const int& RingBuffer::Front() const {
    return *frontIt;
}
    
int& RingBuffer::Back() {
    return *backIt;
}

const int& RingBuffer::Back() const {
    return *backIt;
}

bool RingBuffer::Empty() const {
    return backIt == frontIt; // will be wrong on circ buffer size of one
}

bool RingBuffer::Full() const {
    return (frontIt + 1) == backIt; // also will be wrong on buffer size of one 
}


