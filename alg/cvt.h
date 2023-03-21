#ifndef TENACITAS_LIB_CONVERSIONS_ALG_INT_H
#define TENACITAS_LIB_CONVERSIONS_ALG_INT_H

/// \copyright This file is under GPL 3 license. Please read the \p LICENSE file
/// at the root of \p tenacitas directory

/// \author Rodrigo Canellas - rodrigo.canellas at gmail.com

#include <cstring>
#include <limits>
#include <optional>
#include <stdexcept>
#include <typeinfo>

namespace tenacitas::lib::conversions::alg {

/// \brief Basic type conversion template function
template <typename t_to, typename t_from>
std::optional<t_to> cnvt(t_from /*p_from*/) {
  throw std::runtime_error("no conversion defined from '" +
                           std::string{typeid(t_from).name()} + "' to '" +
                           std::string{typeid(t_to).name()} + "'");
  return {};
}

namespace internal {

// bool overflow(uint8_t p_sizeof, const char *p_str) {
//   static constexpr uint8_t max_length_p_str_8{3};
//   static constexpr uint8_t max_length_p_str_16{5};
//   static constexpr uint8_t max_length_p_str_32{10};
//   static constexpr uint8_t max_length_p_str_64{20};

//  const auto p_size_of{std::strlen(p_str)};

//  if ((p_sizeof == 8) && (p_size_of > max_length_p_str_8)) {
//    return true;
//  }

//  if ((p_size_of == 16) && (p_size_of > max_length_p_str_16)) {
//    return true;
//  }

//  if ((p_size_of == 32) && (p_size_of > max_length_p_str_32)) {
//    return true;
//  }

//  if ((p_size_of == 64) && (p_size_of > max_length_p_str_64)) {
//    return true;
//  }
//  return false;
//}

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

template <typename t_to> std::optional<t_to> to_uint(const char *p_str) {
  using _next_int = typename next_int<sizeof(t_to), false>::type;

  t_to _result = 0;

  while (*p_str) {
    if (std::isdigit(static_cast<uint8_t>(*p_str)) == 0) {
      return {};
    }

    const auto _prod{static_cast<_next_int>(_result * 10)};

    if ((_result != 0) &&
        ((_prod == 0) || (_prod > std::numeric_limits<t_to>::max()))) {
      return {};
    }

    _result = _prod;

    const auto _sum{
        static_cast<t_to>(_result + static_cast<uint8_t>(*p_str - '0'))};

    if ((_result != 0) && (_sum == 0)) {
      return {};
    }

    _result = _sum;

    ++p_str;
  }
  return _result;
}

template <typename t_to>
std::optional<t_to> to_sint(const char *p_str, bool p_negative = false) {

  t_to _result = 0;
  while (*p_str) {
    if (std::isdigit(static_cast<unsigned char>(*p_str)) == 0) {
      return {};
    }

    uint8_t _digit = *p_str - '0';

    if (overflow<t_to>(static_cast<int64_t>(_result * 10))) {
      return {};
    }

    _result *= 10;

    if (overflow<t_to>(static_cast<int64_t>(_result - _digit))) {
      return {};
    }

    _result -= _digit; // calculate in negatives to support INT_MIN, LONG_MIN,..

    ++p_str;
  }
  return p_negative ? _result : -_result;
}

template <typename t_to> std::optional<t_to> to_int(const char *p_str) {

  if constexpr (!std::is_integral_v<t_to>) {
    return {};
  }
  if constexpr (std::is_floating_point_v<t_to>) {
    return {};
  }

  //  if (overflow(sizeof(t_to), p_str)) {
  //    return {};
  //  }

  bool _negative = false;

  if (*p_str == '+') {
    ++p_str;
  } else if (*p_str == '-') {
    ++p_str;
    _negative = true;
  }

  constexpr bool _unsigned{std::is_unsigned_v<t_to>};

  if (_negative && _unsigned) {
    return {};
  }

  if (_unsigned) {
    return to_uint<t_to>(p_str);
  }
  return to_sint<t_to>(p_str, _negative);
}

} // namespace internal

template <>
std::optional<uint8_t> cnvt<uint8_t, const char *>(const char *p_from) {
  return internal::to_int<uint8_t>(p_from);
}

template <> std::optional<uint16_t> cnvt(const char *p_from) {
  return internal::to_int<uint16_t>(p_from);
}

template <> std::optional<uint32_t> cnvt(const char *p_from) {
  return internal::to_int<uint32_t>(p_from);
}

template <> std::optional<uint64_t> cnvt(const char *p_from) {
  return internal::to_int<uint64_t>(p_from);
}

template <>
std::optional<int8_t> cnvt<int8_t, const char *>(const char *p_from) {
  return internal::to_int<int8_t>(p_from);
}

template <> std::optional<int16_t> cnvt(const char *p_from) {
  return internal::to_int<int16_t>(p_from);
}

template <> std::optional<int32_t> cnvt(const char *p_from) {
  return internal::to_int<int32_t>(p_from);
}

template <> std::optional<int64_t> cnvt(const char *p_from) {
  return internal::to_int<int64_t>(p_from);
}

} // namespace tenacitas::lib::conversions::alg

#endif
