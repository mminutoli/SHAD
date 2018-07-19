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

#include <functional>
#include <numeric>
#include <random>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

#include "common.hpp"
using namespace shad_test_stl;

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

// accumulate callable
template <typename T>
struct std_accumulate_ {
  template <typename It>
  T operator()(It begin, It end, T init) {
    return std::accumulate(begin, end, init);
  }
};

// // todo reduce callable - since c++17
// template <typename T>
// struct std_reduce_ {
//  template <typename It>
//  T operator()(It begin, It end, T init) {
//    return std::experimental::reduce(begin, end, init, std::plus<T>{});
//  }
//};

// value initialization
template <typename val_t>
val_t init_val_() {
  return val_t{0};
}

template <>
map_it_val_t init_val_<map_it_val_t>() {
  return map_it_val_t{0, 0};
}

// template test for checking find over iterators
template <typename T>
class NumericTests : public ::testing::Test {
 protected:
  template <typename F>
  void accumulate(F &&f) {
    // create the input containers
    auto in = create_container_<tag, T>{}(this->kNumElements);

    // accumulate
    auto obs = f(in.begin(), in.end(), init_val_<it_val_t>());

    // seq-for accumulation
    auto exp = init_val_<it_val_t>();
    for (auto &x : in) exp += x;

    // check correctness
    ASSERT_EQ(obs, exp);
  }

  template <typename F>
  void reduce(F &&f) {
    this->accumulate(f);
  }

  virtual ~NumericTests() {}

 private:
  using tag = typename ds_tag<T>::type;
  using it_t = typename T::iterator;
  using it_val_t = typename it_t::value_type;
  static constexpr size_t kNumElements = 1024;
};

//
// run
//
// todo add SHAD types
typedef ::testing::Types<std_vector_t> Types;

TYPED_TEST_CASE(NumericTests, Types);

// (sequential) std
TYPED_TEST(NumericTests, std) {
  using it_val_t = typename TypeParam::iterator::value_type;
  this->accumulate(std_accumulate_<it_val_t>{});
  // this->reduce(std_reduce_<it_val_t>{}); //todo
}

// todo std on shad
// todo sequential shad
// todo distributed shad
// todo distributed-async shad
