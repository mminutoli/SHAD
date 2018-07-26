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

#include <algorithm>

#include "gtest/gtest.h"

#include "common.h"
#include "stl_emulation/algorithm.h"

template <typename T>
using TF = shad_test_stl::TestFixture<T>;

using TestTypes =
    ::testing::Types<shad_test_stl::std_vector_t, shad_test_stl::std_set_t>;
TYPED_TEST_CASE(TF, TestTypes);

///////////////////////////////////////
//
// min_element
//
///////////////////////////////////////
TYPED_TEST(TF, std_min_element) {
  using it_t = typeof(this->in.begin());
  this->test(std::min_element<it_t>, shad_test_stl::min_element_<it_t>);
}

///////////////////////////////////////
//
// max_element
//
///////////////////////////////////////
TYPED_TEST(TF, std_max_element) {
  using it_t = typeof(this->in.begin());
  this->test(std::max_element<it_t>, shad_test_stl::max_element_<it_t>);
}

///////////////////////////////////////
//
// minmax_element
//
///////////////////////////////////////
TYPED_TEST(TF, std_minmax_element) {
  using it_t = typeof(this->in.begin());
  this->test(std::minmax_element<it_t>, shad_test_stl::minmax_element_<it_t>);
}
