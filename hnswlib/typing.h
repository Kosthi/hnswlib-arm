#pragma once

#include <cstdint>
#include <deque>
#include <queue>
#include <unordered_map>
#include <unordered_set>

// #include "allocator_wrapper.h"
// #include "nlohmann/json.hpp"

using InnerIdType =
    uint32_t;  // inner id's type; index's vector count may less than 2^31 - 1
using LabelType = int64_t;  // external id's type

// using JsonType = nlohmann::json;  // alias for nlohmann::json type
using BucketIdType = int32_t;

// template <typename T>
// using UnorderedSet =
//     std::unordered_set<T, std::hash<T>, std::equal_to<T>,
//     vsag::AllocatorWrapper<T>>;
//
// template <typename T>
// using Vector = std::vector<T, vsag::AllocatorWrapper<T>>;
//
// template <typename T>
// using Deque = std::deque<T, vsag::AllocatorWrapper<T>>;
//
// template <typename KeyType, typename ValType>
// using UnorderedMap = std::unordered_map<KeyType,
//                                         ValType,
//                                         std::hash<KeyType>,
//                                         std::equal_to<KeyType>,
//                                         vsag::AllocatorWrapper<std::pair<const
//                                         KeyType, ValType>>>;

// template <typename T, typename... Args>
// inline auto
// AllocateShared(Allocator* allocator, Args&&... args) {
//     return std::allocate_shared<T>(AllocatorWrapper<T>(allocator),
//     std::forward<Args>(args)...);
// }

using ConstParamMap =
    const std::unordered_map<std::string, std::vector<std::string>>;

struct CompareByFirst {
  constexpr bool operator()(
      std::pair<float, InnerIdType> const& a,
      std::pair<float, InnerIdType> const& b) const noexcept {
    return a.first < b.first;
  }
};

using MaxHeap = std::priority_queue<std::pair<float, InnerIdType>,
                                    std::vector<std::pair<float, InnerIdType>>,
                                    CompareByFirst>;
