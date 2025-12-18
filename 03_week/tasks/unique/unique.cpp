#include <vector>

std::vector<int> Unique(const std::vector<int>& v) {
    std::vector<int> uniqueElem{};

    uniqueElem.reserve(v.size());

    
    for (auto val : v) {
        if (uniqueElem.empty() || (uniqueElem.back() != val)) { 
            uniqueElem.push_back(val);
        }
    }

    uniqueElem.shrink_to_fit();

    return uniqueElem;
}
