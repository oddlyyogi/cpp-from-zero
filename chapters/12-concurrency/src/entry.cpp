#include "entry.hpp"

namespace loglens {

namespace {
std::string_view next_word(std::string_view& text) {
    auto end = text.find(' ');
    std::string_view word = text.substr(0, end);
    text.remove_prefix(end == std::string_view::npos ? text.size() : end);
    while (text.starts_with(' ')) {
        text.remove_prefix(1);
    }
    return word;
}
}  // namespace

std::expected<LogEntry, ParseError> parse_line(std::string_view line) {
    std::string_view rest = line;
    std::string_view date = next_word(rest);
    std::string_view time = next_word(rest);
    std::string_view level = next_word(rest);
    std::string_view source = next_word(rest);
    if (date.size() != 10) {
        return std::unexpected(ParseError::BadDate);
    }
    if (time.size() != 8) {
        return std::unexpected(ParseError::BadTime);
    }
    if (level.empty()) {
        return std::unexpected(ParseError::NoLevel);
    }
    if (!source.ends_with(':')) {
        return std::unexpected(ParseError::NoSource);
    }
    source.remove_suffix(1);
    LogEntry entry;
    entry.date = date;
    entry.time = time;
    entry.level = parse_level(line);
    entry.source = source;
    entry.message = rest;
    return entry;
}

std::string_view describe(ParseError error) {
    switch (error) {
    case ParseError::BadDate: return "bad date";
    case ParseError::BadTime: return "bad time";
    case ParseError::NoLevel: return "no level";
    case ParseError::NoSource: return "no source";
    }
    return "?";
}

}  // namespace loglens
