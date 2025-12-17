#include <cstdint>
#include <ostream>
#include <sys/types.h>
#include <type_traits>

enum class CheckFlags : uint8_t {
    NONE = 0,
    TIME = (1 << 0),
    DATE = (1 << 1),
    USER = (1 << 2),
    CERT = (1 << 3),
    KEYS = (1 << 4),
    DEST = (1 << 5),
    ALL = TIME | DATE | USER | CERT | KEYS | DEST
};

// Для GoogleTest
explicit operator bool(CheckFlags f) {
    return static_cast<std::underlying_type_t<CheckFlags>>(f) != 0;
}

bool operator!(const CheckFlags f) {
    return static_cast<std::underlying_type_t<CheckFlags>>(f) == 0;
}

bool operator==(CheckFlags lhs, CheckFlags rhs) {
    return static_cast<std::underlying_type_t<CheckFlags>>(lhs) ==
           static_cast<std::underlying_type_t<CheckFlags>>(rhs);
}

bool operator!=(CheckFlags lhs, CheckFlags rhs) {
    return !(lhs == rhs);
}

CheckFlags operator|(CheckFlags lhs, CheckFlags rhs) {
    return static_cast<CheckFlags>(
            (static_cast<std::underlying_type_t<CheckFlags>>(lhs) |
            static_cast<std::underlying_type_t<CheckFlags>>(rhs)) & static_cast<std::underlying_type_t<CheckFlags>>(CheckFlags::ALL)
    );
}

CheckFlags operator&(CheckFlags lhs, CheckFlags rhs) {
    auto uintLhs = static_cast<std::underlying_type_t<CheckFlags>>(lhs);
    auto uintRhs = static_cast<std::underlying_type_t<CheckFlags>>(rhs);
    
    return static_cast<CheckFlags>(uintLhs & uintRhs);
}

CheckFlags operator^(CheckFlags lhs, CheckFlags rhs) {
    return static_cast<CheckFlags>(
        static_cast<std::underlying_type_t<CheckFlags>>(lhs) ^
        static_cast<std::underlying_type_t<CheckFlags>>(rhs)
    );
}

CheckFlags operator~(const CheckFlags& f) {
    return static_cast<CheckFlags>(~static_cast<std::underlying_type_t<CheckFlags>>(f));
}

std::ostream& operator<<(std::ostream& os, const CheckFlags& f) {
    if (f == CheckFlags::ALL) {
        return os;
    }    
    return os;
}
