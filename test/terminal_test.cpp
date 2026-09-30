#include <doctest/doctest.h>

#include "../src/terminal.hpp"

#include <iomanip>
#include <sstream>
#include <string>

TEST_CASE(
    "terminal accepts valid times, provides hints and starts another round") {
    Clock expected(42);
    expected.new_round();
    int values[] = {0, 0, 0};
    std::string grid = "\n";
    for (int i = 0; i < 16; ++i) {
        values[Clock::group(i)] += expected.bit(i) * Clock::weight(i);
        grid += expected.bit(i) ? "●" : "○";
        grid += i % 4 == 3 ? '\n' : ' ';
    }
    grid += '\n';

    std::ostringstream answers;
    answers << "not a time\n16 0 0\n"
            << (values[0] + 1) % 16 << ' ' << values[1] << ' ' << values[2]
            << '\n'
            << std::setfill('0') << std::setw(2) << values[0] << ':'
            << std::setw(2) << values[1] << ':' << std::setw(2) << values[2]
            << '\n'
            << "  q  \n";
    std::istringstream input(answers.str());
    std::ostringstream output;
    Clock clock(42);
    run_terminal(clock, input, output);

    const std::string text = output.str();
    CHECK(text.find(grid) != std::string::npos);
    CHECK(text.find("H:1(") == std::string::npos);
    CHECK(text.find("H:0(") == std::string::npos);
    CHECK(text.find("Enter hours 0-15") != std::string::npos);
    CHECK(text.find("Correct fields: minutes, seconds. Try again.") !=
          std::string::npos);
    CHECK(text.find("Correct! Try the next clock.") != std::string::npos);
    CHECK(text.find("Goodbye!") != std::string::npos);
    CHECK((text.find("\n●", text.find("Correct!")) != std::string::npos ||
           text.find("\n○", text.find("Correct!")) != std::string::npos));
}

TEST_CASE("terminal exits gracefully on end of input") {
    Clock clock(42);
    std::istringstream input;
    std::ostringstream output;
    run_terminal(clock, input, output);
    CHECK(output.str().find("Goodbye!") != std::string::npos);
}
