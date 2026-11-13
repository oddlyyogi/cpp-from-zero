#pragma once

#include "level.hpp"

#include <expected>
#include <string>
#include <string_view>

namespace loglens {

enum class ParseError { BadDate, BadTime, NoLevel, NoSource };

struct LogEntry {
    std::string date;
    std::string time;
    Level level = Level::Info;
    std::string source;
    std::string message;
};

std::expected<LogEntry, ParseError> parse_line(std::string_view line);
std::string_view describe(ParseError error);

}  // namespace loglens