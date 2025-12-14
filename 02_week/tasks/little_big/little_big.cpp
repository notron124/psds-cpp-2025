#include <cstring>
#include <iostream>

template<typename T>
void PrintMemory(T num, bool isReversed = false) {
    std::string output = "";

    // Надеюсь использование memcpy разрешено
    unsigned char bytes[sizeof(T)];
    std::memcpy(bytes, &num, sizeof(T));
 
    size_t start = isReversed ? (sizeof(T) - 1) : 0;
    int step = isReversed ? -1 : 1;

    for (size_t i = start; i < sizeof(T); i += step) {
        unsigned char currentByte = bytes[i];
        
        for (int j = 4; j >= 0; j -= 4) {
            int remainder = (currentByte >> j) & 0xf;
            char hexChar = 0;

            hexChar = remainder < 10 ? '0' + remainder : 'A' + (remainder - 10);

            output += hexChar;
        }
    }
    output = "0x" + output;
    std::cout << output << std::endl;
}
