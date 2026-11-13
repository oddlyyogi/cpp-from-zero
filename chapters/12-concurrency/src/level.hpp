#pragma once

#include <string_view>

namespace loglens {

enum class Level { Debug, Info, Warn, Error };

Level parse_level(std::string_view line);
std::string_view level_name(Level level);
inline bool is_problem(Level level) {
    return level == Level::Warn || level == Level::Error;
}

}  // namespace loglens