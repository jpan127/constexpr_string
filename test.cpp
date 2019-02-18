#include "cstring.h"

#include <iostream>
#include <typeinfo>

int main() {
    constexpr auto str = concatenate("hello", "helloo", "hellooo");
    std::cout << str.value() << std::endl;
    std::cout << str.size() << std::endl;
}
