#include <cstdint>
#include <iostream>
#include <limits>
#include <optional>
#include <sstream>

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

// struct testNoConversion {
//   static std::string desc() { return "test cvt<a>(b)"; }

//  bool operator()(program::alg::options &) {
//    using namespace tenacitas::lib::conversions::tst;
//    b _b;

//    auto _maybe{cvt<a>(_b)};

//    if (_maybe.first) {
//      std::cerr << "It did convert, as it should not, because '"
//                << *_maybe.first << '\n';
//      return true;
//    }

//    std::cerr << "It converted to " << _maybe.second << ", but it should not";
//    return false;
//  }
//};

template <typename t_int> struct test_unsigned_int_max {
  static std::string desc() {
    std::stringstream _stream;

    _stream << "cvt<" << internal::int_name<t_int>() << ">(\""
            << static_cast<uint64_t>(std::numeric_limits<t_int>::max())
            << "\"), which is std::numeric_limits<"
            << internal::int_name<t_int>() << ">::max()";
    return _stream.str();
  }

  bool operator()(const program::alg::options &) {

    std::stringstream _stream;
    _stream << static_cast<uint64_t>(std::numeric_limits<t_int>::max());

    std::string _value{_stream.str()};

    auto _maybe{cvt<t_int>(_value)};
    if (_maybe.first) {
      std::cerr << "It did not convert, but it should have, because '"
                << *_maybe.first << "'\n";
      return false;
    }

    if (_maybe.second != std::numeric_limits<t_int>::max()) {
      std::cerr << "It converted to " << static_cast<uint64_t>(_maybe.second)
                << ", but it should have converted to " << _value << "\n";
    }

    std::cerr << "It converted to " << static_cast<uint64_t>(_maybe.second)
              << ", as expected\n";
    return true;
  }
};

template <typename t_int> struct test_unsigned_int_max_overflow {
  static std::string desc() {

    std::stringstream _stream;

    if constexpr (std::is_same_v<t_int, uint64_t>) {
      _stream << "cvt<" << internal::int_name<t_int>() << ">(\""
              << "18446744073709551616"
              << "\"), which is std::numeric_limits<"
              << internal::int_name<t_int>() << ">::max() + 1";

    } else {
      _stream << "cvt<" << internal::int_name<t_int>() << ">(\""
              << static_cast<uint64_t>(std::numeric_limits<t_int>::max()) + 1
              << "\"), which is std::numeric_limits<"
              << internal::int_name<t_int>() << ">::max() + 1";
    }
    return _stream.str();
  }

  bool operator()(const program::alg::options &) {

    std::stringstream _stream;
    _stream << static_cast<uint64_t>(std::numeric_limits<t_int>::max());

    std::string _value{_stream.str()};

    int8_t _last(_value[_value.size() - 1] - '0');
    ++_last;
    _value[_value.size() - 1] = _last + '0';

    auto _maybe{cvt<t_int>(_value)};
    if (!_maybe.first) {
      std::cerr << "It converted " << static_cast<uint64_t>(_maybe.second)
                << ", but it should not have\n";
      return false;
    }

    std::cerr << "It did not convert, as expected, because '" << *_maybe.first
              << "'\n";
    return true;
  }
};

template <typename t_int> struct test_signed_int_max {
  static std::string desc() {
    std::stringstream _stream;
    _stream << "cvt<" << internal::int_name<t_int>() << ">(\""
            << static_cast<int64_t>(std::numeric_limits<t_int>::max())
            << "\"), which is std::numeric_limits<"
            << internal::int_name<t_int>() << ">::max()";
    return _stream.str();
  }

  bool operator()(const program::alg::options &) {

    std::stringstream _stream;
    _stream << static_cast<int64_t>(std::numeric_limits<t_int>::max());

    std::string _value{_stream.str()};

    auto _maybe{cvt<t_int>(_value)};
    if (_maybe.first) {
      std::cerr << "It did not convert, but it should have, because '"
                << *_maybe.first << "'\n";
      return false;
    }

    if (_maybe.second != std::numeric_limits<t_int>::max()) {
      std::cerr << "It converted to " << static_cast<int64_t>(_maybe.second)
                << ", but it should have converted to " << _value << "\n";
    }

    std::cerr << "It converted to " << static_cast<int64_t>(_maybe.second)
              << ", as expected\n";
    return true;
  }
};

template <typename t_int> struct test_signed_int_max_overflow {
  static std::string desc() {
    std::stringstream _stream;
    if constexpr (std::is_same_v<t_int, int64_t>) {
      _stream << "cvt<" << internal::int_name<t_int>() << ">(\""
              << "9223372036854775808"
              << "\"), which is std::numeric_limits<"
              << internal::int_name<t_int>() << ">::max() + 1";

    } else {
      _stream << "cvt<" << internal::int_name<t_int>() << ">(\""
              << static_cast<uint64_t>(std::numeric_limits<t_int>::max()) + 1
              << "\"), which is std::numeric_limits<"
              << internal::int_name<t_int>() << ">::max() + 1";
    }
    return _stream.str();
  }

  bool operator()(const program::alg::options &) {

    std::stringstream _stream;
    _stream << static_cast<int64_t>(std::numeric_limits<t_int>::max());

    std::string _value{_stream.str()};

    int8_t _last(_value[_value.size() - 1] - '0');
    ++_last;
    _value[_value.size() - 1] = _last + '0';

    auto _maybe{cvt<t_int>(_value)};
    if (!_maybe.first) {
      std::cerr << "It converted to " << static_cast<int64_t>(_maybe.second)
                << ", but it should not have\n";
      return false;
    }

    std::cerr << "It did not convert, as expected, because '" << *_maybe.first
              << "'\n";

    return true;
  }
};

template <typename t_int> struct test_signed_int_min {
  static std::string desc() {
    std::stringstream _stream;
    _stream << "cvt<" << internal::int_name<t_int>() << ">(\""
            << static_cast<int64_t>(std::numeric_limits<t_int>::min())
            << "\"), which is std::numeric_limits<"
            << internal::int_name<t_int>() << ">::min() ";
    return _stream.str();
  }
  bool operator()(const program::alg::options &) {

    std::stringstream _stream;
    _stream << static_cast<int64_t>(std::numeric_limits<t_int>::min());

    std::string _value{_stream.str()};

    auto _maybe{cvt<t_int>(_value)};
    if (_maybe.first) {
      std::cerr << "It did not convert, but it should have, because '"
                << *_maybe.first << "'\n";
      return false;
    }

    if (_maybe.second != std::numeric_limits<t_int>::min()) {
      std::cerr << "It should have converted to " << _value
                << ", but it converted to "
                << static_cast<int64_t>(_maybe.second) << '\n';
      return false;
    }

    std::cerr << "It converted to " << static_cast<int64_t>(_maybe.second)
              << ", as it should \n";
    return true;
  }
};

template <typename t_int> struct test_signed_int_min_underflow {
  static std::string desc() {
    std::stringstream _stream;
    if constexpr (std::is_same_v<t_int, int64_t>) {
      _stream << "cvt<" << internal::int_name<t_int>() << ">(\""
              << "-9223372036854775808"
              << "\"), which is std::numeric_limits<"
              << internal::int_name<t_int>() << ">::min() - 1";
    } else {
      _stream << "cvt<" << internal::int_name<t_int>() << ">(\""
              << static_cast<int64_t>(std::numeric_limits<t_int>::min()) - 1
              << "\"), which is std::numeric_limits<"
              << internal::int_name<t_int>() << ">::min() - 1";
    }
    return _stream.str();
  }

  bool operator()(const program::alg::options &) {

    std::stringstream _stream;
    _stream << static_cast<int64_t>(std::numeric_limits<t_int>::min());

    std::string _value{_stream.str()};

    int8_t _last(_value[_value.size() - 1] - '0');
    ++_last;
    _value[_value.size() - 1] = _last + '0';

    auto _maybe{cvt<t_int>(_value)};
    if (!_maybe.first) {
      std::cerr << "It converted to " << static_cast<int64_t>(_maybe.second)
                << ", but it should not have\n";
      return false;
    }

    std::cerr << "It did not convert, as expected, because '" << *_maybe.first
              << "'\n";

    return true;
  }
};

using test0000 = test_unsigned_int_max<uint8_t>;
using test0001 = test_unsigned_int_max_overflow<uint8_t>;
using test0002 = test_signed_int_max<int8_t>;
using test0003 = test_signed_int_max_overflow<int8_t>;
using test0004 = test_signed_int_min<int8_t>;
using test0005 = test_signed_int_min_underflow<int8_t>;

using test0006 = test_unsigned_int_max<uint16_t>;
using test0007 = test_unsigned_int_max_overflow<uint16_t>;
using test0008 = test_signed_int_max<int16_t>;
using test0009 = test_signed_int_max_overflow<int16_t>;
using test0010 = test_signed_int_min<int16_t>;
using test0011 = test_signed_int_min_underflow<int16_t>;

using test0012 = test_unsigned_int_max<uint32_t>;
using test0013 = test_unsigned_int_max_overflow<uint32_t>;
using test0014 = test_signed_int_max<int32_t>;
using test0015 = test_signed_int_max_overflow<int32_t>;
using test0016 = test_signed_int_min<int32_t>;
using test0017 = test_signed_int_min_underflow<int32_t>;

using test0018 = test_unsigned_int_max<uint64_t>;
using test0019 = test_unsigned_int_max_overflow<uint64_t>;
using test0020 = test_signed_int_max<int64_t>;
using test0021 = test_signed_int_max_overflow<int64_t>;
using test0022 = test_signed_int_min<int64_t>;
using test0023 = test_signed_int_min_underflow<int64_t>;

// struct test006 {
//   static std::string desc() { return "cvt<uint8_t>(\"-8\")"; }

//  bool operator()(const program::alg::options &) {

//    auto _maybe{cvt<uint8_t>("-8")};

//    if (_maybe.first) {
//      std::cerr << "It did not convert, as expected, because '" <<
//      *_maybe.first
//                << "'\n";
//      return true;
//    }
//    std::cerr << "It should not have converted, but it did to " <<
//    _maybe.second
//              << '\n';
//    return false;
//  }
//};

// struct test007 {
//   static std::string desc() { return "cvt<uint8_t>(\"0000122\")"; }

//  bool operator()(const program::alg::options &) {

//    auto _maybe{cvt<uint8_t>("0000122")};

//    if (_maybe.first) {
//      std::cerr << "It should have converted, but it did because '"
//                << *_maybe.first << "'\n";
//      return false;
//    }

//    if (_maybe.second != 122) {
//      std::cerr << "It should have converted to 122, but it converted to "
//                << static_cast<uint16_t>(_maybe.second) << '\n';
//      return false;
//    }

//    std::cerr << "It converted to " << static_cast<uint16_t>(_maybe.second)
//              << ", as it should" << '\n';
//    return true;
//  }
//};

// struct test008 {
//   static std::string desc() { return "cvt<uint8_t>(\"2.4\")"; }

//  bool operator()(const program::alg::options &) {

//    auto _maybe{cvt<uint8_t>("2.4")};

//    if (_maybe.first) {
//      std::cerr << "It did not convert, as it should, because '"
//                << *_maybe.first << "'\n";
//      return true;
//    }

//    std::cerr << "It converte to " << static_cast<uint16_t>(_maybe.second)
//              << ", but it should not" << '\n';
//    return false;
//  }
//};

// struct test009 {
//   static std::string desc() { return "cvt<uint8_t>(\"1c2\")"; }

//  bool operator()(const program::alg::options &) {

//    auto _maybe{cvt<uint8_t>("1c2")};

//    if (_maybe.first) {
//      std::cerr << "It did not convert, as it should, because '"
//                << *_maybe.first << "'\n";
//      return true;
//    }

//    std::cerr << "It converted to " << static_cast<uint16_t>(_maybe.second)
//              << ", but it should not" << '\n';
//    return false;
//  }
//};

// struct test010 {
//   static std::string desc() { return "cvt<int8_t>(\"-128\")"; }

//  bool operator()(const program::alg::options &) {

//    auto _maybe{cvt<int8_t>("-128")};

//    if (_maybe.first) {
//      std::cerr << "It did not convert because '" << *_maybe.first
//                << "', but it should have\n";
//      return false;
//    }

//    auto _i{std::move(_maybe.second)};
//    if (_i != -128) {
//      std::cerr << "It converted to " << static_cast<int16_t>(_i)
//                << ", but it should have converted to -128\n";
//      return false;
//    }

//    std::cerr << "It converted to " << static_cast<int16_t>(_maybe.second)
//              << ", as expected\n";
//    return true;
//  }
//};

// struct test011 {
//   static std::string desc() { return "cvt<int8_t>(\"-129\")"; }

//  bool operator()(const program::alg::options &) {

//    auto _maybe{cvt<int8_t>("-129")};
//    if (_maybe.first) {
//      std::cerr << "It did not convert, as expected, because '" <<
//      *_maybe.first
//                << "'\n";
//      return true;
//    }

//    std::cerr << "It should not have converted, but it did to " <<
//    _maybe.second
//              << '\n';
//    return false;
//  }
//};

// struct test012 {
//   static std::string desc() { return "cvt<int8_t>(\"127\")"; }

//  bool operator()(const program::alg::options &) {

//    auto _maybe{cvt<int8_t>("127")};

//    if (_maybe.first) {
//      std::cerr << "It did not convert because '" << *_maybe.first
//                << "', but it should have\n";
//      return false;
//    }

//    auto _i{std::move(_maybe.second)};
//    if (_i != 127) {
//      std::cerr << "It converted to " << static_cast<int16_t>(_i)
//                << ", but it should have converted to 127\n";
//      return false;
//    }

//    std::cerr << "It converted to " << static_cast<int16_t>(_maybe.second)
//              << ", as expected\n";
//    return true;
//  }
//};

// struct test013 {
//   static std::string desc() { return "cvt<int8_t>(\"128\")"; }

//  bool operator()(const program::alg::options &) {

//    auto _maybe{cvt<int8_t>("128")};
//    if (_maybe.first) {
//      std::cerr << "It did not convert, as expected, because '" <<
//      *_maybe.first
//                << "'\n";
//      return true;
//    }

//    std::cerr << "It should not have converted, but it did to "
//              << static_cast<int16_t>(_maybe.second) << '\n';
//    return false;
//  }
//};

// struct test014 {
//   static std::string desc() {
//     return "cvt<uint64_t>(\"18446744073709551615\"), which is "
//            "std::numeric_limits<uint64_t>::max()";
//   }

//  bool operator()(const program::alg::options &) {

//    std::stringstream _stream;
//    _stream << std::numeric_limits<uint64_t>::max();

//    std::string _value{_stream.str()};

//    auto _maybe{cvt<uint64_t>(_value)};
//    if (_maybe.first) {
//      std::cerr << "It did not convert, but it should have, because '"
//                << *_maybe.first << "'\n";
//      return false;
//    }

//    if (_maybe.second != std::numeric_limits<uint64_t>::max()) {
//      std::cerr << "It converted to " << _maybe.second
//                << ", but it should have converted to " << _value << "\n";
//    }

//    std::cerr << "It converted to " << _maybe.second << ", as expected\n";
//    return true;
//  }
//};

// struct test015 {
//   static std::string desc() {
//     return "cvt<uint64_t>(\"18446744073709551616\"), which is "
//            "std::numeric_limits<uint64_t>::max() + 1";
//   }

//  bool operator()(const program::alg::options &) {

//    std::stringstream _stream;
//    _stream << std::numeric_limits<uint64_t>::max();

//    std::string _value{_stream.str()};

//    int8_t _last(_value[_value.size() - 1] - '0');
//    ++_last;
//    _value[_value.size() - 1] = _last + '0';

//    auto _maybe{cvt<uint64_t>(_value)};
//    if (!_maybe.first) {
//      std::cerr << "It converted " << _maybe.second
//                << ", but it should not have\n";
//      return false;
//    }

//    std::cerr << "It did not convert, as expected, because '" << *_maybe.first
//              << "'\n";
//    return true;
//  }
//};

// struct test016 {
//   static std::string desc() {
//     return "cvt<int64_t>(\"9223372036854775807,\"), which is "
//            "std::numeric_limits<int64_t>::max()";
//   }

//  bool operator()(const program::alg::options &) {

//    std::stringstream _stream;
//    _stream << std::numeric_limits<int64_t>::max();

//    std::string _value{_stream.str()};

//    auto _maybe{cvt<int64_t>(_value)};
//    if (_maybe.first) {
//      std::cerr << "It did not convert, but it should have, because '"
//                << *_maybe.first << "'\n";
//      return false;
//    }

//    if (_maybe.second != std::numeric_limits<int64_t>::max()) {
//      std::cerr << "It converted to " << _maybe.second
//                << ", but it should have converted to " << _value << "\n";
//    }

//    std::cerr << "It converted to " << _maybe.second << ", as expected\n";
//    return true;
//  }
//};

// struct test017 {
//   static std::string desc() {
//     return "cvt<int64_t>(\"9223372036854775808\"), which is "
//            "std::numeric_limits<int64_t>::max() + 1";
//   }

//  bool operator()(const program::alg::options &) {

//    std::stringstream _stream;
//    _stream << std::numeric_limits<int64_t>::max();

//    std::string _value{_stream.str()};

//    int8_t _last(_value[_value.size() - 1] - '0');
//    ++_last;
//    _value[_value.size() - 1] = _last + '0';

//    auto _maybe{cvt<int64_t>(_value)};
//    if (!_maybe.first) {
//      std::cerr << "It converted to " << _maybe.second
//                << ", but it should not have\n";
//      return false;
//    }

//    std::cerr << "It did not convert, as expected, because '" << *_maybe.first
//              << "'\n";

//    return true;
//  }
//};

// struct test018 {
//   static std::string desc() {
//     return "cvt<int64_t>(\"-9223372036854775808\"), which is "
//            "std::numeric_limits<int64_t>::min()";
//   }

//  bool operator()(const program::alg::options &) {

//    std::stringstream _stream;
//    _stream << std::numeric_limits<int64_t>::min();

//    std::string _value{_stream.str()};

//    auto _maybe{cvt<int64_t>(_value)};
//    if (_maybe.first) {
//      std::cerr << "It did not convert, but it should have, because '"
//                << *_maybe.first << "'\n";
//      return false;
//    }

//    if (_maybe.second != std::numeric_limits<int64_t>::min()) {
//      std::cerr << "It should have converted to "
//                << std::numeric_limits<int64_t>::min()
//                << ", but it converted to " << _maybe.second << '\n';
//      return false;
//    }

//    std::cerr << "It converted to " << _maybe.second << ", as it should \n";
//    return true;
//  }
//};

// struct test019 {
//   static std::string desc() {
//     return "cvt<int64_t>(\"-9223372036854775809\"), which is "
//            "std::numeric_limits<int64_t>::max() - 1";
//   }

//  bool operator()(const program::alg::options &) {

//    std::stringstream _stream;
//    _stream << std::numeric_limits<int64_t>::min();

//    std::string _value{_stream.str()};

//    int8_t _last(_value[_value.size() - 1] - '0');
//    ++_last;
//    _value[_value.size() - 1] = _last + '0';

//    auto _maybe{cvt<int64_t>(_value)};
//    if (!_maybe.first) {
//      std::cerr << "It converted to " << _maybe.second
//                << ", but it should not have\n";
//      return false;
//    }

//    std::cerr << "It did not convert, as expected, because '" << *_maybe.first
//              << "'\n";

//    return true;
//  }
//};

int main(int argc, char **argv) {
  test::alg::tester _test(argc, argv);

  // run_test(_test, testNoConversion);
  run_test(_test, test0000);
  run_test(_test, test0001);
  run_test(_test, test0002);
  run_test(_test, test0003);
  run_test(_test, test0004);
  run_test(_test, test0005);
  run_test(_test, test0006);
  run_test(_test, test0007);
  run_test(_test, test0008);
  run_test(_test, test0009);
  run_test(_test, test0010);
  run_test(_test, test0011);
  run_test(_test, test0012);
  run_test(_test, test0013);
  run_test(_test, test0014);
  run_test(_test, test0015);
  run_test(_test, test0016);
  run_test(_test, test0017);
  run_test(_test, test0018);
  run_test(_test, test0019);
  run_test(_test, test0020);
  run_test(_test, test0021);
  run_test(_test, test0022);
  run_test(_test, test0023);
}
