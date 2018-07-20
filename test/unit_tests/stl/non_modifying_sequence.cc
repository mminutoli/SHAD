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

#include <random>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

#include "algorithm_wrappers.hpp"
#include "common.hpp"
using namespace shad_test_stl;

template <typename T>
class NonModifyingSequenceTest : public ::testing::Test {
 protected:
  virtual ~NonModifyingSequenceTest() {}
  static constexpr size_t kNumElements = 1024, num_objs = 128;
};

template <typename T>
class AllOfTest : public NonModifyingSequenceTest<T> {
  using tag = typename ds_tag<T>::type;
  using it_val_t = typename T::iterator::value_type;

 protected:
  template <typename F>
  void run(F &&f) {
    auto in = create_container_<tag, T>{}(this->kNumElements);

    // apply
    auto observed = f(in.begin(), in.end(), [](it_val_t &x) { return gtz(x); });

    // seq-for reference
    auto expected = true;
    for (auto &x : in) expected = expected && gtz(x);

    // check correctness
    ASSERT_EQ(observed, expected);
  }
};

template <typename T>
class AnyOfTest : public NonModifyingSequenceTest<T> {
  using tag = typename ds_tag<T>::type;
  using it_val_t = typename T::iterator::value_type;

 protected:
  template <typename F>
  void run(F &&f) {
    auto in = create_container_<tag, T>{}(this->kNumElements);

    // apply
    auto observed = f(in.begin(), in.end(), [](it_val_t &x) { return gtz(x); });

    // seq-for reference
    auto expected = false;
    for (auto &x : in) expected = expected || gtz(x);
  }
};

template <typename T>
class NoneOfTest : public NonModifyingSequenceTest<T> {
  using tag = typename ds_tag<T>::type;
  using it_val_t = typename T::iterator::value_type;

 protected:
  template <typename F>
  void run(F &&f) {
    auto in = create_container_<tag, T>{}(this->kNumElements);

    // apply
    auto observed = f(in.begin(), in.end(), [](it_val_t &x) { return gtz(x); });

    // seq-for reference
    auto expected = true;
    for (auto &x : in) expected = expected && gtz(x);
  }
};

template <typename T>
class FindTest : public NonModifyingSequenceTest<T> {
  using tag = typename ds_tag<T>::type;
  using it_t = typename T::iterator;
  using it_val_t = typename it_t::value_type;

 protected:
  template <typename F>
  void run(F &&f) {
    // create the input containers
    auto in = create_container_<tag, T>{}(this->kNumElements);
    auto objs = cherry_pick_<tag, T>{}(in);
    std::vector<it_t> observed(this->num_objs), expected(this->num_objs);

    // search
    auto obs_it = observed.begin();
    for (auto &obj : objs) *obs_it++ = f(in.begin(), in.end(), obj);

    // seq-for search
    auto exp_it = expected.begin();
    for (auto &obj : objs) {
      *exp_it = in.end();
      for (auto it = in.begin(); it != in.end(); ++it)
        if (*it == obj) {
          *exp_it = it;
          break;
        }
      ++exp_it;
    }

    // check correctness
    exp_it = expected.begin();
    for (auto &found_entry : observed) ASSERT_EQ(found_entry, *exp_it++);
  }
};

//
// run
//
// todo add SHAD types
typedef ::testing::Types<std_vector_t, std_unordered_map_t> AllTypes;
typedef ::testing::Types<std_vector_t> VectorTypes;
typedef ::testing::Types<std_unordered_map_t> MapTypes;

TYPED_TEST_CASE(AllOfTest, AllTypes);
TYPED_TEST(AllOfTest, std) {
  using it_val_t = typename TypeParam::iterator::value_type;
  this->run(std_all_of_<it_val_t>{});
}

TYPED_TEST_CASE(AnyOfTest, AllTypes);
TYPED_TEST(AnyOfTest, std) {
  using it_val_t = typename TypeParam::iterator::value_type;
  this->run(std_any_of_<it_val_t>{});
}

TYPED_TEST_CASE(NoneOfTest, AllTypes);
TYPED_TEST(NoneOfTest, std) {
  using it_val_t = typename TypeParam::iterator::value_type;
  this->run(std_none_of_<it_val_t>{});
}

TYPED_TEST_CASE(FindTest, AllTypes);
TYPED_TEST(FindTest, std) {
  using it_val_t = typename TypeParam::iterator::value_type;
  this->run(std_find_<it_val_t>{});
}

// todo sequential shad
// todo distributed shad
// todo distributed-async shad
