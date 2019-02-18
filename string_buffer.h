#pragma once

#include "string_literal.h"

#include <array>

template <std::size_t N, typename ... Literal>
class StringBuffer {
  public:
    /// Size of the buffer
    static constexpr std::size_t Size = N;

    /// Constructor without delimiter
    constexpr StringBuffer(Literal ... literals) {
        constexpr auto copy = [](auto &buffer, const auto &other, auto &index) {
            for (std::size_t ii = 0; ii < other.size(); ii++) {
                buffer[index++] = other[ii];
            }
        };

        (copy(buffer_, literals, index_), ...);

        // Null terminate
        buffer_[index_] = '\0';
    }

    /// Constructor with delimiter
    constexpr StringBuffer(const char delimiter, Literal ... literals) {
        constexpr auto copy = [](auto &buffer, const char delimiter, const auto &other, auto &index) {
            for (std::size_t ii = 0; ii < other.size(); ii++) {
                buffer[index++] = other[ii];
            }

            buffer[index++] = delimiter;
        };

        (copy(buffer_, delimiter, literals, index_), ...);

        // Null terminate and replace last delimiter
        buffer_[index_ - 1] = '\0';
    }

    /// Returns c string
    constexpr const char *value() const {
        return buffer_.data();
    }

    /// Returns size of string
    constexpr std::size_t size() const {
        return Size;
    }

  private:
    /// Underlying buffer
    std::array<char, N + 2> buffer_{};

    /// Tracks the indice of the buffer on construction
    std::size_t index_ = 0;
};
