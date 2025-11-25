#include <cstddef>
#include <stdexcept>

// Есть ощущение, что это можно решить как-то более лаконично и просто

/**
 * @brief Получить длину последовательности из одинаковых знаков.
 * @param array указатель на элемент массива, с которого начнется проверка.
 * @return Длина последовательности.
 * @note Все символы будут сравниваться с первым из переданного массива.
 */
size_t GetIdenticalCharSequenceLen(char *array) {
    size_t sequenceLen = 0;

    if (array[0] == '\0') {
        return 0;
    }

    while (array[0] == array[sequenceLen]) {
        ++sequenceLen;
    }

    return sequenceLen;
}

/**
 * @brief Сконвертировать одинаковые символы.
 * @param array указатель на начало обрабатываемого массива.
 * @param convertedSymIdx ссылка на индекс последнего сконвертированного символа.
 * @param currentSymIdx ссылка на индекс текущего обрабатываемого символа.
 * @param swapChar знак, на который будет произведена замена array[convertedSymIdx].
 * @return none
 */
void ConvertIdenticalCharacters(char array[], size_t& convertedSymIdx, size_t& currentSymIdx, char swapChar) {  
    size_t sequenceLen = GetIdenticalCharSequenceLen(&array[currentSymIdx]);
                
    array[convertedSymIdx++] = swapChar;

    if (sequenceLen == 1) {
        currentSymIdx += sequenceLen;
        return;    
    }

    if (sequenceLen >= 10) {
        array[convertedSymIdx++] = '0';
    } else {
        array[convertedSymIdx++] = sequenceLen + '0';
    }

    currentSymIdx += sequenceLen;
}

size_t CharChanger(char array[], size_t size, char delimiter = ' ') {
    size_t convertedSymbolIdx = 0, currentSymbolIdx = 0;

    while(currentSymbolIdx < size && convertedSymbolIdx < size) {
        if (array[currentSymbolIdx] == '\0') {
            break;
        }

        if (isspace(array[currentSymbolIdx])) {
            currentSymbolIdx += GetIdenticalCharSequenceLen(&array[currentSymbolIdx]);

            array[convertedSymbolIdx++] = delimiter;
            continue;
        }

        if (isalnum(array[currentSymbolIdx])) {
            if (isdigit(array[currentSymbolIdx])) {
                ConvertIdenticalCharacters(array, convertedSymbolIdx, currentSymbolIdx, '*');
                continue;
            }
            
            ConvertIdenticalCharacters(array, convertedSymbolIdx, currentSymbolIdx, toupper(array[currentSymbolIdx]));
            continue;
        }

        ConvertIdenticalCharacters(array, convertedSymbolIdx, currentSymbolIdx, '_');    
    }

    array[convertedSymbolIdx] = '\0';
    return convertedSymbolIdx;
}
