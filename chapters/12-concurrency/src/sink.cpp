#include "sink.hpp"

#include <print>
#include <string>

namespace loglens {

void TextSink::row(std::string_view name, long long count, double share) {
    std::string bar(static_cast<int>(share / percent_per_mark_), '#');
    std::println("{:<6} {:>5} {:>6.1f}%  {}", name, count, share, bar);
}

void CsvSink::begin() {
    std::println("level,count,share");
}

void CsvSink::row(std::string_view name, long long count, double share) {
    std::println("{},{},{:.1f}", name, count, share);
}

std::unique_ptr<Sink> make_sink(std::string_view format) {
    if (format == "text") {
        return std::make_unique<TextSink>(2);
    }
    if (format == "csv") {
        return std::make_unique<CsvSink>();
    }
    return nullptr;
}

}  // namespace loglens