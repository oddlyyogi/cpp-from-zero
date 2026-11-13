#include "ring_buffer.hpp"

#include <algorithm>
#include <utility>

namespace loglens {

RingBuffer::RingBuffer(std::size_t capacity)
    : capacity_(std::max<std::size_t>(capacity, 1)), data_(new int[capacity_]{}) {}

RingBuffer::~RingBuffer() {
    delete[] data_;
}

RingBuffer::RingBuffer(const RingBuffer& other)
    : capacity_(other.capacity_), data_(new int[capacity_]), count_(other.count_) {
    std::copy(other.data_, other.data_ + capacity_, data_);
}

RingBuffer::RingBuffer(RingBuffer&& other) noexcept
    : capacity_(other.capacity_),
      data_(std::exchange(other.data_, nullptr)),
      count_(std::exchange(other.count_, 0)) {}


RingBuffer& RingBuffer::operator=(RingBuffer&& other) noexcept {
    if (this != &other) {
        delete[] data_;
        capacity_ = other.capacity_;
        data_ = std::exchange(other.data_, nullptr);
        count_ = std::exchange(other.count_, 0);
    }
    return *this;
}

RingBuffer& RingBuffer::operator=(const RingBuffer& other) {
    RingBuffer copy(other);
    std::swap(data_, copy.data_);
    std::swap(capacity_, copy.capacity_);
    std::swap(count_, copy.count_);
    return *this;
}

void RingBuffer::push(int value) {
    data_[count_ % capacity_] = value;
    ++count_;
}

std::size_t RingBuffer::size() const {
    return std::min(count_, capacity_);
}

int RingBuffer::at(std::size_t i) const {
    return data_[(count_ - size() + i) % capacity_];
}

}  // namespace loglens