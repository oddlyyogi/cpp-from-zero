#include "counter.hpp"

#include <string>

#include <gtest/gtest.h>

TEST(Counter, AddsAndRanks) {
    loglens::Counter<std::string> counter;
    counter.add("db");
    counter.add("http", 3);
    counter.add("db");
    EXPECT_EQ(counter.count("db"), 2);
    EXPECT_EQ(counter.count("cache"), 0);
    auto top = counter.top(1);
    ASSERT_EQ(top.size(), 1u);
    EXPECT_EQ(top[0].first, "http");
}