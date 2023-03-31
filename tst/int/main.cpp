#include <cstdint>
#include <iostream>
#include <limits>
#include <optional>

#include <tenacitas.lib.conversions/alg/cvt.h>
#include <tenacitas.lib.program/alg/options.h>
#include <tenacitas.lib.test/alg/tester.h>

using namespace tenacitas::lib;
using namespace tenacitas::lib::conversions::alg;

namespace tenacitas::lib::conversions::tst {
struct a {
  friend std::ostream &operator<<(std::ostream &p_out, const a &) {
    p_out << "a";
    return p_out;
  }
};
struct b {};
} // namespace tenacitas::lib::conversions::tst

struct testNoConversion {
  static std::string desc() { return "test cvt<a>(b)"; }

  bool operator()(program::alg::options &) {
    using namespace tenacitas::lib::conversions::tst;
    b _b;

    auto _maybe{cvt<a>(_b)};

    if (_maybe.first) {
      std::cerr << "It did convert, as it should not, because '"
                << *_maybe.first << '\n';
      return true;
    }

    std::cerr << "It converted to " << _maybe.second << ", but it should not";
    return false;
  }
};

struct test000 {
  static std::string desc() { return "cvt<uint8_t>(\"256\")"; }

  bool operator()(const program::alg::options &) {

    auto _maybe{cvt<uint8_t>("256")};

    if (_maybe.first) {
      std::cerr << "It did not convert, as expected, because '" << *_maybe.first
                << "'\n";
      return true;
    }

    std::cerr << "It should not have converted, but it did to " << _maybe.second
              << '\n';
    return false;
  }
};

struct test001 {
  static std::string desc() { return "cvt<uint8_t>(\"345\")"; }

  bool operator()(const program::alg::options &) {

    auto _maybe{cvt<uint8_t>("345")};

    if (_maybe.first) {
      std::cerr << "It did not convert, as expected, because '" << *_maybe.first
                << "'\n";
      return true;
    }
    std::cerr << "It should not have converted, but it did to " << _maybe.second
              << '\n';
    return false;
  }
};

struct test002 {
  static std::string desc() { return "cvt<uint8_t>(\"255\")"; }

  bool operator()(const program::alg::options &) {

    auto _maybe{cvt<uint8_t>("255")};

    if (_maybe.first) {
      std::cerr << "It did not convert because '" << *_maybe.first
                << "', but it should have\n";
      return false;
    }

    auto _i{std::move(_maybe.second)};
    if (_i != 255) {
      std::cerr << "It converted to " << static_cast<uint16_t>(_i)
                << ", but it should have converted to 255z\n";
      return false;
    }

    std::cerr << "It converted to " << static_cast<uint16_t>(_maybe.second)
              << ", as expected\n";

    return true;
  }
};

struct test003 {
  static std::string desc() { return "cvt<uint8_t>(\"1234\")"; }

  bool operator()(const program::alg::options &) {

    auto _maybe{cvt<uint8_t>("1234")};

    if (_maybe.first) {
      std::cerr << "It did not convert, as expected, because '" << *_maybe.first
                << "'\n";
      return true;
    }
    std::cerr << "It should not have converted, but it did to " << _maybe.second
              << '\n';
    return false;
  }
};

struct test004 {
  static std::string desc() { return "cvt<uint8_t>(\"-12\")"; }

  bool operator()(const program::alg::options &) {

    auto _maybe{cvt<uint8_t>("-12")};

    if (_maybe.first) {
      std::cerr << "It did not convert, as expected, because '" << *_maybe.first
                << "'\n";
      return true;
    }
    std::cerr << "It should not have converted, but it did to " << _maybe.second
              << '\n';
    return false;
  }
};

struct test005 {
  static std::string desc() { return "cvt<uint8_t>(\"-1234\")"; }

  bool operator()(const program::alg::options &) {

    auto _maybe{cvt<uint8_t>("-1234")};

    if (_maybe.first) {
      std::cerr << "It did not convert, as expected, because '" << *_maybe.first
                << "'\n";
      return true;
    }
    std::cerr << "It should not have converted, but it did to " << _maybe.second
              << '\n';
    return false;
  }
};

struct test006 {
  static std::string desc() { return "cvt<uint8_t>(\"-8\")"; }

  bool operator()(const program::alg::options &) {

    auto _maybe{cvt<uint8_t>("-8")};

    if (_maybe.first) {
      std::cerr << "It did not convert, as expected, because '" << *_maybe.first
                << "'\n";
      return true;
    }
    std::cerr << "It should not have converted, but it did to " << _maybe.second
              << '\n';
    return false;
  }
};

struct test007 {
  static std::string desc() { return "cvt<uint8_t>(\"0000122\")"; }

  bool operator()(const program::alg::options &) {

    auto _maybe{cvt<uint8_t>("0000122")};

    if (_maybe.first) {
      std::cerr << "It should have converted, but it did because '"
                << *_maybe.first << "'\n";
      return false;
    }

    if (_maybe.second != 122) {
      std::cerr << "It should have converted to 122, but it converted to "
                << static_cast<uint16_t>(_maybe.second) << '\n';
      return false;
    }

    std::cerr << "It converted to " << static_cast<uint16_t>(_maybe.second)
              << ", as it should" << '\n';
    return true;
  }
};

struct test008 {
  static std::string desc() { return "cvt<uint8_t>(\"2.4\")"; }

  bool operator()(const program::alg::options &) {

    auto _maybe{cvt<uint8_t>("2.4")};

    if (_maybe.first) {
      std::cerr << "It did not convert, as it should, because '"
                << *_maybe.first << "'\n";
      return true;
    }

    std::cerr << "It converte to " << static_cast<uint16_t>(_maybe.second)
              << ", but it should not" << '\n';
    return false;
  }
};

struct test009 {
  static std::string desc() { return "cvt<uint8_t>(\"1c2\")"; }

  bool operator()(const program::alg::options &) {

    auto _maybe{cvt<uint8_t>("1c2")};

    if (_maybe.first) {
      std::cerr << "It did not convert, as it should, because '"
                << *_maybe.first << "'\n";
      return true;
    }

    std::cerr << "It converted to " << static_cast<uint16_t>(_maybe.second)
              << ", but it should not" << '\n';
    return false;
  }
};

struct test010 {
  static std::string desc() { return "cvt<int8_t>(\"-128\")"; }

  bool operator()(const program::alg::options &) {

    auto _maybe{cvt<int8_t>("-128")};

    if (_maybe.first) {
      std::cerr << "It did not convert because '" << *_maybe.first
                << "', but it should have\n";
      return false;
    }

    auto _i{std::move(_maybe.second)};
    if (_i != -128) {
      std::cerr << "It converted to " << static_cast<int16_t>(_i)
                << ", but it should have converted to -128\n";
      return false;
    }

    std::cerr << "It converted to " << static_cast<int16_t>(_maybe.second)
              << ", as expected\n";
    return true;
  }
};

struct test011 {
  static std::string desc() { return "cvt<int8_t>(\"-129\")"; }

  bool operator()(const program::alg::options &) {

    auto _maybe{cvt<int8_t>("-129")};
    if (_maybe.first) {
      std::cerr << "It did not convert, as expected, because '" << *_maybe.first
                << "'\n";
      return true;
    }

    std::cerr << "It should not have converted, but it did to " << _maybe.second
              << '\n';
    return false;
  }
};

struct test012 {
  static std::string desc() { return "cvt<int8_t>(\"127\")"; }

  bool operator()(const program::alg::options &) {

    auto _maybe{cvt<int8_t>("127")};

    if (_maybe.first) {
      std::cerr << "It did not convert because '" << *_maybe.first
                << "', but it should have\n";
      return false;
    }

    auto _i{std::move(_maybe.second)};
    if (_i != 127) {
      std::cerr << "It converted to " << static_cast<int16_t>(_i)
                << ", but it should have converted to 127\n";
      return false;
    }

    std::cerr << "It converted to " << static_cast<int16_t>(_maybe.second)
              << ", as expected\n";
    return true;
  }
};

struct test013 {
  static std::string desc() { return "cvt<int8_t>(\"128\")"; }

  bool operator()(const program::alg::options &) {

    auto _maybe{cvt<int8_t>("128")};
    if (_maybe.first) {
      std::cerr << "It did not convert, as expected, because '" << *_maybe.first
                << "'\n";
      return true;
    }

    std::cerr << "It should not have converted, but it did to "
              << static_cast<int16_t>(_maybe.second) << '\n';
    return false;
  }
};

struct test014 {
  static std::string desc() { return "cvt<uint8_t>(\"0xD3\")"; }

  bool operator()(const program::alg::options &) {

    auto _maybe{cvt<uint8_t>("0xD3")};
    if (_maybe.first) {
      std::cerr << "It did not convert, but it should have, because '"
                << *_maybe.first << "'\n";
      return false;
    }

    if (_maybe.second != 0xD3) {
      std::cerr << "It converted to " << static_cast<int16_t>(_maybe.second)
                << ", but it should have converted to 0xD3\n";
    }

    std::cerr << "It converted to " << static_cast<int16_t>(_maybe.second)
              << ", as expected\n";
    return true;
  }
};

struct test015 {
  static std::string desc() { return "cvt<uint8_t>(\"0xD302\")"; }

  bool operator()(const program::alg::options &) {

    auto _maybe{cvt<uint8_t>("0xD302")};
    if (_maybe.first) {
      std::cerr << "It did not convert, as it should, because '"
                << *_maybe.first << "'\n";
      return true;
    }

    std::cerr << "It converted to " << static_cast<int16_t>(_maybe.second)
              << ", but is should not have\n";
    return false;
  }
};

int main(int argc, char **argv) {
  test::alg::tester _test(argc, argv);

  run_test(_test, testNoConversion);
  run_test(_test, test000);
  run_test(_test, test001);
  run_test(_test, test002);
  run_test(_test, test003);
  run_test(_test, test004);
  run_test(_test, test005);
  run_test(_test, test006);
  run_test(_test, test007);
  run_test(_test, test008);
  run_test(_test, test009);
  run_test(_test, test010);
  run_test(_test, test011);
  run_test(_test, test012);
  run_test(_test, test013);
  //  run_test(_test, test014);
  //  run_test(_test, test015);
}
