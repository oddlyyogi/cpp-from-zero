#include <print>
#include <string_view>

void use_after_free() {
    int* coat = new int(7);
    delete coat;
    std::println("{}", *coat);
}

void double_free() {
    int* coat = new int(7);
    delete coat;
    delete coat;
}

void overflow() {
    int* rack = new int[50]{};
    rack[50] = 1;
    delete[] rack;
}

void leak() {
    int* rack = new int[10]{};
    rack[0] = 1;
}

int main(int argc, char* argv[]) {
    std::string_view which = argc > 1 ? argv[1] : "";
    if (which == "use") use_after_free();
    if (which == "double") double_free();
    if (which == "overflow") overflow();
    if (which == "leak") leak();
}