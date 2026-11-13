#include <memory>
#include <string>
#include <print>

class Appliance {
public:
    virtual ~Appliance() = default;
    virtual void power_on() const = 0;
    void label() const { std::println("appliance label"); }
};

class Kettle : public Appliance {
public:
    void power_on() const override { std::println("kettle boils water"); }
    void label() const { std::println("kettle label"); }
    std::string note = std::string(100, '~');
};

struct Shape {
    virtual ~Shape() = default;
    virtual std::string name() const { return "shape"; }
};
struct Circle : Shape {
    std::string name() const override { return "circle"; }
};

int main() {
    Kettle k;
    const Appliance& a = k;
    a.power_on();
    a.label();
    Circle circle;
    const Shape& ref = circle;
    Shape copy = circle;
    std::println("{} {}", ref.name(), copy.name());
    std::unique_ptr<Appliance> owned = std::make_unique<Kettle>();
    owned->power_on();
    if (auto* kettle = dynamic_cast<Kettle*>(owned.get())) {
        std::println("it is a kettle: {} characters of note", kettle->note.size());
    }
}