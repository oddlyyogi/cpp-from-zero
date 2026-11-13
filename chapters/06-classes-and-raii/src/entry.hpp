#pragma once

#include "level.hpp"

#include <string>
#include <string_view>

namespace loglens {

struct LogEntry {
    std::string date;
    std::string time;
    Level level = Level::Info;
    std::string source;
    std::string message;
};

bool parse_line(std::string_view line, LogEntry& out);

}  // namespace loglens