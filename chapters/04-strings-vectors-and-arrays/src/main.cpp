#include <fstream>
#include <print>
#include <span>
#include <string>
#include <string_view>

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
    while (std::getline(in, line)) {
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