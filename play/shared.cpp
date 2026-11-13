#include <memory>
#include <print>
#include <string>

struct Node {
    std::string name;
    std::shared_ptr<Node> next;
    std::weak_ptr<Node> back;
};

int main() {
    auto a = std::make_shared<Node>("a");
    auto b = std::make_shared<Node>("b");
    b->next = a;
    std::println("a is owned {} times", a.use_count());
    a->back = b;
    if (auto other = a->back.lock()) {
        std::println("a can still reach {}", other->name);
    }
}