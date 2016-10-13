#include <catch.hpp>
#include <algorithm>
#include <numeric>
#include "algorithms/sorting.hpp"

namespace ns_sorting {

    TEST_CASE("sorting", "[cpp_examples][sorting]") {
        SECTION("insertion_sort") {
            std::vector<int> ordered_items(100);
            std::vector<int> unordered_items(ordered_items.size());

            std::iota(ordered_items.begin(), ordered_items.end(),
                ordered_items.size());
            std::reverse_copy(ordered_items.begin(), ordered_items.end(),
                unordered_items.begin());

            REQUIRE(std::equal(ordered_items.begin(), ordered_items.end(),
                unordered_items.begin()) != true);
            ns_sorting::insertion_sort(unordered_items);
            REQUIRE(std::equal(ordered_items.begin(), ordered_items.end(),
                unordered_items.begin()) == true);
        }
    }
}
