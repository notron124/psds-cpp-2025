#include <climits>
#include <utility>
#include <vector>

std::pair<std::vector<int>::const_iterator, std::vector<int>::const_iterator> MinMax(const std::vector<int>& v) {
    if (v.empty()) {
        return {v.end(), v.end()};
    }

    auto minIt = v.begin();
    auto maxIt = v.end();    
    int min = INT_MAX;
    int max = INT_MIN;

    for (auto it = v.begin(); it != v.end(); ++it) {
        if (*it < min) {
            min = *it;
            minIt = it;
        }

        if (*it >= max) {
            max = *it;
            maxIt = it;
        }
    }
    
    return {minIt, maxIt};
}
