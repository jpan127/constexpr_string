#pragma once

#include "string_literal.h"

#include <array>

#define EXPLICIT_SPECIALIZATION 0

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
        buffer_[index_] = '\0';
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

template <typename T>
constexpr std::size_t length(const T literal) {
    return literal;
}

template <typename FirstType, typename ... Literal>
constexpr std::size_t length(const FirstType first, const Literal ... literals) {
    return length(first) + length(literals...);
}

template <std::size_t ... sizes>
struct SumTrait : std::integral_constant<std::size_t, length(sizes...)> {
};

template <std::size_t ... sizes>
constexpr std::size_t kSum = SumTrait<sizes...>::value;

#if EXPLICIT_SPECIALIZATION

#include "explicitly_specialized_cstring.h"

#else /// EXPLICIT_SPECIALIZATION

template <typename ... Literal>
constexpr bool all_custom_string_literals() {
    return (std::is_base_of_v<LiteralBase, Literal> && ...);
}

template <typename ... Literal>
constexpr auto concatenate(Literal && ... literals) {
    constexpr bool kIsCustomStringLiteral = all_custom_string_literals<typename std::remove_reference<Literal>::type...>();
    if constexpr (kIsCustomStringLiteral) {
        constexpr std::size_t n = kSum<literals...>;
        return cstring<n, Literal...>(literals...);
    } else {
        constexpr std::size_t n = length(StringLiteral{literals}...);
        return cstring<n, decltype(StringLiteral{literals})...>( StringLiteral{literals}... );
    }
}

// template <auto ... Literals>
// constexpr auto concatenate() {
//     constexpr std::size_t n = kSum<Literals...>;
//     return cstring<n, decltype(Literals)...>(Literals...);
// }

#endif /// EXPLICIT_SPECIALIZATION
