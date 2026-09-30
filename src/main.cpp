#ifdef __EMSCRIPTEN__
#include "clock.hpp"

#include <emscripten/emscripten.h>

#include <cstring>
#include <random>
#include <string>

namespace {
Clock& clock_state()
{
    static Clock clock(std::random_device{}());
    return clock;
}

struct Text {
    const char* key;
    const char* en;
    const char* sv;
};

const Text texts[] = {
    {"title", "Binary Clock Training", "Binärklockan – öva på att läsa bitar"},
    {"heading", "Binary Clock Training", "Binärklockan"},
    {"intro", "Read the lit squares and enter the time. Add up the weights in each color group: the first four bits are hours, the next six minutes, and the last six seconds.",
     "Läs av de tända rutorna och skriv klockslaget. Lägg ihop vikterna i varje färggrupp: de första fyra bitarna är timmar, följande sex minuter och sista sex sekunder."},
    {"note", "Note: Four bits can only show hours 00–15. This exercise therefore uses times between 00:00:00 and 15:59:59. A lit square counts; an unlit square is zero.",
     "Obs: Fyra bitar räcker bara till timmarna 00–15. Den här övningen använder därför klockslag mellan 00:00:00 och 15:59:59. En tänd ruta räknas, en släckt ruta är noll."},
    {"hours", "Hours", "Timmar"},
    {"minutes", "Minutes", "Minuter"},
    {"seconds", "Seconds", "Sekunder"},
    {"hoursLabel", "Hours (0–15)", "Timmar (0–15)"},
    {"minutesLabel", "Minutes (0–59)", "Minuter (0–59)"},
    {"secondsLabel", "Seconds (0–59)", "Sekunder (0–59)"},
    {"check", "Check answer", "Kontrollera svaret"},
    {"next", "New time", "Nytt klockslag"},
    {"language", "Language", "Språk"},
    {"grid", "Binary clock, 16 bits in reading order", "Binärklocka, 16 bitar i läsordning"},
    {"weight", "weight", "vikt"},
    {"on", "lit", "tänd"},
    {"off", "unlit", "släckt"},
    {"prompt", "What time do the squares show?", "Vilket klockslag visar rutorna?"},
    {"success", "Exactly right! Great job. Try a new time!", "Helt rätt! Bra jobbat. Prova ett nytt klockslag!"},
    {"correct", "Correct", "Rätt"},
    {"none", "none yet", "ingen ännu"},
    {"retry", "Try again with the marked fields.", "Försök igen med de markerade fälten."},
};

const char* text(const char* key, int language)
{
    for (const auto& entry : texts) {
        if (std::strcmp(key, entry.key) == 0) return language == 1 ? entry.sv : entry.en;
    }
    return "";
}

const char* group_name(int group)
{
    static const char* names[] = {"hours", "minutes", "seconds"};
    return group >= 0 && group < 3 ? names[group] : "";
}
} // namespace

extern "C" {
EMSCRIPTEN_KEEPALIVE void clock_new_round() { clock_state().new_round(); }
EMSCRIPTEN_KEEPALIVE int clock_bit(int index) { return clock_state().bit(index); }
EMSCRIPTEN_KEEPALIVE int clock_group(int index) { return Clock::group(index); }
EMSCRIPTEN_KEEPALIVE int clock_weight(int index) { return Clock::weight(index); }
EMSCRIPTEN_KEEPALIVE int clock_check(int hours, int minutes, int seconds)
{
    return clock_state().check(hours, minutes, seconds);
}
EMSCRIPTEN_KEEPALIVE int clock_correct(int group) { return clock_state().correct(group); }
EMSCRIPTEN_KEEPALIVE int clock_solved() { return clock_state().solved(); }
EMSCRIPTEN_KEEPALIVE const char* clock_text(const char* key, int language)
{
    return text(key, language);
}

// Returned pointers remain valid until the next call to the same function.
EMSCRIPTEN_KEEPALIVE const char* clock_bit_label(int index, int language)
{
    static std::string label;
    int group = Clock::group(index);
    if (group < 0) return "";
    label = std::string(text(group_name(group), language)) + ", " +
            text("weight", language) + " " + std::to_string(Clock::weight(index)) + ", " +
            text(clock_state().bit(index) ? "on" : "off", language);
    return label.c_str();
}

EMSCRIPTEN_KEEPALIVE const char* clock_feedback(int language)
{
    static std::string message;
    const Clock& clock = clock_state();
    if (clock.result() < 0) return text("prompt", language);
    if (clock.solved()) return text("success", language);
    message = std::string(text("correct", language)) + ": ";
    bool any = false;
    for (int part = 0; part < 3; ++part) {
        if (!clock.correct(part)) continue;
        if (any) message += ", ";
        message += text(group_name(part), language);
        any = true;
    }
    if (!any) message += text("none", language);
    message += ". ";
    message += text("retry", language);
    return message.c_str();
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
