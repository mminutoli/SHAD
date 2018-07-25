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

#include <numeric>

#include "gtest/gtest.h"

#include "common.hpp"
#include "stl_emulation/numeric.hpp"
using namespace shad_test_stl;

typedef ::testing::Types<std_vector_t> TestTypes;
TYPED_TEST_CASE(TestFixture, TestTypes);

///////////////////////////////////////
//
// accumulate
//
///////////////////////////////////////
TYPED_TEST(TestFixture, std_accumulate) {
  using it_t = typeof(this->in.begin());
  using val_t = it_value_t<TypeParam>;
  this->test(std::accumulate<it_t, val_t>, accumulate_<it_t, val_t>,
             make_val<val_t>(0));
}

///////////////////////////////////////
//
// reduce
//
///////////////////////////////////////
TYPED_TEST(TestFixture, std_reduce) {
  using it_t = typeof(this->in.begin());
  using val_t = it_value_t<TypeParam>;
  this->test(std::reduce<it_t>, reduce_<it_t>);
}
