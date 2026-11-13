#include <array>
#include <concepts>
#include <string_view>
#include "counter.hpp"
#include <print>
#include <string>

struct Point {
    int x;
    int y;
};

template <typename T>
    requires std::totally_ordered<T>
T max_of(T a, T b) {
    return a < b ? b : a;
}

void show(auto value) {
    std::println("show: {}", value);
}

template <typename T>
concept Named = requires(const T& t) {
    { t.name() } -> std::convertible_to<std::string_view>;
};

void greet(const Named auto& thing) {
    std::println("hello, {}", thing.name());
}

struct Server {
    std::string_view name() const { return "db"; }
};

template <typename T, std::size_t N>
T total(const std::array<T, N>& values) {
    T sum{};
    for (const T& v : values) {
        sum += v;
    }
    return sum;
}

template <typename T>
void describe(T value) {
    if constexpr (std::integral<T>) {
        std::println("integer {}", value);
    } else {
        std::println("other {}", value);
    }
}

template <typename... Ts>
auto sum_all(Ts... values) {
    return (values + ...);
}

int main() {
    std::println("{} {}", max_of(3, 7), max_of(2.5, 1.5));
    std::println("{}", max_of(std::string("apple"), std::string("pear")));
    std::println("{}", max_of<double>(3, 2.5));
    loglens::Counter<char> letters;
    for (char c : std::string("banana")) {
        letters.add(c);
    }
    for (const auto& [letter, n] : letters.top(2)) {
        std::println("{} {}", letter, n);
    }
    std::array marks{2, 4, 6};
    std::println("total {}", total(marks));
    describe(7);
    describe(1.5);
    std::println("sum {}", sum_all(1, 2, 3, 4.5));
    greet(Server{});
    static_assert(!Named<int>);
    show(42);
    show(std::string("hi"));
}