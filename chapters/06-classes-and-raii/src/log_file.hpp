#pragma once

#include <cstdio>
#include <string>

namespace loglens {

class LogFile {
public:
    explicit LogFile(const std::string& path);
    ~LogFile();

    LogFile(const LogFile&) = delete;
    LogFile& operator=(const LogFile&) = delete;

    bool is_open() const { return file_ != nullptr; }
    bool read_line(std::string& out);

private:
    std::FILE* file_ = nullptr;
};

}  // namespace loglens