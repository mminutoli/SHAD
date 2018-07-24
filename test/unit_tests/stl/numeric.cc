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
class NumericTestFixture : public ::testing::Test {
 public:
  void SetUp() { in = create_container_<T>(this->kNumElements); }

 protected:
  virtual ~NumericTestFixture() {}
  static constexpr size_t kNumElements = 1024;
  T in;
};

template <typename T>
class AccumulateTest : public NumericTestFixture<T> {
 protected:
  template <typename F>
  void run(F &&f) {
    auto init_val = init_val_<typename T::iterator::value_type>();
    auto obs = f(this->in.begin(), this->in.end(), init_val);
    auto exp = accumulate_(this->in.begin(), this->in.end(), init_val);
    ASSERT_EQ(obs, exp);
  }

 private:
  template <class InputIt, class T_>
  T_ accumulate_(InputIt first, InputIt last, T_ init) {
    for (; first != last; ++first) {
      init = std::move(init) + *first;
    }
    return init;
  }
};

template <typename T>
class ReduceTest : public NumericTestFixture<T> {
 protected:
  template <typename F>
  void run(F &&f) {
    auto obs = f(this->in.begin(), this->in.end());
    auto exp = reduce_(this->in.begin(), this->in.end());
    ASSERT_EQ(obs, exp);
  }

 private:
  template <class InputIt>
  typename T::iterator::value_type reduce_(InputIt first, InputIt last) {
    assert(first != last);
    auto init = *first++;
    for (; first != last; ++first) {
      init = std::move(init) + *first;
    }
    return init;
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

TYPED_TEST_CASE(ReduceTest, VectorTypes);
TYPED_TEST(ReduceTest, std) {
  this->run(std::reduce<it_t<TypeParam>>);
}

// todo sequential shad
// todo distributed shad
// todo distributed-async shad
