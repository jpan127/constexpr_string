#pragma once

#include "string_literal.h"

#include <array>

template <std::size_t LengthA, std::size_t LengthB>
class constexpr_string {
  public:
    static constexpr std::size_t kSize = LengthA + LengthB;

    /// Constructor
    constexpr constexpr_string(const StringLiteral<LengthA> &a,
                               const StringLiteral<LengthB> &b) {

        constexpr auto copy = [](auto &buffer, const auto &other, const std::size_t begin, const std::size_t end) {
            for (std::size_t ii = begin; ii < begin + end; ii++) {
                buffer[ii] = other[ii - begin];
            }
        };

        // Copy over A
        copy(buffer_, a, 0, LengthA);

        // Copy over B
        copy(buffer_, b, LengthA, LengthB);

        // Null terminate
        buffer_[LengthA + LengthB] = '\0';
    }

    constexpr const char *value() const {
        return buffer_.data();
    }

  private:
    std::array<char, kSize + 1> buffer_{};
};

template <std::size_t LengthA, std::size_t LengthB>
constexpr constexpr_string<LengthA, LengthB> operator+(const StringLiteral<LengthA> &a,
                                                       const StringLiteral<LengthB> &b) {
    return constexpr_string<LengthA, LengthB>(a, b);
}

// void test() {
//     constexpr StringLiteral h = "hello ";
//     constexpr StringLiteral w =  "world";

//     constexpr constexpr_string kString3(h, w);
//     constexpr constexpr_string kString4 = h + w;

//     std::cout << kString3.kSize << " : " << kString3.value() << std::endl;
//     std::cout << kString4.kSize << " : " << kString4.value() << std::endl;
// }
