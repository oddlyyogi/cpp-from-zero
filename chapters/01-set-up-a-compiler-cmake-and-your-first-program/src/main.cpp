#include <print>
#include <string_view>

std::string_view version();

int main() {
    std::println("loglens version {}", version());
    return 0;
}