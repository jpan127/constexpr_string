#include "cstring.h"

#include <iostream>

int main() {
    constexpr auto a = StringLiteral{"hello"};
    constexpr auto b = StringLiteral{"helloo"};
    constexpr auto c = StringLiteral{"hellooo"};
    constexpr auto unspecialized = make_cstring(a, b, c);
    constexpr auto specialized = make_cstring("hello", "helloo");
    std::cout << unspecialized.value() << std::endl;
    std::cout << specialized.value() << std::endl;
}
