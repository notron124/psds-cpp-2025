#include <memory>

template<typename ObjType, typename Deleter = std::default_delete<ObjType>, typename... Args>
decltype(auto) MakeUnique(Args&&... args) {
    return std::unique_ptr<ObjType, Deleter> {new ObjType(std::forward<Args>(args)...)};
}
