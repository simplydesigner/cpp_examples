#include <catch.hpp>
#include "memory/shared_ptr.hpp"
#include "object_alive.hpp"
#include <utility>
#include <iostream>

namespace ns_memory {

    TEST_CASE("shared_ptr", "[cpp_examples][shared_ptr]") {
        bool alive = false;

        SECTION("shared_ptr(const T*) and ") {
            {
                object* cpObject{new object(alive)};
                shared_ptr<object> pObject{cpObject};
                REQUIRE(alive == true);
            }
            REQUIRE(alive == false);
        }

        SECTION("shared_ptr(const shared_ptr&)") {
            {
                object* cpObject{new object(alive)};
                shared_ptr<object> pObject_1{cpObject};
                {
                    auto pObject_2 = pObject_1;
                }
                REQUIRE(alive == true);
            }
            REQUIRE(alive == false);
        }

        SECTION("shared_ptr(shared_ptr&&)") {
            {
                object* cpObject{new object(alive)};
                shared_ptr<object> pObject_1{cpObject};
                shared_ptr<object> pObject_2{std::move(pObject_1)};
                REQUIRE(alive == true);
            }
            REQUIRE(alive == false);
        }

        SECTION("shared_ptr& operator=(const shared_ptr&)") {
            {
                object* cpObject{new object(alive)};
                shared_ptr<object> pObject_1{cpObject};
                shared_ptr<object> pObject_2;
                pObject_2 = pObject_1;
                REQUIRE(alive == true);
            }
            REQUIRE(alive == false);
        }

        SECTION("shared_ptr& operator=(shared_ptr&&)") {
            {
                object* cpObject{new object(alive)};
                shared_ptr<object> pObject_1{cpObject};
                shared_ptr<object> pObject_2;
                pObject_2 = std::move(pObject_1);
                REQUIRE(alive == true);
            }
            REQUIRE(alive == false);
        }

        SECTION(":= nullptr") {
            object* cpObject{new object(alive)};
            shared_ptr<object> pObject_1{cpObject};
            REQUIRE(alive == true);
            shared_ptr<object> pObject_2;
            pObject_1 = pObject_2;
            REQUIRE(alive == false);
        }
    }
}
