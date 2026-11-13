#include "kv_store.hpp"
#include "ring_buffer.hpp"

#include <filesystem>
#include <fstream>

#include <gtest/gtest.h>

class KvStoreTest : public ::testing::Test {
protected:
    void SetUp() override {
        dir_ = std::filesystem::temp_directory_path() / "loglens_test";
        std::filesystem::create_directories(dir_);
        path_ = (dir_ / "test.kv").string();
        std::filesystem::remove(path_);
    }
    void TearDown() override { std::filesystem::remove_all(dir_); }

    std::filesystem::path dir_;
    std::string path_;
};

TEST_F(KvStoreTest, PutThenGet) {
    loglens::KvStore store(path_);
    store.put("user.ada", "admin");
    EXPECT_EQ(store.get("user.ada"), "admin");
    EXPECT_EQ(store.get("nobody"), std::nullopt);
}

TEST_F(KvStoreTest, SurvivesReopen) {
    {
        loglens::KvStore store(path_);
        store.put("theme", "dark");
        store.put("theme", "light");
    }
    loglens::KvStore again(path_);
    EXPECT_EQ(again.get("theme"), "light");
    EXPECT_EQ(again.size(), 1u);
}

TEST_F(KvStoreTest, BadRecordThrows) {
    std::ofstream(path_) << "PUT ok yes\nOOPS\n";
    EXPECT_THROW(loglens::KvStore store(path_), loglens::KvError);
}

TEST(RingBuffer, KeepsLastValues) {
    loglens::RingBuffer ring(3);
    for (int i = 1; i <= 5; ++i) {
        ring.push(i);
    }
    ASSERT_EQ(ring.size(), 3u);
    EXPECT_EQ(ring.at(0), 3);
    EXPECT_EQ(ring.at(2), 5);
}