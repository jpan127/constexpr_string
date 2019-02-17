#include <string_view>

template <typename First>
constexpr std::size_t sum(First first) {
    return first.size();
}

template <typename First, typename ... StringViews>
constexpr std::size_t sum(First first, StringViews ... stringviews) {
    return first.size() + sum(stringviews...);
}

// template <typename ... StringViews>
// constexpr std::size_t accumulate(StringViews &&... stringviews) {
//     constexpr auto s = variadic::make_cstring<sum(stringviews...), StringViews...>(stringviews...);
// }

// template <std::size_t N>
// constexpr std::size_t echo() {
//     return N;
// }

// template <typename ... StringViews>
// constexpr std::size_t accumulate(StringViews && ... stringviews) {
//     const auto n = sum(std::forward<StringViews>(stringviews)...);
//     return echo<n>();
// }

int main() {
    using namespace std::string_view_literals;
    constexpr std::string_view a = "hello"sv;
    constexpr std::string_view b = "helloo"sv;
    constexpr std::string_view c = "hellooo"sv;
    constexpr std::size_t n = sum(a, b, c);
    std::cout << n << std::endl;
    constexpr auto d = variadic::make_cstring<n>(a, b, c);
    std::cout << d.value() << std::endl;

    // accumulate("hello"sv, "helloo"sv);
}
