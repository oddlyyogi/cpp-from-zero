#pragma once

#include <algorithm>
#include <concepts>
#include <cstddef>
#include <unordered_map>
#include <utility>
#include <vector>

namespace loglens {

template <std::equality_comparable Key>
class Counter {
public:
    void add(const Key& key, long long n = 1) {
        auto [it, inserted] = where_.try_emplace(key, entries_.size());
        if (inserted) {
            entries_.emplace_back(key, n);
        } else {
            entries_[it->second].second += n;
        }
    }
    [[nodiscard]] long long count(const Key& key) const {
        auto it = where_.find(key);
        return it == where_.end() ? 0 : entries_[it->second].second;
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
    std::unordered_map<Key, std::size_t> where_;

};

}  // namespace loglens