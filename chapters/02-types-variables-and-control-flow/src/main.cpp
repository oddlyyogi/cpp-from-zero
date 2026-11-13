#include <iostream>
#include <print>
#include <string>
#include <string_view>

std::string_view version();

enum class Level { Debug, Info, Warn, Error };

int main() {
    std::println("loglens version {}", version());

    long long total = 0;
    long long debug = 0, info = 0, warn = 0, error = 0;
    std::string line;
    while (std::getline(std::cin, line)) {
        // blank lines are not log entries
        if (line.empty()) {
            continue;
        }
        ++total;
        Level level = Level::Info;
        if (line.contains(" ERROR ")) {
            level = Level::Error;
        } else if (line.contains(" WARN ")) {
            level = Level::Warn;
        } else if (line.contains(" DEBUG ")) {
            level = Level::Debug;
        }
        switch (level) {
        case Level::Debug: ++debug; break;
        case Level::Info: ++info; break;
        case Level::Warn: ++warn; break;
        case Level::Error: ++error; break;
        }
    }
    if (total == 0) {
        std::println("no lines read");
        return 1;
    }
    std::println("{} lines", total);
    for (Level l : {Level::Debug, Level::Info, Level::Warn, Level::Error}) {
        std::string_view name;
        long long n = 0;
        switch (l) {
        case Level::Debug: name = "DEBUG"; n = debug; break;
        case Level::Info: name = "INFO"; n = info; break;
        case Level::Warn: name = "WARN"; n = warn; break;
        case Level::Error: name = "ERROR"; n = error; break;
        }
        double share = 100.0 * n / total;
        std::string bar(static_cast<int>(share / 2), '#');
        std::println("{:<6} {:>5} {:>6.1f}%  {}", name, n, share, bar);
    }
    if (long long problems = warn + error; problems > 0) {
        std::println("{} {} attention", problems, problems == 1 ? "line needs" : "lines need");
    }
    return 0;
}