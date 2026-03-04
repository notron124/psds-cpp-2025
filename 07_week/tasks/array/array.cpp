#include <algorithm>
#include <cstddef>
#include <ctime>
#include <initializer_list>

template<typename T, std::size_t N>
class Array {
public:
    Array() = default;

    Array(std::initializer_list<T> list) noexcept {
        size_t size = std::min(list.size(), N);
        for (size_t i = 0; i < size; ++i) {
            elems_[i] = list[i];
        }
    }

    Array(const Array& other) {
        std::copy(other.elems_, other.elems_ + N, elems_);
    }

    Array(Array&& other) noexcept {
        for (size_t i = 0; i < N; ++i) {
            elems_[i] = std::move(other.elems_[i]);
        }
    }

    Array& operator=(const Array& other) {
        if (this == &other) {
            return *this;
        }

        std::copy(other.elems_, other.elems_ + N, elems_);
        return *this;
    }

    Array& operator=(Array&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        for (size_t i = 0; i < N; ++i) {
            elems_[i] = std::move(other.elems_[i]);
        }
    }

    ~Array() = default;

    

private:
    T elems_[N];
};
