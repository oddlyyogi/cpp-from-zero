#pragma once

#include <algorithm>
#include <concepts>
#include <cstddef>
#include <utility>
#include <vector>

namespace loglens {

template <std::equality_comparable Key>
class Counter {
public:
    void add(const Key& key, long long n = 1) {
        for (auto& [k, count] : entries_) {
            if (k == key) {
                count += n;
                return;
            }
        }
        entries_.emplace_back(key, n);
    }
    [[nodiscard]] long long count(const Key& key) const {
        for (const auto& [k, c] : entries_) {
            if (k == key) {
                return c;
            }
        }
        return 0;
    }

    [[nodiscard]] std::vector<std::pair<Key, long long>> top(std::size_t n) const {
        auto sorted = entries_;
        std::stable_sort(sorted.begin(), sorted.end(), more);
        if (sorted.size() > n) {
            sorted.resize(n);
        }
        return sorted;
    }

private:
    static bool more(const std::pair<Key, long long>& a, const std::pair<Key, long long>& b) {
        return a.second > b.second;
    }

    std::vector<std::pair<Key, long long>> entries_;

};

}  // namespace loglens