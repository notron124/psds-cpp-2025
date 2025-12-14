#include <cmath>
#include <vector>

struct DataStats {
    double avg = 0.0;
    double sd = 0.0;
};

struct DataStats CalculateDataStats(const std::vector<int> &v) {
    if (v.empty()) {
        return {0.0, 0.0};
    }

    long sum = 0;
    long sumSq = 0;

    for (auto val : v) {
        sum += val;
        sumSq += static_cast<long>(val) * val;
    }

    auto n = v.size();
    double avg = static_cast<double>(sum) / n;
    double variance = (sumSq - (static_cast<double>(sum) * sum) / n) / n;

    return { avg, std::sqrt(variance) };
}
