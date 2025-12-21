#include <cstddef>
#include <vector>

class Stack {
public:
    void Push(int val);
    bool Pop();
    int& Top();
    const int& Top() const;
    bool Empty() const;
    size_t Size() const;
    void Clear();
    void Swap(Stack& other);

    bool operator==(const Stack& other) const {
        return this->stack_ == other.stack_;
    }

    bool operator!=(const Stack& other) const {
        return !(*this == other);
    }
            
private:
    std::vector<int> stack_{};
};

void Stack::Push(int val) {
    stack_.push_back(val);
}

bool Stack::Pop() {
    if (stack_.empty()) {
        return false;
    }
    
    stack_.pop_back();
    return true;
}

int& Stack::Top() {
    return stack_.back();
}

const int& Stack::Top() const {
    return stack_.back();
}

bool Stack::Empty() const {
    return stack_.empty();
}

size_t Stack::Size() const {
    return stack_.size();
}

void Stack::Clear() {
    stack_.clear();
}

void Stack::Swap(Stack& other) {
    stack_.swap(other.stack_);
}
