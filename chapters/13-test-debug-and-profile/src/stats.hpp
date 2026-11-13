#pragma once

#include "counter.hpp"
#include "entry.hpp"
#include "sink.hpp"


#include <array>
#include <string>
#include <string_view>
#include <vector>

namespace loglens {

struct Counts {
    long long total = 0;
    long long malformed = 0;
    std::array<long long, 4> by_level{};
    std::array<long long, 24 * 60> by_minute{};
    Counter<std::string> sources;
    Counter<ParseError> reasons;
};

void count_line(Counts& counts, std::string_view line);
[[nodiscard]] long long count_of(const Counts& counts, Level level);
void report_levels(const Counts& counts, Sink& sink);
void print_report(const Counts& counts, int percent_per_mark = 2);

}  // namespace loglens