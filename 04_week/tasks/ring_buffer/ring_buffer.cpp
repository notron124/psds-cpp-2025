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
    bool TryPop();
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
    if ((frontIt + 1) != backIt) {
        *frontIt = val;
        ++frontIt;
    }

    
}
    
