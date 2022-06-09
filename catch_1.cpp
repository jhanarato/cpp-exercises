#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("how do catch test cases work?") {
    // starting gets initialised to 15 in each section.
    int starting = 15;

    SECTION("add to starting") {
        starting += 12;
        REQUIRE(starting == 27);
    }

    SECTION("add to starting ignoring the above section") {
        starting += 4;
        REQUIRE(starting == 19);
    }
}