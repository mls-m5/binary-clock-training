#include "clock.hpp"

Clock::Clock(std::uint32_t seed)
    : rng_(seed) {}

void Clock::new_round() {
    hours_ = std::uniform_int_distribution<int>(0, 15)(rng_);
    minutes_ = std::uniform_int_distribution<int>(0, 59)(rng_);
    seconds_ = std::uniform_int_distribution<int>(0, 59)(rng_);
    result_ = -1;
}

int Clock::group(int index) {
    if (index < 0 || index >= 16)
        return -1;
    return index < 4 ? 0 : index < 10 ? 1 : 2;
}

int Clock::weight(int index) {
    int part = group(index);
    if (part < 0)
        return 0;
    return 1 << ((part == 0 ? 3 : part == 1 ? 9 : 15) - index);
}

int Clock::bit(int index) const {
    int part = group(index);
    if (part < 0)
        return 0;
    int value = part == 0 ? hours_ : part == 1 ? minutes_ : seconds_;
    return (value & weight(index)) != 0;
}

int Clock::check(int hours, int minutes, int seconds) {
    if (hours < 0 || hours > 15 || minutes < 0 || minutes > 59 || seconds < 0 ||
        seconds > 59 || solved())
        return result_;
    result_ = (hours == hours_ ? 1 : 0) | (minutes == minutes_ ? 2 : 0) |
              (seconds == seconds_ ? 4 : 0);
    return result_;
}

bool Clock::correct(int part) const {
    return part >= 0 && part < 3 && result_ >= 0 && (result_ & (1 << part));
}

bool Clock::solved() const {
    return result_ == 7;
}
