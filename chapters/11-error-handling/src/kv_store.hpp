#pragma once

#include <optional>
#include <stdexcept>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace loglens {

class KvError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class KvStore {
public:
    explicit KvStore(std::string path);

    void put(const std::string& key, const std::string& value);
    bool del(const std::string& key);
    [[nodiscard]] std::optional<std::string> get(const std::string& key) const;
    [[nodiscard]] std::vector<std::string> keys() const;
    [[nodiscard]] std::size_t size() const { return index_.size(); }

private:
    void append(std::string_view record);

    std::string path_;
    std::unordered_map<std::string, std::string> index_;
};

}  // namespace loglens