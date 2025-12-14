#include <stdexcept>

typedef bool (*predicate_func_t)(int);

const int* FindLastElement(const int* begin, const int* end, predicate_func_t predicate) {
    if (begin == nullptr || end == nullptr) {
        return end;
    }

    if (begin >= end) {
        return end;
    }

    const int* result = end;

    // begin и end передаются by copy, так что инкремент указателя
    // не повлияет на переданный указатель 
    while (begin != end) {
        if (predicate(*begin)) {
            result = begin;
        }
        ++begin;
    }

    return result;
}
