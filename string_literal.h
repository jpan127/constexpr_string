#pragma once

#include <cstddef>
#include <type_traits>

class LiteralBase {
};

template <std::size_t NPlus1>
class StringLiteral : public LiteralBase {
  public:
    static constexpr std::size_t Size = NPlus1 - 1;

    constexpr StringLiteral(const char (&buffer)[NPlus1]) : buffer_(buffer){};

    constexpr char operator[](const std::size_t index) const {
        return buffer_[index];
    }

    constexpr std::size_t size() const {
        return Size;
    }

    constexpr operator std::size_t() const {
        return Size;
    }

  private:
    const char (&buffer_)[NPlus1];
};

/// \note In C++20 this quality satisfaction will allow it to be a templateable non-type
static_assert(std::is_literal_type<decltype(StringLiteral{"test"})>::value);
