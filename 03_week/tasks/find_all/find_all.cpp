#include <stdexcept>

typedef bool (*Predicate)(int);

std::vector<size_t> FindAll(const std::vector<int> &v, Predicate predicate_func) {
    if (v.empty() || predicate_func == nullptr) {
        return {};
    }

    std::vector<size_t> output;
    output.reserve(v.size());

    for (size_t i = 0; i < v.size(); ++i) {
        if (predicate_func(v[i])) {
            output.push_back(i);
        }
    }

    output.shrink_to_fit();

    return output;
}
