#include <cstdint>
#include <print>

int main() {
    std::println("int {}  long long {}  double {}",
                 sizeof(int), sizeof(long long), sizeof(double));
    std::println("char {}  bool {}  size_t {}",
                 sizeof(char), sizeof(bool), sizeof(std::size_t));
    char grade = 'A';
    std::println("{} {} {}", grade, grade + 1, static_cast<char>(grade + 1));
    bool ok = 3 > 2;
    std::println("ok is {}", ok);
    std::int64_t bytes_read = 0;
    std::println("bytes_read {}", bytes_read);
    int a = 3.7;
    std::println("a = {}", a);
    auto lines = 400;
    auto ratio = 0.25;
    std::println("lines {} ratio {}", lines, ratio);
    const int max_errors = 10;
    constexpr int level_count = 4;
    static_assert(level_count == 4, "we track four log levels");
    std::println("max_errors {}", max_errors);
    std::println("7 / 2 = {}  7 % 2 = {}  7 / 2.0 = {}", 7 / 2, 7 % 2, 7 / 2.0);
    std::println("0.1 + 0.2 = {}", 0.1 + 0.2);
    int big = 2147483647;
    std::println("big + 1 = {}", big + 1);
    int minus_one = -1;
    unsigned int three = 3;
    std::println("-1 < 3u is {}", minus_one < three);
    for (int i = 1; i <= 3; ++i) {
        std::println("{} {}", i, i == 1 ? "line" : "lines");
    }
}