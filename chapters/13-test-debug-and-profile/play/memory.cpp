#include <print>

int main() {
    int x = 42;
    int* p = &x;
    std::println("address {}  value {}", static_cast<const void*>(p), *p);
    *p = 7;
    std::println("x is now {}", x);
    const int* reader = &x;
    int* const pinned = &x;
    std::println("a pointer takes {} bytes, via reader {}", sizeof(reader), *reader + *pinned);
    int hooks[3] = {10, 20, 30};
    int* h = hooks;
    std::println("{} {}", *h, *(h + 1));
    int* coat = new int(7);
    std::println("coat {}", *coat);
    delete coat;
    int* rack = new int[50]{};
    rack[49] = 1;
    delete[] rack;
    int* none = nullptr;
    if (none == nullptr) {
        std::println("none points nowhere");
    }
}