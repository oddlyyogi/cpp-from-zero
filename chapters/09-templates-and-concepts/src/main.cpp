#include <algorithm>
#include "log_file.hpp"
#include "sink.hpp"
#include "ring_buffer.hpp"
#include <print>
#include <memory>
#include <span>
#include <string>
#include <string_view>
#include <vector>

#include "level.hpp"
#include "stats.hpp"
#include "version.hpp"

int main(int argc, char* argv[]) {
    std::span<char*> args(argv, static_cast<std::size_t>(argc));
    if (args.size() < 2) {
        std::println("usage: loglens <file>");
        return 2;
    }
    std::string_view format = "text";
    if (args.size() >= 4 && std::string_view(args[2]) == "--format") {
        format = args[3];
    }
    std::unique_ptr<loglens::Sink> sink = loglens::make_sink(format);
    if (!sink) {
        std::println("unknown format {}", format);
        return 2;
    }
    loglens::LogFile in(args[1]);
    if (!in.is_open()) {
        std::println("cannot open {}", args[1]);
        return 1;
    }

    loglens::Counts counts;
    std::string line;
    loglens::RingBuffer last_errors(5);
    int line_no = 0;
    while (in.read_line(line)) {
        // blank lines are not log entries
        if (line.empty()) {
            continue;
        }
        ++line_no;
        loglens::count_line(counts, line);
        if (loglens::parse_level(line) == loglens::Level::Error) {
            last_errors.push(line_no);
        }
    }
    if (counts.total == 0) {
        std::println("no lines read");
        return 1;
    }
    if (format == "csv") {
        loglens::report_levels(counts, *sink);
        return 0;
    }
    std::println("loglens version {}", loglens::version());
    loglens::print_report(counts);
    std::print("last errors at lines:");
    for (std::size_t i = 0; i < last_errors.size(); ++i) {
        std::print(" {}", last_errors.at(i));
    }
    std::println();
    return 0;
}