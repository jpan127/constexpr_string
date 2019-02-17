
    /// \note It is not possible for N to be computed in constexpr since the inputs have the ability
    ///       to not be constant expressions
    #if 0
    template <typename ... Literal>
    constexpr auto make_cstring(Literal ... literals) {
        constexpr std::size_t N = total_size<Literal...>(std::forward<Literal>(literals)...);
        return cstring<N, Literal...>(std::forward<Literal>(literals)...);
    }
    #endif

    // void test_make_cstring() {
    //     constexpr StringLiteral h = "hello ";
    //     constexpr StringLiteral w =  "world";

    //     constexpr auto kCString = make_cstring<total_size(h, w)>(h, w);
    //     std::cout << kCString.value() << std::endl;
    //     std::cout << kCString.kSize << std::endl;
    // }

    template <typename TupleType, std::size_t ... Index>
    constexpr std::size_t total_size(TupleType literals, std::index_sequence<Index...>) {
        constexpr auto total_size = [](auto literal) { return literal.kSize; };
        return (total_size(std::get<Index>(literals)), ...);
        // return total_size(std::get<Sequence>(std::forward<TupleType>(literals)));
    }

    // void test_initializer_list() {
    //     constexpr StringLiteral h = "hello ";
    //     constexpr StringLiteral w =  "world";

    //     constexpr auto kStrings = std::make_tuple(h, w);

    //     const auto size = total_size<decltype(kStrings)>(kStrings);
    // }

    // template <typename FirstType, typename ... Literal>
    // constexpr std::size_t total_size(FirstType first, Literal ... literals) {
    //     constexpr auto total_size = [](auto literal) { return literal.kSize; };
    //     return first.kSize + total_size(literals...);
    // }

    // void test_total_size() {
    //     constexpr StringLiteral test1 = "hello ";
    //     constexpr StringLiteral test2 = "hello  ";
    //     constexpr auto size = total_size(test1, test2);
    //     assert(size == 12);
    // }

