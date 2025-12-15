#include <stdexcept>

typedef bool (*Predicate)(int);

void Filter(std::vector<int> &v, Predicate predicateFunc) { 
    if (v.empty() || predicateFunc == nullptr) {
        return;
    }
    
    for (auto it = v.begin(); it != v.end();) {
        if (predicateFunc(*it)) {
            it = v.erase(it);
        } else {
            ++it;
        }
    }
}
