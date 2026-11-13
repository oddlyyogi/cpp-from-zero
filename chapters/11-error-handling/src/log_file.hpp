#pragma once

#include <cstdio>
#include <string>
#include <memory>

namespace loglens {

struct FileCloser {
    void operator()(std::FILE* f) const noexcept { std::fclose(f); }
};

class LogFile {
public:
    explicit LogFile(const std::string& path);

    bool is_open() const { return file_ != nullptr; }
    bool read_line(std::string& out);

private:
    std::unique_ptr<std::FILE, FileCloser> file_;
};

}  // namespace loglens