#include "stats.hpp"

#include <print>
#include <string>

namespace loglens {

void count_line(Counts& counts, std::string_view line) {
    ++counts.total;
    switch (parse_level(line)) {
    case Level::Debug: ++counts.debug; break;
    case Level::Info: ++counts.info; break;
    case Level::Warn: ++counts.warn; break;
    case Level::Error: ++counts.error; break;
    }
}

long long count_of(const Counts& counts, Level level) {
    switch (level) {
    case Level::Debug: return counts.debug;
    case Level::Info: return counts.info;
    case Level::Warn: return counts.warn;
    case Level::Error: return counts.error;
    }
    return 0;
}

void print_report(const Counts& counts, int percent_per_mark) {
    std::println("{} lines", counts.total);
    long long problems = 0;
    for (Level l : {Level::Debug, Level::Info, Level::Warn, Level::Error}) {
        long long n = count_of(counts, l);
        double share = 100.0 * n / counts.total;
        if (is_problem(l)) {
            problems += n;
        }
        std::string bar(static_cast<int>(share / percent_per_mark), '#');
        std::println("{:<6} {:>5} {:>6.1f}%  {}", level_name(l), n, share, bar);
    }
    if (problems > 0) {
        std::println("{} {} attention", problems, problems == 1 ? "line needs" : "lines need");
    }
}

}  // namespace loglens