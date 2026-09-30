#pragma once

#include "clock.hpp"

#include <iosfwd>

// Runs the native exercise until the user enters q or closes the input stream.
void run_terminal(Clock& clock, std::istream& input, std::ostream& output);
