#include <vector>

typedef bool (*Predicate)(int);

void Filter(std::vector<int> &v, Predicate predicateFunc) { 
    if (v.empty() || predicateFunc == nullptr) {
        return;
    }

    auto secondIt = v.begin();
    size_t newSize = 0;
    for (auto it = v.begin(); it != v.end(); ++it) {
        if (predicateFunc(*it)) {
            if (it != secondIt) {
                *secondIt = *it; 
            }
            ++secondIt;
            ++newSize;
        }
    }

    v.resize(newSize);
}
