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

#include "gtest/gtest.h"

#include "ds_tag.hpp"

namespace shad_test_stl {

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

typedef ::testing::Types<std_vector_t, std_unordered_map_t> AllTypes;
typedef ::testing::Types<std_vector_t> VectorTypes;
// todo add SHADTypes/SHADVectorTypes

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

// random selection from containers
template <typename T>
std::vector<it_value_t<T>> cherry_pick_(const T &in) {
  using tag = typename ds_tag<T>::type;
  std::vector<it_value_t<T>> res;
  std::mt19937 rng;
  std::uniform_int_distribution<int> pick_dist{0, 1};
  for (auto it = in.begin(); it != in.end(); ++it) {
    if (pick_dist(rng))
      res.push_back(*it);
    else
      res.push_back(random_value_<tag, it_value_t<T>>{}(rng));
  }
  return res;
}

// random sub-sequencing from containers
template <typename T>
T maybe_subseq_from_(const T &in, size_t start_idx) {
  using tag = typename ds_tag<T>::type;
  T res;
  std::mt19937 rng;
  std::uniform_int_distribution<int> pick_dist{0, 1};
  std::uniform_int_distribution<int> continue_dist{0, 10};

  // move to starting point
  auto first = in.begin();
  size_t i = 0;
  while (i++ < start_idx && first != in.end()) ++first;

  while (first != in.end()) {
    if (!continue_dist(rng)) break;
    if (pick_dist(rng))
      insert_value_<tag, T>{}(res, *first);
    else
      insert_value_<tag, T>{}(res, random_value_<tag, it_value_t<T>>{}(rng));
    ++first;
  }
  return res;
}

template <typename T>
struct is_even {
  bool operator()(const T &x) { return !(x % 2); }
};

template <>
struct is_even<map_it_val_t> {
  bool operator()(const map_it_val_t &x) { return is_even<int>{}(x.second); }
};

template <typename T>
T sum(const T &x, const T &y) {
  return x + y;
}

template <>
map_it_val_t sum<map_it_val_t>(const map_it_val_t &x, const map_it_val_t &y) {
  return map_it_val_t{sum(x.first, y.first), sum(x.second, y.second)};
}
}  // namespace shad_test_stl

#endif
