#include <algorithm>
#include <numeric>
#include <map>
#include <print>
#include <ranges>
#include <string>
#include <unordered_map>
#include <vector>

int main() {
    std::map<std::string, int> ordered{{"http", 168}, {"db", 77}, {"cache", 75},
                                       {"auth", 51}, {"worker", 29}};
    std::unordered_map<std::string, int> hashed(ordered.begin(), ordered.end());
    std::println("{}", ordered);
    std::println("{}", hashed);
    std::println("timer: {}", ordered["timer"]);
    std::println("size {}", ordered.size());
    std::println("has db: {}, has mail: {}", hashed.contains("db"), hashed.contains("mail"));
    std::vector<int> ms{12, 575, 90, 128, 667, 76};
    int limit = 100;
    auto slow = [limit](int m) { return m > limit; };
    std::println("slow {} total {}", std::ranges::count_if(ms, slow),
                 std::accumulate(ms.begin(), ms.end(), 0));
    int worst = 0;
    std::ranges::for_each(ms, [&worst](int m) { worst = std::max(worst, m); });
    std::ranges::sort(ms, [](int a, int b) { return a > b; });
    std::println("worst {} sorted {}", worst, ms);
    std::erase_if(ms, [&](int m) { return !slow(m); });
    std::println("only slow {}", ms);
    std::vector<int> times{12, 575, 90, 128, 667, 76};
    auto tenths = times | std::views::filter(slow)
                        | std::views::transform([](int m) { return m / 100; });
    std::println("tenths {}", tenths | std::ranges::to<std::vector>());
    for (auto [i, m] : std::views::enumerate(times) | std::views::take(2)) {
        std::println("#{} = {}", i, m);
    }
    std::vector<std::pair<std::string, int>> by_count(ordered.begin(), ordered.end());
    std::ranges::sort(by_count, std::ranges::greater{}, &std::pair<std::string, int>::second);
    std::println("{}", by_count | std::views::keys | std::views::take(3));
}