#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "..\Full_program_v3.92\Clock.h"

TEST_CASE("Test clock") {
  Clock test = Clock::Clock(1, 2, 3);
  SECTION("Test convertTo24HrTime") {
    REQUIRE(convertTo24HrTime(1, "AM") == 0);
    REQUIRE(convertTo24HrTime(1, "PM") == 12);
    REQUIRE(convertTo24HrTime(5, "AM") == 4);
    REQUIRE(convertTo24HrTime(12, "PM") == 23);
  }
}
