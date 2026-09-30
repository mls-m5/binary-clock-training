#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>

#include <random>

namespace {
struct Time {
    int hours;
    int minutes;
    int seconds;
};

std::mt19937 rng(std::random_device{}());
Time current{};

int bit(int value, int width, int index)
{
    return (value >> (width - 1 - index)) & 1;
}
} // namespace

extern "C" {
EMSCRIPTEN_KEEPALIVE void clock_new_round()
{
    current = {
        std::uniform_int_distribution<int>(0, 15)(rng),
        std::uniform_int_distribution<int>(0, 59)(rng),
        std::uniform_int_distribution<int>(0, 59)(rng),
    };
}

// Row-major order in the 4x4 grid: 4 hour bits, 6 minute bits, 6 second bits.
EMSCRIPTEN_KEEPALIVE int clock_bit(int index)
{
    if (index < 0 || index >= 16) return 0;
    if (index < 4) return bit(current.hours, 4, index);
    if (index < 10) return bit(current.minutes, 6, index - 4);
    return bit(current.seconds, 6, index - 10);
}

// A set bit marks a correct field: hours = 1, minutes = 2, seconds = 4.
EMSCRIPTEN_KEEPALIVE int clock_check(int hours, int minutes, int seconds)
{
    if (hours < 0 || hours > 15 || minutes < 0 || minutes > 59 ||
        seconds < 0 || seconds > 59) return 0;
    return (hours == current.hours ? 1 : 0) |
           (minutes == current.minutes ? 2 : 0) |
           (seconds == current.seconds ? 4 : 0);
}
}

int main() { return 0; }
#else
#include <iostream>

int main()
{
    std::cout << "Build with Emscripten to open the binary clock exercise.\n";
}
#endif
