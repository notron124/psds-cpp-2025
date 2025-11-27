#include <cstddef>
#include <stdexcept>
#include <cmath>

double CalculateRMS(double values[], size_t size) {
    if (size == 0 || values == NULL) {
        return 0.0;
    }

    double sum = 0.0;
    for (size_t i = 0; i < size; ++i) {
       sum += values[i] * values[i];
    }

    return std::sqrt(sum / static_cast<double>(size));
}
