#include <meta>
#include <print>
#include <string_view>

enum class Level { Debug, Info, Warn, Error };

template <typename E>
constexpr std::string_view name_of(E value) {
    template for (constexpr auto e : std::define_static_array(std::meta::enumerators_of(^^E))) {
        if (value == [:e:]) {
            return std::meta::identifier_of(e);
        }
    }
    return "?";
}

int main() {
    for (Level l : {Level::Debug, Level::Info, Level::Warn, Level::Error}) {
        std::println("{}", name_of(l));
    }
    static_assert(name_of(Level::Warn) == "Warn");
}