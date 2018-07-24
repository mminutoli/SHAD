//===------------------------------------------------------------*- C++ -*-===//
//
//                                     SHAD
//
//      The Scalable High-performance Algorithms and Data Structure Library
//
//===----------------------------------------------------------------------===//
//
// Copyright 2018 Battelle Memorial Institute
//
// Licensed under the Apache License, Version 2.0 (the "License"); you may not
// use this file except in compliance with the License. You may obtain a copy
// of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
// WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
// License for the specific language governing permissions and limitations
// under the License.
//
//===----------------------------------------------------------------------===//

#ifndef TEST_UNIT_TESTS_STL_COMMON_HPP_
#define TEST_UNIT_TESTS_STL_COMMON_HPP_

#include <random>
#include <unordered_map>
#include <vector>

#include "ds_tag.hpp"

namespace shad_test_stl {

// benchmark registration utilities
constexpr uint32_t BENCHMARK_MIN_SIZE = 1024;
constexpr uint32_t BENCHMARK_MAX_SIZE = 64 << 20;

// typing utilities
template <typename T>
using it_t = typename T::iterator;

template <typename T>
using it_value_t = typename T::iterator::value_type;

// types for data structures and iterators
// todo add SHAD types
using std_vector_t = std::vector<int>;
using std_unordered_map_t = std::unordered_map<int, int>;

using vector_it_val_t = typename std_vector_t::iterator::value_type;
using map_it_val_t = typename std_unordered_map_t::iterator::value_type;

// random value generation
template <typename tag, typename value_t>
struct random_value_ {
  value_t operator()(std::mt19937 &rng) {
    assert(false);
    return value_t{};
  }
};

template <typename value_t>
struct random_value_<vector_tag, value_t> {
  value_t operator()(std::mt19937 &rng) {
    std::uniform_int_distribution<int> dist{-128, 128};
    return value_t{dist(rng)};
  }
};

template <typename value_t>
struct random_value_<map_tag, value_t> {
  value_t operator()(std::mt19937 &rng) {
    std::uniform_int_distribution<int> dist{-128, 128};
    return value_t{dist(rng), dist(rng)};
  }
};

// value insertion
template <typename tag, typename T>
struct insert_value_ {
  void operator()(T &, const typename T::iterator::value_type) {}
};

template <typename T>
struct insert_value_<vector_tag, T> {
  void operator()(T &in, const typename T::iterator::value_type &val) {
    in.push_back(val);
  }
};

template <typename T>
struct insert_value_<map_tag, T> {
  void operator()(T &in, const typename T::iterator::value_type &val) {
    in[val.first] = val.second;
  }
};

// container creation
template <typename T>
T create_container_(size_t size) {
  using tag = typename ds_tag<T>::type;
  T res;
  std::mt19937 rng;
  for (auto i = size; i > 0; --i)
    insert_value_<tag, T>{}(res, random_value_<tag, it_value_t<T>>{}(rng));
  return res;
}
}  // namespace shad_test_stl

#endif
