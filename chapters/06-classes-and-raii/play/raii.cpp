#include <print>
#include <utility>
#include <string>

class Noisy {
public:
    explicit Noisy(std::string name) : name_(std::move(name)) {
        std::println("open {}", name_);
    }
    ~Noisy() {
        std::println("close {}", name_);
    }

private:
    std::string name_;
};

void greet(const Noisy&) {
    std::println("hello");
}

void process(bool fail) {
    Noisy file("file");
    if (fail) {
        std::println("giving up early");
        return;
    }
    std::println("finished");
}

int main() {
    Noisy a("a");
    {
        Noisy b("b");
    }
    Noisy c("c");
    std::println("end of main");
    process(false);
    process(true);
}