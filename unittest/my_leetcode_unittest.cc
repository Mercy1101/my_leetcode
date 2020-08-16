#include <catch2/catch.hpp>

#include "my_leetcode.hpp"

TEST_CASE("leetcode 一次编辑", "[leetcod][onEidtAway]") {
  auto bo = lee::oneEditAway("pale", "ple");
  REQUIRE(lee::oneEditAway("pale", "ple"));
  REQUIRE(!lee::oneEditAway("pales", "pal"));
}