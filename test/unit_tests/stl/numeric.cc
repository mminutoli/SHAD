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
class NumericTest : public ::testing::Test {
 protected:
  virtual ~NumericTest() {}
  static constexpr size_t kNumElements = 1024;
};

template <typename T>
class AccumulateTest : public NumericTest<T> {
  using tag = typename ds_tag<T>::type;
  using it_val_t = typename T::iterator::value_type;

 protected:
  template <typename F>
  void run(F &&f) {
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
};

//
// run
//
// todo add SHAD types
typedef ::testing::Types<std_vector_t> VectorTypes;

TYPED_TEST_CASE(AccumulateTest, VectorTypes);
TYPED_TEST(AccumulateTest, std) {
  this->run(std::accumulate<it_t<TypeParam>, it_value_t<TypeParam>>);
}

// todo sequential shad
// todo distributed shad
// todo distributed-async shad
