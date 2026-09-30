#pragma once

#include <cstdint>
#include <random>

class Clock {
public:
    explicit Clock(std::uint32_t seed);

    void new_round();
    int bit(int index) const;
    static int group(int index); // 0 = hours, 1 = minutes, 2 = seconds
    static int weight(int index);
    int check(int hours, int minutes, int seconds);
    bool correct(int group) const;
    bool solved() const;
    int result() const {
        return result_;
    } // -1 = no answer yet; otherwise 3-bit mask

private:
    std::mt19937 rng_;
    int hours_ = 0;
    int minutes_ = 0;
    int seconds_ = 0;
    int result_ = -1;
};
