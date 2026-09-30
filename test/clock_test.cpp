#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "../src/clock.hpp"

TEST_CASE("invalid bit positions have no group or weight")
{
    CHECK(Clock::group(-1) == -1);
    CHECK(Clock::group(16) == -1);
    CHECK(Clock::weight(-1) == 0);
    CHECK(Clock::weight(16) == 0);
}

TEST_CASE("clock bits decode to a valid time and answers are checked by field")
{
    Clock clock(42);
    for (int round = 0; round < 100; ++round) {
        clock.new_round();
        CHECK(clock.result() == -1);
        CHECK_FALSE(clock.solved());

        int values[] = {0, 0, 0};
        for (int i = 0; i < 16; ++i) {
            int group = Clock::group(i);
            REQUIRE(group == (i < 4 ? 0 : i < 10 ? 1 : 2));
            CHECK((clock.bit(i) == 0 || clock.bit(i) == 1));
            values[group] += clock.bit(i) * Clock::weight(i);
        }
        CHECK(values[0] <= 15);
        CHECK(values[1] <= 59);
        CHECK(values[2] <= 59);
        CHECK(clock.check(-1, 0, 0) == -1);
        CHECK(clock.check((values[0] + 1) % 16, values[1], values[2]) == 6);
        CHECK_FALSE(clock.correct(0));
        CHECK(clock.correct(1));
        CHECK(clock.correct(2));
        CHECK(clock.check(values[0], values[1], values[2]) == 7);
        CHECK(clock.solved());
        CHECK(clock.check(0, 0, 0) == 7); // Solved round stays solved.
    }
}
