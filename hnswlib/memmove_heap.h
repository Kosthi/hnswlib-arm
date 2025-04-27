#pragma once

#include <queue>

#include "distance_heap.h"

template <bool max_heap = true, bool fixed_size = true>
class MemmoveHeap : public DistanceHeap {
 public:
 public:
  MemmoveHeap(int64_t max_size);

  void push(float dist, InnerIdType id) override;

  void emplace(float dist, InnerIdType id);

  [[nodiscard]] const DistanceRecord& top() const override {
    return this->ordered_buffer_[cur_size_ - 1];
  }

  void pop() override { cur_size_--; }

  [[nodiscard]] uint64_t size() const override { return this->cur_size_; }

  [[nodiscard]] bool empty() const override { return this->cur_size_ == 0; }

 private:
  std::vector<DistanceRecord> ordered_buffer_;

  int64_t cur_size_{0};
};

template <bool max_heap, bool fixed_size>
MemmoveHeap<max_heap, fixed_size>::MemmoveHeap(int64_t max_size)
    : DistanceHeap(max_size), ordered_buffer_() {
  if constexpr (fixed_size) {
    ordered_buffer_.resize(max_size + 1);
  }
}

template <bool max_heap, bool fixed_size>
void MemmoveHeap<max_heap, fixed_size>::push(float dist, InnerIdType id) {
  using CompareType =
      typename std::conditional<max_heap, CompareMax, CompareMin>::type;
  if constexpr (fixed_size) {
    if (this->size() < max_size_ or (dist < this->top().first) == max_heap) {
      DistanceRecord record = {dist, id};
      auto pos = std::upper_bound(this->ordered_buffer_.begin(),
                                  this->ordered_buffer_.begin() + cur_size_,
                                  record, CompareType()) -
                 this->ordered_buffer_.begin();
      // NOLINTNEXTLINE(bugprone-undefined-memory-manipulation)
      std::memmove(ordered_buffer_.data() + pos + 1,
                   ordered_buffer_.data() + pos,
                   (max_size_ - pos) * sizeof(DistanceRecord));
      ordered_buffer_[pos] = record;
      this->cur_size_++;
      if (this->size() > this->max_size_) {
        this->pop();
      }
    }
  } else {
    DistanceRecord record = {dist, id};
    auto pos =
        std::upper_bound(this->ordered_buffer_.begin(),
                         this->ordered_buffer_.end(), record, CompareType()) -
        this->ordered_buffer_.begin();
    ordered_buffer_.emplace_back(record);
    // NOLINTNEXTLINE(bugprone-undefined-memory-manipulation)
    std::memmove(ordered_buffer_.data() + pos + 1, ordered_buffer_.data() + pos,
                 (cur_size_ - pos) * sizeof(DistanceRecord));
    ordered_buffer_[pos] = record;
    cur_size_++;
  }
}

template <bool max_heap, bool fixed_size>
void MemmoveHeap<max_heap, fixed_size>::emplace(float dist, InnerIdType id) {
  push(dist, id);
}
