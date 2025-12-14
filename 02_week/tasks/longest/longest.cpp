#include <stdexcept>


const char* FindLongestSubsequence(const char* begin, const char* end, size_t& count) {
    if (begin == nullptr || end == nullptr) {
        count = 0;
        return nullptr;
    }

    if (begin >= end) {
        count = 0;
        return nullptr;
    }

    size_t currSequenseLen = 0;
    const char* longestSequenceStart = begin;

    while (begin != end) {
        currSequenseLen++;

        if (*begin != *(begin + 1)) {
            if (currSequenseLen > count) {
                count = currSequenseLen;
                longestSequenceStart = begin - (currSequenseLen - 1);
            }
            currSequenseLen = 0;
        }
               
        ++begin;
    }

    return longestSequenceStart;
}

char* FindLongestSubsequence(char* begin, char* end, size_t& count) {
    const char* result = FindLongestSubsequence(
        static_cast<const char*>(begin),
        static_cast<const char*>(end),
        count
    );

    return const_cast<char*>(result);
}
