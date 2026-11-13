module;

#include <cstddef>
#include <string>

export module loglens.bars;

export namespace loglens {

std::string bar(double share, int percent_per_mark) {
    return std::string(static_cast<std::size_t>(share / percent_per_mark), '#');
}
}  // namespace loglens