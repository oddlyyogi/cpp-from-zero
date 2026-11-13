#include <print>
#include <variant>

struct Text {
    int percent_per_mark = 2;
};
struct Csv {
    char separator = ',';
};

using Format = std::variant<Text, Csv>;

struct Describe {
    void operator()(const Text& t) const { std::println("text, {}%", t.percent_per_mark); }
    void operator()(const Csv& c) const { std::println("csv, separator {}", c.separator); }
};

int main() {
    Format f = Csv{};
    std::visit(Describe{}, f);
    f = Text{};
    std::visit(Describe{}, f);
    std::println("holds Text: {}", std::holds_alternative<Text>(f));
    if (auto* t = std::get_if<Text>(&f)) {
        std::println("marks every {}%", t->percent_per_mark);
    }
}