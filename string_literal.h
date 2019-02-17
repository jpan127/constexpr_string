#pragma once

#include <cstddef>

template <std::size_t NPlus1>
class StringLiteral {
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
