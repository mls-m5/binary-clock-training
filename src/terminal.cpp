#include "terminal.hpp"

#include <algorithm>
#include <sstream>
#include <string>

namespace {
void show_clock(const Clock &clock, std::ostream &output) {
    output << '\n';
    for (int index = 0; index < 16; ++index) {
        output << (clock.bit(index) ? "●" : "○");
        output << (index % 4 == 3 ? '\n' : ' ');
    }
    output << '\n';
}

bool parse_time(std::string line, int &hours, int &minutes, int &seconds) {
    std::replace(line.begin(), line.end(), ':', ' ');
    std::istringstream answer(line);
    std::string extra;
    return (answer >> hours >> minutes >> seconds) && !(answer >> extra) &&
           hours >= 0 && hours <= 15 && minutes >= 0 && minutes <= 59 &&
           seconds >= 0 && seconds <= 59;
}
} // namespace

void run_terminal(Clock &clock, std::istream &input, std::ostream &output) {
    output
        << "Binary Clock Training (terminal edition)\n"
           "Read left to right, top to bottom: first 4 bits = hours (0-15),\n"
           "next 6 = minutes, last 6 = seconds (0-59). ● = 1, ○ = 0.\n"
           "Enter HH:MM:SS or three space-separated numbers. Type q to quit.\n";
    std::string line;
    for (;;) {
        clock.new_round();
        show_clock(clock, output);
        while (!clock.solved()) {
            output << "Your answer (HH:MM:SS or q): " << std::flush;
            if (!std::getline(input, line)) {
                output << "Goodbye!\n";
                return;
            }
            std::istringstream command(line);
            std::string word, extra;
            if ((command >> word) && (word == "q" || word == "Q") &&
                !(command >> extra)) {
                output << "Goodbye!\n";
                return;
            }
            int hours, minutes, seconds;
            if (!parse_time(line, hours, minutes, seconds)) {
                output << "Enter hours 0-15, minutes 0-59, and seconds 0-59 "
                          "(e.g. 09:23:45).\n";
                continue;
            }
            clock.check(hours, minutes, seconds);
            if (clock.solved()) {
                output << "Correct! Try the next clock.\n";
                break;
            }
            output << "Correct fields: ";
            const char *names[] = {"hours", "minutes", "seconds"};
            bool any = false;
            for (int part = 0; part < 3; ++part) {
                if (!clock.correct(part))
                    continue;
                if (any)
                    output << ", ";
                output << names[part];
                any = true;
            }
            if (!any)
                output << "none yet";
            output << ". Try again.\n";
        }
    }
}
