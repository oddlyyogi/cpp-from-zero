#pragma once

#include "level.hpp"

#include <string_view>

namespace loglens {

struct Counts {
    long long total = 0;
    long long debug = 0;
    long long info = 0;
    long long warn = 0;
    long long error = 0;
};

void count_line(Counts& counts, std::string_view line);
[[nodiscard]] long long count_of(const Counts& counts, Level level);
void print_report(const Counts& counts, int percent_per_mark = 2);

}  // namespace loglens