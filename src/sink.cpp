#include "sink.hpp"

#include <print>
#include <string>

#include <nlohmann/json.hpp>

import loglens.bars;

namespace loglens {

void TextSink::row(std::string_view name, long long count, double share) {
    std::println("{:<6} {:>5} {:>6.1f}%  {}", name, count, share,
                 bar(share, percent_per_mark_));
}

void CsvSink::begin() {
    std::println("level,count,share");
}

void CsvSink::row(std::string_view name, long long count, double share) {
    std::println("{},{},{:.1f}", name, count, share);
}

void JsonSink::row(std::string_view name, long long count, double share) {
    rows_.push_back({std::string(name), count, share});
}

void JsonSink::end() {
    nlohmann::ordered_json doc = nlohmann::ordered_json::array();
    for (const Row& r : rows_) {
        doc.push_back({{"level", r.name}, {"count", r.count}, {"share", r.share}});
    }
    std::println("{}", doc.dump(2));
}

std::unique_ptr<Sink> make_sink(std::string_view format) {
    if (format == "text") {
        return std::make_unique<TextSink>(2);
    }
    if (format == "csv") {
        return std::make_unique<CsvSink>();
    }
    if (format == "json") {
        return std::make_unique<JsonSink>();
    }
    return nullptr;
}

}  // namespace loglens