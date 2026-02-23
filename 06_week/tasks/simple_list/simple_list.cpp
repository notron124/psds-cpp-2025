#include <cstddef>
#include <string>

// Эффективнее было бы выделить data в отдельную структуру
// с наследованием Node и везде использовать неявный upcast/downcast.
// Однако это сделало бы код менее лаконичным и для простой реализации
// я выбрал читаемость и выразительность кода относительно небольшой оптимизации. 
struct Node {
    std::string data;
    Node* next;
    Node* prev;

    Node() : data(), next(this), prev(this) {}

    Node(const std::string& str) : data(str), next(nullptr), prev(nullptr) {}
    
    Node(std::string&& str) : data(std::move(str)), next(nullptr), prev(nullptr) {}
};

class SimpleList {
public:
    SimpleList() = default;

    SimpleList(const SimpleList& other) {
        for (Node* cur = other.dummy_.next; cur != &other.dummy_; cur = cur->next) {
            PushBack(cur->data);
        }
    }

    SimpleList(SimpleList&& other) {    
        Move(std::move(other));
    }

    ~SimpleList() {
        Clear();
    }

    SimpleList& operator=(const SimpleList& other) {
        if (this == &other) {
            return *this;
        }

        Clear();                
        for (Node* cur = other.dummy_.next; cur != &other.dummy_; cur = cur->next) {
            PushBack(cur->data);
        }
        return *this;
    }

    SimpleList& operator=(SimpleList&& other) {
        if (this == &other) {
            return *this;
        }

        Clear();
        Move(std::move(other));
        return *this;
    }

    void Swap(SimpleList& other) noexcept;
    size_t Size() const noexcept;
    bool Empty() const noexcept;
    void PushBack(const std::string& str);
    void PushBack(std::string&& str);
    void PopBack();
    void PushFront(const std::string& str);
    void PushFront(std::string&& str);
    void PopFront();
    std::string& Back() const noexcept;
    std::string& Front() const noexcept;
    void Clear();
private:  
    Node dummy_;
    size_t size_ = 0;
    
    void Remove(Node* node);
    void Insert(Node* pos, Node* node) noexcept;
    void Move(SimpleList&& other) noexcept;
};

void SimpleList::Remove(Node* node) {
    if (Empty() || !node) {
        return;
    }

    node->next->prev = node->prev;
    node->prev->next = node->next;
    delete node; 
    --size_;
}

void SimpleList::Insert(Node* pos, Node* node) noexcept {
    if (!pos || !node) {
        return;
    }

    node->prev = pos;
    node->next = pos->next;
    pos->next->prev = node;
    pos->next = node;
    ++size_;
}

void SimpleList::Move(SimpleList&& other) noexcept {
    dummy_.next = other.dummy_.next;
    dummy_.prev = other.dummy_.prev;
    dummy_.next->prev = &dummy_;
    dummy_.prev->next = &dummy_;
    size_ = other.size_;
    other.dummy_.next = &other.dummy_;
    other.dummy_.prev = &other.dummy_;
    other.size_ = 0;
}

void SimpleList::Swap(SimpleList& other) noexcept {
    std::swap(dummy_.next, other.dummy_.next);
    std::swap(dummy_.prev, other.dummy_.prev);
    std::swap(size_, other.size_);

    if (!Empty()) {
        dummy_.next->prev = &dummy_;
        dummy_.prev->next = &dummy_;
    }

    if (!other.Empty()) {
        other.dummy_.next->prev = &other.dummy_;
        other.dummy_.prev->next = &other.dummy_;
    }
}

size_t SimpleList::Size() const noexcept {
    return size_;
}

bool SimpleList::Empty() const noexcept {
    return size_ == 0;
}

void SimpleList::PushBack(const std::string& str) {
    Node* newNode = new Node(str);
    Insert(dummy_.prev, newNode);
}

void SimpleList::PushBack(std::string&& str) {
    Node* newNode = new Node(std::move(str));
    Insert(dummy_.prev, newNode);
}

void SimpleList::PopBack() {
    Remove(dummy_.prev);
}

void SimpleList::PushFront(const std::string& str) {
    Node* newNode = new Node(str);
    Insert(&dummy_, newNode);
}

void SimpleList::PushFront(std::string&& str) {
    Node* newNode = new Node(std::move(str));
    Insert(&dummy_, newNode);
}

void SimpleList::PopFront() {
    Remove(dummy_.next);
}

std::string& SimpleList::Back() const noexcept {
    return dummy_.prev->data;
}

std::string& SimpleList::Front() const noexcept {
    return dummy_.next->data;
}

void SimpleList::Clear() {
    while(!Empty()) {
        Remove(dummy_.next);
    }
}

void Swap(SimpleList& lst1, SimpleList& lst2) {
    lst1.Swap(lst2);
}
