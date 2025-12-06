#include <stdexcept>

typedef double(*operations_t)(double, double); 

double ApplyOperations(double a, double b, operations_t mathOperations[], size_t size) {
    if (size == 0 || mathOperations == nullptr) {
        return 0.0;
    }

    double sum = 0.0;
    
    for (size_t i = 0; i < size; ++i) {
        if (mathOperations[i] != nullptr) {
            sum += mathOperations[i](a, b);
        }
    }

    return sum;
}
