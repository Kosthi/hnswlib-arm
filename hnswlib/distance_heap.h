#pragma once

#include <type_traits>
#include <utility>

#include "typing.h"
// #include "vsag/allocator.h"

class DistanceHeap {
 public:
  using DistanceRecord = std::pair<float, InnerIdType>;

  template <class HeapImpl>
  HeapImpl& GetImpl() {
    return static_cast<HeapImpl>(*this);
  }

  struct CompareMax {
    constexpr bool operator()(DistanceRecord const& a,
                              DistanceRecord const& b) const noexcept {
      return a.first < b.first;
    }
  };

  struct CompareMin {
    constexpr bool operator()(DistanceRecord const& a,
                              DistanceRecord const& b) const noexcept {
      return a.first > b.first;
    }
  };

 public:
  DistanceHeap(int64_t max_size = -1) : max_size_(max_size) {};

  virtual void push(const DistanceRecord& record) {
    return this->push(record.first, record.second);
  }

  virtual void push(float dist, InnerIdType id) = 0;

  [[nodiscard]] virtual const DistanceRecord& top() const = 0;

  virtual void pop() = 0;

  [[nodiscard]] virtual uint64_t size() const = 0;

  [[nodiscard]] virtual bool empty() const = 0;

 protected:
  // Allocator* allocator_{nullptr};
  int64_t max_size_{-1};
};

using DistHeapPtr = std::shared_ptr<DistanceHeap>;
