#pragma once

#include "string_buffer.h"

namespace cexpr_string::detail {

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

    // Makes a StringBuffer object
    return StringBuffer<n, Literal...>(literals...);
}

template <typename ... Literal>
constexpr auto join_helper(const char delimiter, Literal && ... literals) {
    constexpr std::size_t kNumLiterals = sizeof...(literals);

    // Determines the combined size of all the literals
    constexpr std::size_t n = (decltype(StringLiteral{literals})::Size + ...) + (kNumLiterals - 1);

    // Makes a StringBuffer object
    return StringBuffer<n, Literal...>(delimiter, literals...);
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

} // namespace cexpr_string::detail

namespace cexpr_string {

template <typename ... Literal>
constexpr auto concatenate(Literal && ... literals) {
    constexpr bool kAllConstCharLiterals = detail::all_const_char_literals<Literal...>;

    // For [const char *] literals, they need to be explicitly converted to [StringLiteral]
    if constexpr (kAllConstCharLiterals) {
        return detail::concatenate_helper(StringLiteral{literals}...);
    // For [StringLiteral] wrappers, they can be passed directly
    } else {
        return detail::concatenate_helper(literals...);
    }
}

template <typename ... Literal>
constexpr auto join_with_whitespace(Literal && ... literals) {
    return detail::join(' ', literals...);
}

template <typename ... Literal>
constexpr auto join_with_underscore(Literal && ... literals) {
    return detail::join('_', literals...);
}

template <typename ... Literal>
constexpr auto join_with_comma(Literal && ... literals) {
    return detail::join(',', literals...);
}

} // namespace cexpr_string
