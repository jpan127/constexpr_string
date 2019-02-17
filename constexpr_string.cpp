#include <cstddef>
#include <array>
#include <iostream>
#include <utility>

    using namespace std::string_view_literals;
#include <string_view>
#include <string.h>

#include "string_literal.h"

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

// template <std::size_t N, typename ... Literal>
// constexpr auto make_cstring(Literal && ... literals) {
//     return cstring<N, Literal...>(std::forward<Literal>(literals)...);
// }

template <typename FirstType>
constexpr std::size_t length(FirstType first) {
    return first;
}

template <typename FirstType, typename ... Literal>
constexpr std::size_t length(FirstType first, Literal ... literals) {
    return first + length(literals...);
}

template <typename ... Literal>
constexpr std::size_t count(Literal ... literals) {
    return sizeof...(literals);
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

template <std::size_t ... Lengths>
constexpr auto make_cstring(const char (&a)[LengthA], const char (&b)[LengthB]) {
    return cstring<LengthA + LengthB, decltype(StringLiteral{a}), decltype(StringLiteral{b})>(StringLiteral{a}, StringLiteral{b});
}

int main() {
    constexpr auto a = StringLiteral{"hello"};
    constexpr auto b = StringLiteral{"helloo"};
    constexpr auto c = StringLiteral{"hellooo"};
    // constexpr auto d = StringLiteral{"hello"};
    // constexpr auto n = length(a, b, c, d);
    // static_assert(length(a, b, c, d) == (strlen("hello") * count(a, b, c, d)));
    // static_assert(make_cstring<length(a, b, c, d)>(a, b, c, d).size() == length(a, b, c, d));

    // constexpr auto s = make_cstring<length(a, b, c, d)>(a, b, c, d);
    // std::cout << s.value() << std::endl;

    constexpr auto unspecialized = make_cstring(a, b, c);
    constexpr auto specialized = make_cstring("hello", "helloo");
    std::cout << unspecialized.value() << std::endl;
    std::cout << specialized.value() << std::endl;
}
