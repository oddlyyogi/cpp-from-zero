#include <print>
#include <string>

void put(const std::string& key, const std::string& value)
    pre(!key.empty())
    pre(!key.contains(' ')) {
    std::println("PUT {} {}", key, value);
}

int main() {
    put("user.ada", "admin");
    put("bad key", "oops");
}