#pragma once

#include <memory>
#include <string_view>

namespace loglens {

class Sink {
public:
    virtual ~Sink() = default;
    virtual void begin() {}
    virtual void end() {}
    virtual void row(std::string_view name, long long count, double share) = 0;
};


class TextSink : public Sink {
public:
    explicit TextSink(int percent_per_mark) : percent_per_mark_(percent_per_mark) {}
    void row(std::string_view name, long long count, double share) override;

private:
    int percent_per_mark_;
};


class CsvSink final : public Sink {
public:
    void begin() override;
    void row(std::string_view name, long long count, double share) override;
};


std::unique_ptr<Sink> make_sink(std::string_view format);

}  // namespace loglens