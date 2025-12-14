#include <iostream>
#include <stdexcept>
#include <string>


void PrintArray(const int* begin, const int* end, int constrainer = 0) {
    if (begin == nullptr || end == nullptr) {
        std::cout << "[]" << std::endl;
        return;
    }

    std::string output = "[";

    size_t size = std::abs(begin - end);

    const int* arr = begin > end ? end + 1 : begin;
    size_t startIndex = begin > end ? size - 1 : 0;
    int step = begin > end ? -1 : 1;
    size_t charCntr = 0;

    for (size_t i = startIndex; i < size; i += step) {
        if (i != startIndex) {
            output.append(", ");
            if ((constrainer > 0) && (charCntr % constrainer == 0)) {
                output.append("...\n ");
                charCntr = 0;
            } 
        }
            
        output.append(std::to_string(arr[i]));
        charCntr++;
    }

    output += "]";

    std::cout << output << std::endl;
}
