#pragma once

template <std::size_t LenA, std::size_t LenB>
constexpr auto concatenate(const char (&a)[LenA], const char (&b)[LenB]) {
    constexpr std::size_t n = kSum<LenA, LenB>;
    using TypeA = decltype(StringLiteral{a});
    using TypeB = decltype(StringLiteral{b});
    return cstring<n, TypeA, TypeB>(
        StringLiteral{a},
        StringLiteral{b}
    );
}

template <std::size_t LenA, std::size_t LenB, std::size_t LenC>
constexpr auto concatenate(const char (&a)[LenA], const char (&b)[LenB], const char (&c)[LenC]) {
    constexpr std::size_t n = kSum<LenA, LenB, LenC>;
    using TypeA = decltype(StringLiteral{a});
    using TypeB = decltype(StringLiteral{b});
    using TypeC = decltype(StringLiteral{c});
    return cstring<n, TypeA, TypeB, TypeC>(
        StringLiteral{a},
        StringLiteral{b},
        StringLiteral{c}
    );
}

template <std::size_t LenA, std::size_t LenB, std::size_t LenC, std::size_t LenD>
constexpr auto concatenate(const char (&a)[LenA], const char (&b)[LenB], const char (&c)[LenC], const char (&d)[LenD]) {
    constexpr std::size_t n = kSum<LenA, LenB, LenC, LenD>;
    using TypeA = decltype(StringLiteral{a});
    using TypeB = decltype(StringLiteral{b});
    using TypeC = decltype(StringLiteral{c});
    using TypeD = decltype(StringLiteral{d});
    return cstring<n, TypeA, TypeB, TypeC, TypeD>(
        StringLiteral{a},
        StringLiteral{b},
        StringLiteral{c},
        StringLiteral{d}
    );
}

template <std::size_t LenA, std::size_t LenB, std::size_t LenC, std::size_t LenD, std::size_t LenE>
constexpr auto concatenate(const char (&a)[LenA], const char (&b)[LenB], const char (&c)[LenC], const char (&d)[LenD], const char (&e)[LenE]) {
    constexpr std::size_t n = kSum<LenA, LenB, LenC, LenD, LenE>;
    using TypeA = decltype(StringLiteral{a});
    using TypeB = decltype(StringLiteral{b});
    using TypeC = decltype(StringLiteral{c});
    using TypeD = decltype(StringLiteral{d});
    using TypeE = decltype(StringLiteral{e});
    return cstring<n, TypeA, TypeB, TypeC, TypeD, TypeE>(
        StringLiteral{a},
        StringLiteral{b},
        StringLiteral{c},
        StringLiteral{d},
        StringLiteral{e}
    );
}

#if defined(__GNUG__)

template <std::size_t LenA, std::size_t LenB>
constexpr auto concatenate(const StringLiteral<LenA> &a, const StringLiteral<LenB> &b) {
    constexpr std::size_t n = kSum<a, b>;
    using TypeA = decltype(a);
    using TypeB = decltype(b);
    return cstring<n, TypeA, TypeB>(a, b);
}

template <std::size_t LenA, std::size_t LenB, std::size_t LenC>
constexpr auto concatenate(const StringLiteral<LenA> &a, const StringLiteral<LenB> &b, const StringLiteral<LenC> &c) {
    constexpr std::size_t n = kSum<a, b, c>;
    using TypeA = decltype(a);
    using TypeB = decltype(b);
    using TypeC = decltype(c);
    return cstring<n, TypeA, TypeB, TypeC>(a, b, c);
}

template <std::size_t LenA, std::size_t LenB, std::size_t LenC, std::size_t LenD>
constexpr auto concatenate(const StringLiteral<LenA> &a, const StringLiteral<LenB> &b, const StringLiteral<LenC> &c, const StringLiteral<LenD> &d) {
    constexpr std::size_t n = kSum<a, b, c, d>;
    using TypeA = decltype(a);
    using TypeB = decltype(b);
    using TypeC = decltype(c);
    using TypeD = decltype(d);
    return cstring<n, TypeA, TypeB, TypeC, TypeD>(a, b, c, d);
}

template <std::size_t LenA, std::size_t LenB, std::size_t LenC, std::size_t LenD, std::size_t LenE>
constexpr auto concatenate(const StringLiteral<LenA> &a, const StringLiteral<LenB> &b, const StringLiteral<LenC> &c, const StringLiteral<LenD> &d, const StringLiteral<LenE> &e) {
    constexpr std::size_t n = kSum<a, b, c, d, e>;
    using TypeA = decltype(a);
    using TypeB = decltype(b);
    using TypeC = decltype(c);
    using TypeD = decltype(d);
    using TypeE = decltype(e);
    return cstring<n, TypeA, TypeB, TypeC, TypeD, TypeE>(a, b, c, d, e);
}

/// Clang does not allow parameters to be used as template arguments to kSum because it deems them as non-constant expressions
/// The Clang implementation below can be used for GCC, however leaving the GCC implementation to show their differences
#elif defined(__clang__)

template <typename LiteralA, typename LiteralB>
constexpr auto concatenate(const LiteralA &a, const LiteralB &b) {
    constexpr std::size_t n = LiteralA::kSize + LiteralB::kSize;
    return cstring<n, LiteralA, LiteralB>(a, b);
}

template <typename LiteralA, typename LiteralB, typename LiteralC>
constexpr auto concatenate(const LiteralA &a, const LiteralB &b, const LiteralC &c) {
    constexpr std::size_t n = LiteralA::kSize + LiteralB::kSize + LiteralC::kSize;
    return cstring<n, LiteralA, LiteralB, LiteralC>(a, b, c);
}

template <typename LiteralA, typename LiteralB, typename LiteralC, typename LiteralD>
constexpr auto concatenate(const LiteralA &a, const LiteralB &b, const LiteralC &c, const LiteralD &d) {
    constexpr std::size_t n = LiteralA::kSize + LiteralB::kSize + LiteralC::kSize + LiteralD::kSize;
    return cstring<n, LiteralA, LiteralB, LiteralC, LiteralD>(a, b, c, d);
}

template <typename LiteralA, typename LiteralB, typename LiteralC, typename LiteralD, typename LiteralE>
constexpr auto concatenate(const LiteralA &a, const LiteralB &b, const LiteralC &c, const LiteralD &d, const LiteralE &e) {
    constexpr std::size_t n = LiteralA::kSize + LiteralB::kSize + LiteralC::kSize + LiteralD::kSize + LiteralE::kSize;
    return cstring<n, LiteralA, LiteralB, LiteralC, LiteralD, LiteralE>(a, b, c, d, e);
}

#endif
