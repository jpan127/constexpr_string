#pragma once

#include "string_literal.h"

#include <array>

template <std::size_t N, typename ... Literal>
class cstring {
  public:
    static constexpr std::size_t Size = N;

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
        return Size;
    }

    std::size_t index_ = 0;
    std::array<char, N + 1> buffer_{};
};

/// Checks if all types inherit from [LiteralBase]
template <typename ... Literal>
constexpr bool all_custom_string_literals = (std::is_base_of_v<LiteralBase, typename std::remove_reference<Literal>::type> && ...);

/// Checks if all types decay to [const char *]
template <typename ... Literal>
constexpr bool all_const_char_literals = (std::is_same<typename std::decay<Literal>::type, const char *>::value && ...);

template <typename ... Literal>
constexpr auto concatenate_helper(Literal && ... literals) {
    // Determines the combined size of all the literals
    constexpr std::size_t n = (decltype(StringLiteral{literals})::Size + ...);

    // Makes a cstring object
    return cstring<n, Literal...>(literals...);
}

template <typename ... Literal>
constexpr auto concatenate(Literal && ... literals) {
    constexpr bool kAllConstCharLiterals = all_const_char_literals<Literal...>;

    // For [const char *] literals, they need to be explicitly converted to [StringLiteral]
    if constexpr (kAllConstCharLiterals) {
        return concatenate_helper(StringLiteral{literals}...);
    // For [StringLiteral] wrappers, they can be passed directly
    } else {
        return concatenate_helper(literals...);
    }
}
