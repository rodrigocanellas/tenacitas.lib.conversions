#ifndef TENACITAS_LIB_CONVERSIONS_TYP_BASE_H
#define TENACITAS_LIB_CONVERSIONS_TYP_BASE_H

/// \copyright This file is under GPL 3 license. Please read the \p LICENSE file
/// at the root of \p tenacitas directory

/// \author Rodrigo Canellas - rodrigo.canellas at gmail.com

#include <cstdint>

namespace tenacitas::lib::conversions::typ {
enum class base : uint8_t { b2 = 2, b8 = 8, b10 = 10, b16 = 16 };
}

#endif
