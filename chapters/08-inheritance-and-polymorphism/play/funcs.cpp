#include <print>
#include <string_view>
#include <string>

void by_value(std::string note) {
    note += " (edited)";
}

void by_reference(std::string& note) {
    note += " (edited)";
}

void show(const std::string& note) {
    std::println("showing: {}", note);
}

[[nodiscard]] int twice(int n) {
    return 2 * n;
}

void describe(int n) {
    std::println("int {}", n);
}

void describe(double d) {
    std::println("double {}", d);
}

void banner(std::string_view title, int width = 20) {
    std::println("{:=^{}}", title, width);
}

int main() {
    std::string report = "draft";
    by_value(report);
    std::println("after by_value:     {}", report);
    by_reference(report);
    std::println("after by_reference: {}", report);
    std::println("twice(4) = {}", twice(4));
    show(report);
    describe(3);
    describe(2.5);
    banner("report");
    banner("report", 30);
}