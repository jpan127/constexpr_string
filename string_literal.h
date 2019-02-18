#pragma once

#include <cstddef>
#include <type_traits>

class LiteralBase {
};

template <std::size_t NPlus1>
class StringLiteral : public LiteralBase {
  public:
    static constexpr std::size_t kSize = NPlus1 - 1;

    constexpr StringLiteral(const char (&buffer)[NPlus1]) : buffer_(buffer){};

    constexpr char operator[](const std::size_t index) const {
        return buffer_[index];
    }

    constexpr std::size_t size() const {
        return kSize;
    }

    constexpr operator std::size_t() const {
        return kSize;
    }

  private:
    const char (&buffer_)[NPlus1];
};

class SL : public LiteralBase {
  public:
    template <std::size_t NPlus1>
    constexpr SL(const char (&buffer)[NPlus1]) : buffer_(buffer), size_(NPlus1){};

    constexpr char operator[](const std::size_t index) const {
        return buffer_[index];
    }

    constexpr std::size_t size() const {
        return size_;
    }

    constexpr operator std::size_t() const {
        return size_;
    }

  private:
    const char *buffer_;
    const std::size_t size_;
};


/// \note In C++20 this quality satisfaction will allow it to be a templateable non-type
static_assert(std::is_literal_type<decltype(StringLiteral{"test"})>::value);
static_assert(std::is_literal_type<decltype(SL{"test"})>::value);
