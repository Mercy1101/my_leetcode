#include <catch2/catch.hpp>

#include "my_leetcode.hpp"

TEST_CASE("leetcode 一次编辑", "") {
  REQUIRE(lee::onEidtAway("pale", "ple"));
  REQUIRE(!lee::onEidtAway("pales", "pal"));
}