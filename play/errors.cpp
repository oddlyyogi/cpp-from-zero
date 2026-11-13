#include <format>
#include <optional>
#include <expected>
#include <string_view>
#include <cstdlib>
#include <print>
#include <stdexcept>
#include <utility>
#include <string>

struct Guard {
    std::string name;
    explicit Guard(std::string n) : name(std::move(n)) { std::println("enter {}", name); }
    ~Guard() { std::println("leave {}", name); }
};

std::optional<int> find_port(std::string_view service) {
    if (service == "http") {
        return 80;
    }
    return std::nullopt;
}

std::expected<int, std::string> parse_percent(std::string_view text) {
    int value = 0;
    for (char c : text) {
        if (c < '0' || c > '9') {
            return std::unexpected(std::format("not a number: {}", text));
        }
        value = value * 10 + (c - '0');
    }
    if (value > 100) {
        return std::unexpected(std::format("out of range: {}", value));
    }
    return value;
}

class ConfigError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

void read_config() {
    Guard g("read_config");
    throw ConfigError("config file is empty");
}

void start() {
    Guard g("start");
    try {
        read_config();
    } catch (const ConfigError&) {
        std::println("start: logging, then passing it on");
        throw;
    }
    std::println("never printed");
}

void cleanup() noexcept {
    throw std::runtime_error("broken promise");
}

int main() {
    if (std::getenv("BREAK") != nullptr) {
        cleanup();
    }
    std::println("http {} mail {}", find_port("http").value_or(-1),
                 find_port("mail").value_or(-1));
    std::println("{}", parse_percent("40").transform([](int v) { return v * 2; }).value_or(0));
    if (auto r = parse_percent("4x"); !r) {
        std::println("error: {}", r.error());
    }
    auto safe = parse_percent("250").or_else(
        [](const std::string& e) -> std::expected<int, std::string> {
            std::println("recovering from: {}", e);
            return 100;
        });
    std::println("safe {}", *safe);
    try {
        start();
    } catch (const std::exception& e) {
        std::println("caught: {}", e.what());
    }
}