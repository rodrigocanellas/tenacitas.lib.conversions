#ifndef TENACITAS_LIB_CONVERSIONS_ALG_INT_H
#define TENACITAS_LIB_CONVERSIONS_ALG_INT_H

/// \copyright This file is under GPL 3 license. Please read the \p LICENSE file
/// at the root of \p tenacitas directory

/// \author Rodrigo Canellas - rodrigo.canellas at gmail.com

#include <optional>
#include <stdexcept>
#include <typeinfo>

namespace tenacitas::lib::conversions::alg {

/// \brief Basic type conversion template function
template <typename t_to, typename t_from> std::optional<t_to> cnvt(t_from);

} // namespace tenacitas::lib::conversions::alg

template <typename t_to, typename t_from>
std::optional<t_to> tenacitas::lib::conversions::alg::cnvt(t_from) {
  throw std::runtime_error("no conversion defined from '" +
                           std::string{typeid(t_from).name()} + "' to '" +
                           std::string{typeid(t_to).name()} + "'");
}

#endif
