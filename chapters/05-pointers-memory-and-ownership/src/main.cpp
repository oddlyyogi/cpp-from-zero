#include <algorithm>
#include <fstream>
#include <print>
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
    std::ifstream in(args[1]);
    if (!in) {
        std::println("cannot open {}", args[1]);
        return 1;
    }
    std::println("loglens version {}", loglens::version());

    loglens::Counts counts;
    std::string line;
    std::vector<int> last_errors(5);
    int errors = 0;
    int line_no = 0;
    while (std::getline(in, line)) {
        // blank lines are not log entries
        if (line.empty()) {
            continue;
        }
        ++line_no;
        loglens::count_line(counts, line);
        if (loglens::parse_level(line) == loglens::Level::Error) {
            last_errors[errors % 5] = line_no;
            ++errors;
        }
    }
    if (counts.total == 0) {
        std::println("no lines read");
        return 1;
    }
    loglens::print_report(counts);
    std::print("last errors at lines:");
    for (int k = std::max(0, errors - 5); k < errors; ++k) {
        std::print(" {}", last_errors[k % 5]);
    }
    std::println();
    return 0;
}