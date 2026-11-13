#include "kv_store.hpp"

#include <algorithm>
#include <fstream>
#include <format>
#include <ranges>
#include <utility>

namespace loglens {

KvStore::KvStore(std::string path) : path_(std::move(path)) {
    std::ifstream in(path_);
    std::string line;
    int line_no = 0;
    while (std::getline(in, line)) {
        ++line_no;
        if (line.starts_with("PUT ")) {
            auto space = line.find(' ', 4);
            if (space == std::string::npos) {
                throw KvError(std::format("{} line {}: bad record '{}'", path_, line_no, line));
            }
            index_[line.substr(4, space - 4)] = line.substr(space + 1);
        } else if (line.starts_with("DEL ")) {
            index_.erase(line.substr(4));
        } else {
            throw KvError(std::format("{} line {}: bad record '{}'", path_, line_no, line));
        }
    }
}
void KvStore::put(const std::string& key, const std::string& value) {
    append("PUT " + key + " " + value);
    index_.insert_or_assign(key, value);
}

bool KvStore::del(const std::string& key) {
    if (index_.erase(key) == 0) {
        return false;
    }
    append("DEL " + key);
    return true;
}

std::optional<std::string> KvStore::get(const std::string& key) const {
    auto it = index_.find(key);
    if (it == index_.end()) {
        return std::nullopt;
    }
    return it->second;
}

std::vector<std::string> KvStore::keys() const {
    auto result = index_ | std::views::keys | std::ranges::to<std::vector>();
    std::ranges::sort(result);
    return result;
}

void KvStore::append(std::string_view record) {
    std::ofstream out(path_, std::ios::app);
    out << record << '\n';
}

}  // namespace loglens
