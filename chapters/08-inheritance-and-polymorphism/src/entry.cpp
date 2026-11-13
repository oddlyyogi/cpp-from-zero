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

bool parse_line(std::string_view line, LogEntry& out) {
    std::string_view rest = line;
    std::string_view date = next_word(rest);
    std::string_view time = next_word(rest);
    std::string_view level = next_word(rest);
    std::string_view source = next_word(rest);
    if (date.size() != 10 || time.size() != 8 || level.empty() || !source.ends_with(':')) {
        return false;
    }
    source.remove_suffix(1);
    out.date = date;
    out.time = time;
    out.level = parse_level(line);
    out.source = source;
    out.message = rest;
    return true;
}

}  // namespace loglens
