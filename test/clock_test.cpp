#include "../src/clock.hpp"

#include <cassert>

int main()
{
    Clock clock(42);
    assert(Clock::group(-1) == -1 && Clock::group(16) == -1);
    assert(Clock::weight(-1) == 0 && Clock::weight(16) == 0);
    for (int round = 0; round < 100; ++round) {
        clock.new_round();
        assert(clock.result() == -1 && !clock.solved());
        int values[] = {0, 0, 0};
        for (int i = 0; i < 16; ++i) {
            int group = Clock::group(i);
            assert(group == (i < 4 ? 0 : i < 10 ? 1 : 2));
            assert(clock.bit(i) == 0 || clock.bit(i) == 1);
            values[group] += clock.bit(i) * Clock::weight(i);
        }
        assert(values[0] <= 15 && values[1] <= 59 && values[2] <= 59);
        assert(clock.check(-1, 0, 0) == -1);
        assert(clock.check((values[0] + 1) % 16, values[1], values[2]) == 6);
        assert(!clock.correct(0) && clock.correct(1) && clock.correct(2));
        assert(clock.check(values[0], values[1], values[2]) == 7);
        assert(clock.solved());
        assert(clock.check(0, 0, 0) == 7); // Solved round stays solved.
    }
}
