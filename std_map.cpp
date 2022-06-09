#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <map>

auto colour_of_magic = "Colour of Magic";
auto the_light_fantastic = "The Light Fantastic";
auto equal_rites = "Equal Rites";
auto mort = "Mort";

TEST_CASE("std::map is an associative array with") {
  std::map<const char*, int> pub_year{
    { colour_of_magic, 1983 },
    { the_light_fantastic, 1986 },
  };

  SECTION("operator[]") {
    REQUIRE(pub_year[colour_of_magic] == 1983);

    pub_year[equal_rites] = 1987; // Don't we add equal_rites here?
    REQUIRE(pub_year[equal_rites] == 1987);

    REQUIRE(pub_year[mort] == 0);
  }

  SECTION("an at method") {
    REQUIRE(pub_year.at(colour_of_magic) == 1983);

    REQUIRE_THROWS_AS(pub_year.at(equal_rites), std::out_of_range); // Why does equal_rites not work? Because different SECTIONS are separate.
  }
}