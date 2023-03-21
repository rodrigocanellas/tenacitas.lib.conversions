#include <cstdint>
#include <iostream>
#include <limits>
#include <optional>

#include <tenacitas.lib.conversions/alg/cvt.h>
#include <tenacitas.lib.program/alg/options.h>
#include <tenacitas.lib.test/alg/tester.h>

using namespace tenacitas::lib;
using namespace tenacitas::lib::conversions;

struct test000 {
  static std::string desc() { return "internal::to_int<uint8_t>(\"256\")"; }

  bool operator()(const program::alg::options &) {

    using namespace alg::internal;

    std::optional<uint8_t> _maybe{to_int<uint8_t>("256")};

    if (_maybe) {
      std::cerr << "It should not have converted, but it did to "
                << _maybe.value() << '\n';
      return false;
    }

    std::cerr << "It did not convert, as expected\n";
    return true;
  }
};

struct test001 {
  static std::string desc() { return "internal::to_int<uint8_t>(\"345\")"; }

  bool operator()(const program::alg::options &) {

    using namespace alg::internal;

    auto _maybe{to_int<uint8_t>("345")};

    if (_maybe) {
      std::cerr << "It should not have converted, but it did to "
                << _maybe.value() << '\n';
      return false;
    }

    std::cerr << "It did not convert, as expected\n";

    return true;
  }
};

struct test002 {
  static std::string desc() { return "internal::to_int<uint8_t>(\"255\")"; }

  bool operator()(const program::alg::options &) {

    using namespace alg::internal;

    auto _maybe{to_int<uint8_t>("255")};

    if (!_maybe) {
      std::cerr << "It did convert, but it should have\n";
      return false;
    }

    auto _i{std::move(_maybe.value())};
    if (_i != 255) {
      std::cerr << "It converted to " << static_cast<uint16_t>(_i)
                << ", but it should have converted to 255z\n";
      return false;
    }

    std::cerr << "It converted to " << static_cast<int16_t>(_maybe.value())
              << ", as expected\n";

    return true;
  }
};

struct test003 {
  static std::string desc() { return "internal::to_int<uint8_t>(\"1234\")"; }

  bool operator()(const program::alg::options &) {

    using namespace alg::internal;

    auto _maybe{to_int<uint8_t>("1234")};

    if (_maybe) {
      std::cerr << "It should not have converted, but it did to "
                << _maybe.value() << '\n';
      return false;
    }

    std::cerr << "It did not convert, as expected\n";

    return true;
  }
};

int main(int argc, char **argv) {
  test::alg::tester _test(argc, argv);

  run_test(_test, test000);
  run_test(_test, test001);
  run_test(_test, test002);
  run_test(_test, test003);
}
