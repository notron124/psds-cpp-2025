#include <algorithm>
#include <cstddef>
#include <ctime>
#include <initializer_list>

template<typename T, std::size_t arrSize>
class Array {
public:
    Array() = default;

    Array(std::initializer_list<T> list) noexcept {
        size_t size = std::min(list.size(), arrSize);
        for (size_t i = 0; i < size; ++i) {
            elems_[i] = list[i];
        }
    }

    constexpr Array(const Array& other) {
        std::copy(other.elems_, other.elems_ + arrSize, elems_);
    }

    Array(Array&& other) noexcept {
        for (size_t i = 0; i < arrSize; ++i) {
            elems_[i] = std::move(other.elems_[i]);
        }
    }

    constexpr Array& operator=(const Array& other) {
        if (this == &other) {
            return *this;
        }

        std::copy(other.elems_, other.elems_ + arrSize, elems_);
        return *this;
    }

    Array& operator=(Array&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        for (size_t i = 0; i < arrSize; ++i) {
            elems_[i] = std::move(other.elems_[i]);
        }
    }

    constexpr T& operator[](size_t idx) const noexcept {
        return elems_[idx];
    }

    ~Array() = default;

    constexpr T& Front() const noexcept;
    constexpr T& Back() const noexcept;
    constexpr const T* Data() const noexcept;
    constexpr bool Empty() const noexcept;
    constexpr size_t Size() const noexcept;
    constexpr void Fill() noexcept;
    constexpr void Swap() noexcept;
    constexpr T* Begin() const noexcept;
    constexpr T* End() const noexcept;
    constexpr const T* cbegin() const noexcept;
    constexpr const T* cend() const noexcept;

private:
    T elems_[arrSize];
};

template<typename T, size_t arrSize>
constexpr bool operator==(Array<T, arrSize>& lhs, Array<T, arrSize>& rhs) {
    return std::equal(lhs.Begin(), lhs.End(), rhs.Begin());
}

template<typename T, size_t arrSize>
constexpr bool operator!=(Array<T, arrSize>& lhs, Array<T, arrSize>& rhs) {
    return !(lhs == rhs);
}

template<typename T, size_t arrSize>
constexpr T& Array<T, arrSize>::Front() const noexcept {
    return elems_[0];
}

template<typename T, size_t arrSize>
constexpr T& Array<T, arrSize>::Back() const noexcept {
    return elems_[arrSize - 1];
}

