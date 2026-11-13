#include "entry.hpp"

#include <gtest/gtest.h>

TEST(ParseLine, ReadsAllFields) {
    auto entry = loglens::parse_line("2026-11-12 08:00:07 INFO  http: GET /loans 200 90ms");
    ASSERT_TRUE(entry.has_value());
    EXPECT_EQ(entry->date, "2026-11-12");
    EXPECT_EQ(entry->source, "http");
    EXPECT_EQ(entry->level, loglens::Level::Info);
    EXPECT_EQ(entry->message, "GET /loans 200 90ms");
}

TEST(ParseLine, RejectsShortTime) {
    auto entry = loglens::parse_line("2026-11-12 9:00 WARN db: slow");
    ASSERT_FALSE(entry.has_value());
    EXPECT_EQ(entry.error(), loglens::ParseError::BadTime);
}

struct BadCase {
    const char* name;
    const char* line;
    loglens::ParseError reason;
};

class BadLine : public ::testing::TestWithParam<BadCase> {};

TEST_P(BadLine, GivesTheReason) {
    const BadCase& c = GetParam();
    auto entry = loglens::parse_line(c.line);
    ASSERT_FALSE(entry.has_value()) << c.line;
    EXPECT_EQ(entry.error(), c.reason);
}

INSTANTIATE_TEST_SUITE_P(Malformed, BadLine, ::testing::Values(
    BadCase{"NoYear", "Nov 12 09:00:02 INFO  http: up", loglens::ParseError::BadDate},
    BadCase{"ShortTime", "2026-11-12 9:00 WARN db: slow", loglens::ParseError::BadTime},
    BadCase{"NoLevel", "2026-11-12 09:00:03", loglens::ParseError::NoLevel},
    BadCase{"NoColon", "2026-11-12 09:00:03 WARN  cache", loglens::ParseError::NoSource}),
    [](const auto& info) { return info.param.name; });