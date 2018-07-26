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

#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

#include "common.hpp"

template <typename T>
using TF = shad_test_stl::TestFixture<T>;

using TestTypes = ::testing::Types<shad_test_stl::std_vector_t>;
TYPED_TEST_CASE(TF, TestTypes);

TYPED_TEST(TF, for_deref) {
  int64_t obs_checksum = 0;
  for (auto it = this->in.begin(); it != this->in.end(); ++it)
    obs_checksum += shad_test_stl::val_to_int_(*it);
  ASSERT_EQ(obs_checksum,
            shad_test_stl::expected_checksum<TypeParam>(this->kNumElements));
}

TYPED_TEST(TF, for_const_deref) {
  int64_t obs_checksum = 0;
  for (auto it = this->in.cbegin(); it != this->in.cend(); ++it)
    obs_checksum += shad_test_stl::val_to_int_(*it);
  ASSERT_EQ(obs_checksum,
            shad_test_stl::expected_checksum<TypeParam>(this->kNumElements));
}

TYPED_TEST(TF, for_inc_deref) {
  int64_t obs_checksum = 0;
  auto it = this->in.begin();
  while (it != this->in.cend())
    obs_checksum += shad_test_stl::val_to_int_(*it++);
  ASSERT_EQ(obs_checksum,
            shad_test_stl::expected_checksum<TypeParam>(this->kNumElements));
}

// todo test arrow dereferencing
