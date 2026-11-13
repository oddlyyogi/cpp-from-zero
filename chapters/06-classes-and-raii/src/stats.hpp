#pragma once

#include "entry.hpp"


#include <array>
#include <string>
#include <string_view>
#include <vector>

namespace loglens {

struct SourceCount {
    std::string source;
    long long count = 0;
};

struct Counts {
    long long total = 0;
    long long malformed = 0;
    std::array<long long, 4> by_level{};
    std::array<long long, 24 * 60> by_minute{};
    std::vector<SourceCount> sources;
};

void count_line(Counts& counts, std::string_view line);
[[nodiscard]] long long count_of(const Counts& counts, Level level);
void print_report(const Counts& counts, int percent_per_mark = 2);

}  // namespace loglens