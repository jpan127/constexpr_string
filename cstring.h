#pragma once

#include "string_literal.h"

#include <array>

template <std::size_t N, typename ... Literal>
class cstring {
  public:
    static constexpr std::size_t kSize = N;

    /// Constructor
    constexpr cstring(Literal ... literals) {
        constexpr auto copy = [](auto &buffer, const auto &other, auto &index) {
            for (std::size_t ii = 0; ii < other.size(); ii++) {
                buffer[index++] = other[ii];
            }
        };

        (copy(buffer_, literals, index_), ...);

        // Null terminate
        buffer_[kSize] = '\0';
    }

    constexpr const char *value() const {
        return buffer_.data();
    }

    constexpr std::size_t size() const {
        return kSize;
    }

    std::size_t index_ = 0;
    std::array<char, N + 1> buffer_{};
};

template <typename FirstType>
constexpr std::size_t length(FirstType first) {
    return first;
}

template <typename FirstType, typename ... Literal>
constexpr std::size_t length(FirstType first, Literal ... literals) {
    return first + length(literals...);
}

template <std::size_t ... sizes>
struct SumTrait {
    static constexpr std::size_t value = length(sizes...);
    constexpr SumTrait() = default;
};

template <std::size_t ... sizes>
constexpr std::size_t kSum = SumTrait<sizes...>::value;

template <typename ... Literal>
constexpr auto make_cstring(Literal && ... literals) {
    constexpr std::size_t n = kSum<literals...>;
    return cstring<n, Literal...>(literals...);
}

template <std::size_t LengthA, std::size_t LengthB>
constexpr auto make_cstring(const char (&a)[LengthA], const char (&b)[LengthB]) {
    return cstring<LengthA + LengthB, decltype(StringLiteral{a}), decltype(StringLiteral{b})>(StringLiteral{a}, StringLiteral{b});
}
