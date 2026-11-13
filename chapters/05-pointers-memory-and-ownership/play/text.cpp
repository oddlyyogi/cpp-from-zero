#include <print>
#include <string>
#include <string_view>
#include <vector>
#include <array>
#include <span>

long long total(std::span<const long long> values) {
    long long sum = 0;
    for (long long x : values) {
        sum += x;
    }
    return sum;
}

int main() {
    std::string line = "2026-11-12 08:00:08 DEBUG db: query took 128ms";
    std::println("size {}", line.size());
    auto pos = line.find("db:");
    std::println("db: at {}", pos);
    std::string source = line.substr(pos, 3);
    std::println("source [{}]", source);
    std::println("{} {} {}", line.starts_with("2026"), line.ends_with("ms"),
                 line.contains("DEBUG"));
    std::string_view view = line;
    view.remove_prefix(20);
    std::println("view [{}]", view);
    std::array<long long, 4> by_level{};
    by_level[3] = 16;
    long long old[4] = {38, 313, 33, 16};
    std::println("{} {}", total(by_level), total(old));
    std::vector<int> v;
    std::size_t cap = 0;
    for (int i = 1; i <= 20; ++i) {
        v.push_back(i);
        if (v.capacity() != cap) {
            cap = v.capacity();
            std::println("size {:2} capacity {:2}", v.size(), cap);
        }
    }
    std::vector<int> w;
    w.reserve(20);
    std::println("w: size {} capacity {}", w.size(), w.capacity());
}