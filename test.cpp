#include "cexpr_string.h"

#include <string.h>

#include <cassert>
#include <iostream>

int main() {
    using namespace cexpr_string;

    {
        constexpr auto concatenated = concatenate("hello", "this", "world", "is", "great");
        std::cout << concatenated.value() << std::endl;
        std::cout << concatenated.size() << std::endl;
        assert(std::string(concatenated.value()) == "hellothisworldisgreat");
        assert(concatenated.size() == strlen("hellothisworldisgreat"));
    }

    {
        constexpr auto joined = join_with_whitespace("hello", "this", "world", "is", "great");
        std::cout << joined.value() << std::endl;
        std::cout << joined.size() << std::endl;
        assert(std::string(joined.value()) == "hello this world is great");
        assert(joined.size() == strlen("hello this world is great"));
    }

    {
        constexpr auto joined = join_with_underscore("hello", "this", "world", "is", "great");
        std::cout << joined.value() << std::endl;
        std::cout << joined.size() << std::endl;
        assert(std::string(joined.value()) == "hello_this_world_is_great");
        assert(joined.size() == strlen("hello_this_world_is_great"));
    }

    {
        constexpr auto joined = join_with_comma("hello", "this", "world", "is", "great");
        std::cout << joined.value() << std::endl;
        std::cout << joined.size() << std::endl;
        assert(std::string(joined.value()) == "hello,this,world,is,great");
        assert(joined.size() == strlen("hello,this,world,is,great"));
    }
}
