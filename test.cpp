#include "cstring.h"

#include <iostream>
#include <typeinfo>

int main() {

    // {
    //     constexpr auto a = StringLiteral{"hello"};
    //     constexpr auto b = StringLiteral{"helloo"};
    //     constexpr auto c = StringLiteral{"hellooo"};
    //     constexpr auto unspecialized = concatenate<
    //         SL{"hello"},
    //         SL{"helloo"},
    //         SL{"hellooo"}>();
    //     std::cout << unspecialized.value() << std::endl;
    // }

    {
        constexpr auto a = StringLiteral{"hello"};
        constexpr auto b = StringLiteral{"helloo"};
        constexpr auto c = StringLiteral{"hellooo"};

        constexpr auto unspecialized = concatenate(a, b, c);
        std::cout << unspecialized.value() << std::endl;
        std::cout << unspecialized.size() << std::endl;

        static_assert(std::is_base_of<LiteralBase, decltype(a)>::value);
        static_assert(std::is_base_of<LiteralBase, decltype(b)>::value);
        static_assert(std::is_base_of<LiteralBase, decltype(c)>::value);
    }

    {
        constexpr auto unspecialized = concatenate("hello", "helloo", "hellooo");
        std::cout << unspecialized.value() << std::endl;
        std::cout << unspecialized.size() << std::endl;
    }
}
