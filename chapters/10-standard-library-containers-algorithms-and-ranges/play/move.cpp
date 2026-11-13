#include <print>
#include <memory>
#include <utility>
#include <vector>

struct Tracker {
    static inline int copies = 0;
    static inline int moves = 0;
    Tracker() = default;
    Tracker(const Tracker&) { ++copies; }
    Tracker(Tracker&&) noexcept { ++moves; }
};

Tracker make() {
    Tracker made;
    return made;
}

int main() {
    std::vector<Tracker> v;
    v.reserve(10);
    Tracker t;
    v.push_back(t);
    v.push_back(Tracker{});
    v.push_back(std::move(t));
    std::println("copies {} moves {}", Tracker::copies, Tracker::moves);
    Tracker::copies = 0;
    Tracker::moves = 0;
    std::vector<Tracker> grow;
    for (int i = 0; i < 1000; ++i) {
        grow.emplace_back();
    }
    std::println("growing: copies {} moves {}", Tracker::copies, Tracker::moves);
    Tracker::copies = 0;
    Tracker::moves = 0;
    Tracker r = make();
    std::println("returned: copies {} moves {}", Tracker::copies, Tracker::moves);
    auto p = std::make_unique<Tracker>();
    auto q = std::move(p);
    std::println("p {} q {}", p ? "owns" : "empty", q ? "owns" : "empty");
}