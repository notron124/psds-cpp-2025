#include <algorithm>
#include <cstddef>
#include <ctime>
#include <initializer_list>
#include <memory>
#include <utility>

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

    constexpr auto operator[](size_t idx) const noexcept {
        return elems_[idx];
    }

    ~Array() = default;

    constexpr T& Front() const noexcept;
    constexpr T& Back() const noexcept;
    constexpr T* Data() noexcept;
    constexpr const T* Data() const noexcept;
    constexpr bool Empty() const noexcept;
    constexpr size_t Size() const noexcept;
    constexpr void Fill(const T& elem) noexcept;
    constexpr void Swap(Array& other) noexcept;
    constexpr auto begin() const noexcept;
    constexpr auto end() const noexcept;
    constexpr const T* cbegin() const noexcept;
    constexpr const T* cend() const noexcept;

private:
    T elems_[arrSize];
};

template<typename T, size_t arrSize>
constexpr bool operator==(const Array<T, arrSize>& lhs, const Array<T, arrSize>& rhs) {
    return std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template<typename T, size_t arrSize>
constexpr bool operator!=(const Array<T, arrSize>& lhs, const Array<T, arrSize>& rhs) {
    return !(lhs == rhs);
}

template<typename T, size_t arrSize>
constexpr bool operator<(const Array<T, arrSize>& lhs, const Array<T, arrSize>& rhs) {
    return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template<typename T, size_t arrSize>
constexpr bool operator>(const Array<T, arrSize>& lhs, const Array<T, arrSize>& rhs) {
    return !(lhs == rhs) && !(lhs < rhs);
}

template<typename T, size_t arrSize>
constexpr bool operator<=(const Array<T, arrSize>& lhs, const Array<T, arrSize>& rhs) {
    return !(lhs > rhs);
}

template<typename T, size_t arrSize>
constexpr bool operator>=(const Array<T, arrSize>& lhs, const Array<T, arrSize>& rhs) {
    return !(lhs < rhs);
}

template<typename T, size_t arrSize>
constexpr T& Array<T, arrSize>::Front() const noexcept {
    return elems_[0];
}

template<typename T, size_t arrSize>
constexpr T& Array<T, arrSize>::Back() const noexcept {
    return elems_[arrSize - 1];
}

template<typename T, size_t arrSize>
constexpr T* Array<T, arrSize>::Data() noexcept {
    return elems_;
}

template<typename T, size_t arrSize>
constexpr const T* Array<T, arrSize>::Data() const noexcept {
    return elems_;
}

template<typename T, size_t arrSize>
constexpr bool Array<T, arrSize>::Empty() const noexcept {
    return arrSize == 0;
}

template<typename T, size_t arrSize>
constexpr size_t Array<T, arrSize>::Size() const noexcept {
    return arrSize;
}

template<typename T, size_t arrSize>
constexpr void Array<T, arrSize>::Fill(const T& elem) noexcept {
    std::fill(begin(), end(), elem);
}

template<typename T, size_t arrSize>
constexpr void Array<T, arrSize>::Swap(Array& other) noexcept {
    for (size_t i = 0; i < arrSize; ++i) {
        std::swap(elems_[i], other.elems_[i]);
    }
}

template<typename T, size_t arrSize>
constexpr auto Array<T, arrSize>::begin() const noexcept {
    return elems_;
}

template<typename T, size_t arrSize>
constexpr auto Array<T, arrSize>::end() const noexcept {
    return elems_ + arrSize;
}

template<typename T, size_t arrSize>
constexpr const T* Array<T, arrSize>::cbegin() const noexcept {
    return elems_;
}

template<typename T, size_t arrSize>
constexpr const T* Array<T, arrSize>::cend() const noexcept {
    return elems_ + arrSize;
}

template<typename T, size_t arrSize>
constexpr void swap(Array<T, arrSize>& arr1, Array<T, arrSize>& arr2) noexcept {
    arr1.Swap(arr2);
}

template<size_t idx, typename ArrayType>
constexpr decltype(auto) get(ArrayType&& arr) {
    return std::forward<ArrayType>(arr)[idx];
}
