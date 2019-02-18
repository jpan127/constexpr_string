#pragma once

#include "string_literal.h"

#include <array>

template <std::size_t N, typename ... Literal>
class cstring {
  public:
    /// Size of the buffer
    static constexpr std::size_t Size = N;

    /// Constructor without delimiter
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

    /// Constructor with delimiter
    constexpr cstring(const char delimiter, Literal ... literals) {
        constexpr auto copy = [](auto &buffer, const char delimiter, const auto &other, auto &index) {
            for (std::size_t ii = 0; ii < other.size(); ii++) {
                buffer[index++] = other[ii];
            }

            buffer[index++] = delimiter;
        };

        (copy(buffer_, delimiter, literals, index_), ...);

        // Null terminate and replace last delimiter
        buffer_[index_ - 1] = '\0';
    }

    /// Returns c string
    constexpr const char *value() const {
        return buffer_.data();
    }

    /// Returns size of string
    constexpr std::size_t size() const {
        return Size;
    }

  private:
    /// Underlying buffer
    std::array<char, N + 2> buffer_{};

    /// Tracks the indice of the buffer on construction
    std::size_t index_ = 0;
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

template <typename ... Literal>
constexpr auto join_helper(const char delimiter, Literal && ... literals) {
    constexpr std::size_t kNumLiterals = sizeof...(literals);

    // Determines the combined size of all the literals
    constexpr std::size_t n = (decltype(StringLiteral{literals})::Size + ...) + (kNumLiterals - 1);

    // Makes a cstring object
    return cstring<n, Literal...>(delimiter, literals...);
}

template <typename ... Literal>
constexpr auto join(const char delimiter, Literal && ... literals) {
    constexpr bool kAllConstCharLiterals = all_const_char_literals<Literal...>;

    // For [const char *] literals, they need to be explicitly converted to [StringLiteral]
    if constexpr (kAllConstCharLiterals) {
        return join_helper(delimiter, StringLiteral{literals}...);
    // For [StringLiteral] wrappers, they can be passed directly
    } else {
        return join_helper(delimiter, literals...);
    }
}

template <typename ... Literal>
constexpr auto join_with_whitespace(Literal && ... literals) {
    return join(' ', literals...);
}

template <typename ... Literal>
constexpr auto join_with_underscore(Literal && ... literals) {
    return join('_', literals...);
}

template <typename ... Literal>
constexpr auto join_with_comma(Literal && ... literals) {
    return join(',', literals...);
}
