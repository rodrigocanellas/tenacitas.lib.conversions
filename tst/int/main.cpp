#include <cstdint>
#include <iostream>
#include <limits>
#include <optional>

#include <tenacitas.lib.conversions/alg/int.h>
#include <tenacitas.lib.program/alg/options.h>
#include <tenacitas.lib.test/alg/tester.h>

using namespace tenacitas::lib;
using namespace tenacitas::lib::conversions;

struct test000 {
  static std::string desc() { return "internal::to_int<uint8_t>(\"256\")"; }

  bool operator()(const program::alg::options &) {

    using namespace alg::internal;

    auto _maybe{to_int<uint8_t>("256")};

    if (_maybe) {
      std::cout << "It should not have converted, but it did to "
                << _maybe.value() << '\n';
      return false;
    }

    std::cout << "It did not convert, as expected\n";
    return true;
  }
};

struct test001 {
  static std::string desc() { return "internal::to_int<uint8_t>(\"345\")"; }

  bool operator()(const program::alg::options &) {

    using namespace alg::internal;

    auto _maybe{to_int<uint8_t>("345")};

    if (_maybe) {
      std::cout << "It should not have converted, but it did to "
                << _maybe.value() << '\n';
      return false;
    }

    std::cout << "It did not convert, as expected\n";

    //    std::cout << "could not convert, as it should not" << std::endl;
    //    if (!_maybe) {
    //      std::cout << "should have converted, but it did not\n";
    //      return false;
    //    }

    //    std::cout << "i = " << static_cast<int16_t>(_maybe.value()) <<
    //    std::endl;
    return true;
  }
};

struct test002 {
  static std::string desc() { return "internal::to_int<uint8_t>(\"255\")"; }

  bool operator()(const program::alg::options &) {

    using namespace alg::internal;

    auto _maybe{to_int<uint8_t>("255")};

    if (!_maybe) {
      std::cout << "It did convert, but it should have\n";
      return false;
    }

    auto _i{std::move(_maybe.value())};
    if (_i != 255) {
      std::cout << "It converted to " << static_cast<uint16_t>(_i)
                << ", but it should have converted to 255z\n";
      return false;
    }

    std::cout << "It converted to " << static_cast<int16_t>(_maybe.value())
              << ", as expected\n";

    return true;
  }
};

int main(int argc, char **argv) {
  test::alg::tester _test(argc, argv);

  run_test(_test, test000);
  run_test(_test, test001);
  run_test(_test, test002);
}
