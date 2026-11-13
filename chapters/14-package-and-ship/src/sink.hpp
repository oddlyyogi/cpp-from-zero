#pragma once

#include <memory>
#include <string>
#include <string_view>
#include <vector>

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


class JsonSink final : public Sink {
public:
    void row(std::string_view name, long long count, double share) override;
    void end() override;

private:
    struct Row {
        std::string name;
        long long count;
        double share;
    };
    std::vector<Row> rows_;
};

std::unique_ptr<Sink> make_sink(std::string_view format);

}  // namespace loglens