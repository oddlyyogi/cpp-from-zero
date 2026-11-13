#include <iostream>
#include <print>
#include <string>
#include <string_view>

#include "level.hpp"
#include "stats.hpp"
#include "version.hpp"

int main() {
    std::println("loglens version {}", loglens::version());

    loglens::Counts counts;
    std::string line;
    while (std::getline(std::cin, line)) {
        // blank lines are not log entries
        if (line.empty()) {
            continue;
        }
        loglens::count_line(counts, line);
    }
    if (counts.total == 0) {
        std::println("no lines read");
        return 1;
    }
    loglens::print_report(counts);
    return 0;
}