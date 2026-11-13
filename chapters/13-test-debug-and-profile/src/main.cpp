#include <algorithm>
#include "log_file.hpp"
#include "sink.hpp"
#include "kv_store.hpp"
#include "ring_buffer.hpp"
#include <chrono>
#include <print>
#include <memory>
#include <span>
#include <string>
#include <string_view>
#include <vector>
#include <filesystem>
#include <format>
#include <atomic>
#include <thread>

#include "level.hpp"
#include "stats.hpp"
#include "version.hpp"

int run_summary(std::span<char*> files) {
    std::vector<loglens::Counts> results(files.size());
    std::atomic<long long> lines{0};
    {
        std::vector<std::jthread> workers;
        for (std::size_t i = 0; i < files.size(); ++i) {
            workers.emplace_back([&, i] {
                loglens::LogFile in(files[i]);
                if (!in.is_open()) {
                    return;
                }
                std::string line;
                while (in.read_line(line)) {
                    if (!line.empty()) {
                        loglens::count_line(results[i], line);
                        ++lines;
                    }
                }
            });
        }
    }
    for (std::size_t i = 0; i < files.size(); ++i) {
        std::println("{:<14} {:>5} lines {:>4} errors", files[i], results[i].total,
                     loglens::count_of(results[i], loglens::Level::Error));
    }
    std::println("{} lines in {} files; hardware threads: {}", lines.load(), files.size(),
                 std::thread::hardware_concurrency());
    return 0;
}

int run_kv(std::span<char*> args) {
    loglens::KvStore store("data.kv");
    std::string_view cmd = args.size() > 2 ? args[2] : "";
    if (cmd == "put" && args.size() == 5) {
        store.put(args[3], args[4]);
        return 0;
    }
    if (cmd == "get" && args.size() == 4) {
        if (auto value = store.get(args[3])) {
            std::println("{}", *value);
            return 0;
        }
        std::println("not found");
        return 1;
    }
    if (cmd == "del" && args.size() == 4) {
        return store.del(args[3]) ? 0 : 1;
    }
    if (cmd == "load" && args.size() == 4) {
        std::filesystem::remove("load.kv");
        loglens::KvStore bulk("load.kv");
        int n = std::stoi(args[3]);
        {
            std::vector<std::jthread> writers;
            for (int t = 0; t < 4; ++t) {
                writers.emplace_back([&bulk, n, t] {
                    for (int i = t; i < n; i += 4) {
                        bulk.put(std::format("key{}", i), std::to_string(i * i));
                    }
                });
            }
        }
        std::println("{} keys", bulk.size());
        return 0;
    }
    if (cmd == "list") {
        for (const std::string& key : store.keys()) {
            std::println("{} = {}", key, store.get(key).value_or("?"));
        }
        return 0;
    }
    std::println("usage: loglens kv put|get|del|list ...");
    return 2;
}

int main(int argc, char* argv[]) {
    std::span<char*> args(argv, static_cast<std::size_t>(argc));
    if (args.size() >= 2 && std::string_view(args[1]) == "kv") {
        try {
            return run_kv(args);
        } catch (const loglens::KvError& e) {
            std::println("error: {}", e.what());
            return 1;
        }
    }
    if (args.size() >= 3 && std::string_view(args[1]) == "--summary") {
        return run_summary(args.subspan(2));
    }
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

    auto start = std::chrono::steady_clock::now();
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
    auto took = std::chrono::steady_clock::now() - start;
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
    std::println("counted in {} ms",
                 std::chrono::duration_cast<std::chrono::milliseconds>(took).count());
    return 0;
}