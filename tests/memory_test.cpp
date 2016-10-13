#include <catch.hpp>
#include "memory/shared_ptr.hpp"
#include "memory_test.hpp"
#include <iostream>

namespace ns_memory {
    TEST_CASE("memory", "[cpp_examples][memory]") {
        SECTION("shared_ptr") {
            {
                auto pObject = shared_ptr<object>(new object);
            }
        }
    }

    object::object() {
        std::cout << "!!!!!!! " << __PRETTY_FUNCTION__ << std::endl;
    }

    object::~object() {
        std::cout << "!!!!!!! " << __PRETTY_FUNCTION__ << std::endl;
    }
}
