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

#include <unordered_map>
#include <vector>

#include "ds_tag.hpp"

namespace shad_test_stl {

// types for data structures and iterators
// todo add SHAD types
using std_vector_t = std::vector<int>;
using std_unordered_map_t = std::unordered_map<int, int>;

using vector_it_val_t = typename std_vector_t::iterator::value_type;
using map_it_val_t = typename std_unordered_map_t::iterator::value_type;

// container creation
template <typename tag, typename T>
struct create_container_ {
  T operator()(size_t) {
    assert(false);
    return T{};
  }
};

template <typename T>
struct create_container_<vector_tag, T> {
  T operator()(size_t size) {
    T res;
    std::mt19937 rng;
    std::uniform_int_distribution<int> dist{-128, 128};
    for (auto i = size; i > 0; --i) res.push_back(dist(rng));
    return res;
  }
};

template <typename T>
struct create_container_<map_tag, T> {
  T operator()(size_t size) {
    T res;
    std::mt19937 rng;
    std::uniform_int_distribution<int> dist{-128, 128};
    for (auto i = size; i > 0; --i) res[dist(rng)] = dist(rng);
    return res;
  }
};

// random selection from containers
template <typename tag, typename T>
struct cherry_pick_ {
  std::vector<typename T::iterator::value_type> operator()(const T &in) {
    assert(false);
    return T{};
  }
};

template <typename T>
struct cherry_pick_<vector_tag, T> {
  std::vector<vector_it_val_t> operator()(const T &in) {
    std::vector<vector_it_val_t> res;
    std::mt19937 rng;
    std::uniform_int_distribution<int> pick_dist{0, 1};
    std::uniform_int_distribution<int> poison_dist{-10, 10};
    for (auto it = in.begin(); it != in.end(); ++it) {
      if (pick_dist(rng))
        res.push_back(*it);
      else
        res.push_back(vector_it_val_t{poison_dist(rng)});
    }
    return res;
  }
};

template <typename T>
struct cherry_pick_<map_tag, T> {
  std::vector<map_it_val_t> operator()(const T &in) {
    std::vector<map_it_val_t> res;
    std::mt19937 rng;
    std::uniform_int_distribution<int> pick_dist{0, 1};
    std::uniform_int_distribution<int> poison_dist{-10, 10};
    for (auto it = in.begin(); it != in.end(); ++it) {
      if (pick_dist(rng))
        res.push_back(*it);
      else
        res.push_back(map_it_val_t{poison_dist(rng), poison_dist(rng)});
    }
    return res;
  }
};

template <typename T>
bool gtz(const T &x) {
  return x > 0;
}

template <>
bool gtz<map_it_val_t>(const map_it_val_t &x) {
  return x.second > 0;
}
}  // namespace shad_test_stl

#endif
