#include "log_file.hpp"

namespace loglens {

LogFile::LogFile(const std::string& path) : file_(std::fopen(path.c_str(), "r")) {}

LogFile::~LogFile() {
    if (file_ != nullptr) {
        std::fclose(file_);
    }
}

bool LogFile::read_line(std::string& out) {
    out.clear();
    int c = 0;
    while ((c = std::fgetc(file_)) != EOF) {
        if (c == '\n') {
            return true;
        }
        out += static_cast<char>(c);
    }
    return !out.empty();
}

}  // namespace loglens