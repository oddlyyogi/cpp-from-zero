#include "level.hpp"

namespace loglens {

namespace {
bool has_tag(std::string_view line, std::string_view tag) {
    return line.contains(tag);
}
}  // namespace

Level parse_level(std::string_view line) {
    if (has_tag(line, " ERROR ")) {
        return Level::Error;
    }
    if (has_tag(line, " WARN ")) {
        return Level::Warn;
    }
    if (has_tag(line, " DEBUG ")) {
        return Level::Debug;
    }
    return Level::Info;
}

std::string_view level_name(Level level) {
    switch (level) {
    case Level::Debug: return "DEBUG";
    case Level::Info: return "INFO";
    case Level::Warn: return "WARN";
    case Level::Error: return "ERROR";
    }
    return "?";
}

}  // namespace loglens