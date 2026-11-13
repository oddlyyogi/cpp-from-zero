#include "stats.hpp"

#include <charconv>
#include <print>
#include <span>
#include <string>

namespace loglens {

void count_line(Counts& counts, std::string_view line) {
    ++counts.total;
    LogEntry entry;
    if (!parse_line(line, entry)) {
        ++counts.malformed;
        return;
    }
    ++counts.by_level[static_cast<std::size_t>(entry.level)];
    int hour = 0;
    int minute = 0;
    std::from_chars(entry.time.data(), entry.time.data() + 2, hour);
    std::from_chars(entry.time.data() + 3, entry.time.data() + 5, minute);
    ++counts.by_minute[hour * 60 + minute];
    counts.sources.add(entry.source);
}

long long count_of(const Counts& counts, Level level) {
    return counts.by_level[static_cast<std::size_t>(level)];
}

void report_levels(const Counts& counts, Sink& sink) {
    long long parsed = counts.total - counts.malformed;
    sink.begin();
    for (Level l : {Level::Debug, Level::Info, Level::Warn, Level::Error}) {
        long long n = count_of(counts, l);
        sink.row(level_name(l), n, 100.0 * n / parsed);
    }
    sink.end();
}

void print_report(const Counts& counts, int percent_per_mark) {
    std::println("{} lines", counts.total);
    long long problems = 0;
    TextSink text(percent_per_mark);
    report_levels(counts, text);
    for (Level l : {Level::Debug, Level::Info, Level::Warn, Level::Error}) {
        long long n = count_of(counts, l);
        if (is_problem(l)) {
            problems += n;
        }
    }
    std::size_t best = 0;
    for (std::size_t i = 0; i < counts.by_minute.size(); ++i) {
        if (counts.by_minute[i] > counts.by_minute[best]) {
            best = i;
        }
    }
    std::println("busiest minute {:02}:{:02} with {} lines",
                 best / 60, best % 60, counts.by_minute[best]);
    for (const auto& [source, n] : counts.sources.top(5)) {
        std::println("  {:<8} {:>5}", source, n);
    }
    if (counts.malformed > 0) {
        std::println("{} malformed lines skipped", counts.malformed);
    }
    if (problems > 0) {
        std::println("{} {} attention", problems, problems == 1 ? "line needs" : "lines need");
    }
}

}  // namespace loglens