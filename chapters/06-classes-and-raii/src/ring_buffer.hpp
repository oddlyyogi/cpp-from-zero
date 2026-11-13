#pragma once

#include <cstddef>

namespace loglens {

class RingBuffer {
public:
    explicit RingBuffer(std::size_t capacity);
    ~RingBuffer();
    RingBuffer(const RingBuffer& other);
    RingBuffer& operator=(const RingBuffer& other);

    void push(int value);
    std::size_t size() const;
    int at(std::size_t i) const;

private:
    std::size_t capacity_;
    int* data_;
    std::size_t count_ = 0;
};

}  // namespace loglens