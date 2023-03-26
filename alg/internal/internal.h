#ifndef TENACITAS_LIB_CONVERSIONS_ALG_INTERNAL_INTERNAL_H
#define TENACITAS_LIB_CONVERSIONS_ALG_INTERNAL_INTERNAL_H

/// \copyright This file is under GPL 3 license. Please read the \p LICENSE file
/// at the root of \p tenacitas directory

/// \author Rodrigo Canellas - rodrigo.canellas at gmail.com

#include <cctype>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <limits>
#include <optional>

namespace tenacitas::lib::conversions::alg::internal {

template <typename t_to> bool overflow(int64_t p_val) {
  if constexpr (sizeof(t_to) < 8) {
    if (p_val < std::numeric_limits<t_to>::min()) {
      return true;
    }
  } else if (static_cast<t_to>(p_val) <= std::numeric_limits<t_to>::max()) {
    return true;
  }
  return false;
}

template <size_t int_size, bool is_signed> struct next_int;

template <> struct next_int<1, false> { using type = uint16_t; };

template <> struct next_int<2, false> { using type = uint32_t; };

template <> struct next_int<4, false> { using type = uint64_t; };

template <> struct next_int<8, false> { using type = uint64_t; };

template <> struct next_int<1, true> { using type = int16_t; };

template <> struct next_int<2, true> { using type = int32_t; };

template <> struct next_int<4, true> { using type = int64_t; };

template <> struct next_int<8, true> { using type = int64_t; };

template <typename t_to>
std::optional<t_to> to_uint(const char *p_begin, const char *p_end) {
  using _next_int = typename next_int<sizeof(t_to), false>::type;

  t_to _result = 0;

  const char *_ite = p_begin;

  while (_ite != p_end) {
    if (std::isdigit(static_cast<uint8_t>(*_ite)) == 0) {
      return {};
    }

    const auto _prod{static_cast<_next_int>(_result * 10)};

    if ((_result != 0) &&
        ((_prod == 0) || (_prod > std::numeric_limits<t_to>::max()))) {
      return {};
    }

    _result = _prod;

    const auto _sum{
        static_cast<t_to>(_result + static_cast<uint8_t>(*_ite - '0'))};

    if ((_result != 0) && (_sum == 0)) {
      return {};
    }

    _result = _sum;

    ++_ite;
  }
  return _result;
}

template <typename t_to>
std::optional<t_to> to_sint(const char *p_begin, const char *p_end,
                            bool p_negative = false) {

  t_to _result = 0;
  const char *_ite{p_begin};
  while (_ite != p_end) {
    if (std::isdigit(static_cast<unsigned char>(*_ite)) == 0) {
      return {};
    }

    uint8_t _digit = *_ite - '0';

    if (overflow<t_to>(static_cast<int64_t>(_result * 10))) {
      return {};
    }

    _result *= 10;

    if (overflow<t_to>(static_cast<int64_t>(_result - _digit))) {
      return {};
    }

    _result -= _digit; // calculate in negatives to support INT_MIN, LONG_MIN,..

    ++_ite;
  }
  return p_negative ? _result : -_result;
}

} // namespace tenacitas::lib::conversions::alg::internal

#endif
