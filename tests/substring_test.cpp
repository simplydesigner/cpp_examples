#include <catch.hpp>
#include <cstddef>
#include "algorithms/substring.hpp"

namespace ns_substring {

    template <typename T>
    void strstr_test(T *strstr) {

        const char *bigstring       = "asdfg Yter 12Jk";
        const char *substring_0     = "asdfg";
        const char *substring_6     = "Yter";
        const char *substring_11    = "12Jk";
        const char *substring_no    = "skdfkJkfm";

        const char *substring;
        std::ptrdiff_t distance;

        REQUIRE_NOTHROW(substring = strstr(bigstring, substring_0));
        REQUIRE(substring != nullptr);
        distance = substring - bigstring;
        REQUIRE(distance == 0);

        REQUIRE_NOTHROW(substring = strstr(bigstring, substring_6));
        REQUIRE(substring != nullptr);
        distance = substring - bigstring;
        REQUIRE(distance == 6);

        REQUIRE_NOTHROW(substring = strstr(bigstring, substring_11));
        REQUIRE(substring != nullptr);
        distance = substring - bigstring;
        REQUIRE(distance == 11);

        REQUIRE_NOTHROW(substring = strstr(bigstring, substring_no));
        REQUIRE(substring == nullptr);

        REQUIRE_NOTHROW(substring = strstr("", substring_no));
        REQUIRE(substring == nullptr);
        REQUIRE_NOTHROW(substring = strstr(bigstring, ""));
        REQUIRE(substring == nullptr);
    }

    TEST_CASE("substring", "[cpp_examples][substring]") {
        SECTION("brute_force") {
            strstr_test(ns_brute_force::strstr);
        }
        SECTION("kmp") {
            strstr_test(ns_kmp::strstr);
        }
    }
}
