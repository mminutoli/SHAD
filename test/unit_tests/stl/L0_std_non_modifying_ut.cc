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

#include "common.hpp"
#include "stl_emulation/algorithm.hpp"
using namespace shad_test_stl;

typedef ::testing::Types<std_vector_t, std_unordered_map_t> TestTypes;
TYPED_TEST_CASE(TestFixture, TestTypes);

///////////////////////////////////////
//
// find_if, find_if_not
//
///////////////////////////////////////
TYPED_TEST(TestFixture, std_find_if) {
  using it_t = typeof(this->in.begin());

  // found
  this->test(std::find_if<it_t, is_even<it_value_t<TypeParam>>>,
             find_if_<it_t, is_even<it_value_t<TypeParam>>>,
             is_even<it_value_t<TypeParam>>{});

  // not found
  this->test(std::find_if<it_t, is_odd<it_value_t<TypeParam>>>,
             find_if_<it_t, is_odd<it_value_t<TypeParam>>>,
             is_odd<it_value_t<TypeParam>>{});
}

TYPED_TEST(TestFixture, std_find_if_not) {
  using it_t = typeof(this->in.begin());

  // not found
  this->test(std::find_if_not<it_t, is_even<it_value_t<TypeParam>>>,
             find_if_not_<it_t, is_even<it_value_t<TypeParam>>>,
             is_even<it_value_t<TypeParam>>{});

  // found
  this->test(std::find_if_not<it_t, is_odd<it_value_t<TypeParam>>>,
             find_if_not_<it_t, is_odd<it_value_t<TypeParam>>>,
             is_odd<it_value_t<TypeParam>>{});
}

///////////////////////////////////////
//
// all_of, any_of, none_of
//
///////////////////////////////////////
TYPED_TEST(TestFixture, std_all_of) {
  using it_t = typeof(this->in.begin());

  // true
  this->test(std::all_of<it_t, is_even<it_value_t<TypeParam>>>,
             all_of_<it_t, is_even<it_value_t<TypeParam>>>,
             is_even<it_value_t<TypeParam>>{});

  // false
  this->test(std::all_of<it_t, is_odd<it_value_t<TypeParam>>>,
             all_of_<it_t, is_odd<it_value_t<TypeParam>>>,
             is_odd<it_value_t<TypeParam>>{});
}

TYPED_TEST(TestFixture, std_any_of) {
  using it_t = typeof(this->in.begin());

  // true
  this->test(std::any_of<it_t, is_even<it_value_t<TypeParam>>>,
             any_of_<it_t, is_even<it_value_t<TypeParam>>>,
             is_even<it_value_t<TypeParam>>{});

  // false
  this->test(std::any_of<it_t, is_odd<it_value_t<TypeParam>>>,
             any_of_<it_t, is_odd<it_value_t<TypeParam>>>,
             is_odd<it_value_t<TypeParam>>{});
}

TYPED_TEST(TestFixture, std_none_of) {
  using it_t = typeof(this->in.begin());

  // false
  this->test(std::none_of<it_t, is_even<it_value_t<TypeParam>>>,
             none_of_<it_t, is_even<it_value_t<TypeParam>>>,
             is_even<it_value_t<TypeParam>>{});

  // true
  this->test(std::none_of<it_t, is_odd<it_value_t<TypeParam>>>,
             none_of_<it_t, is_odd<it_value_t<TypeParam>>>,
             is_odd<it_value_t<TypeParam>>{});
}

///////////////////////////////////////
//
// for_each, for_each_n - todo
//
///////////////////////////////////////

///////////////////////////////////////
//
// count, count_if
//
///////////////////////////////////////
TYPED_TEST(TestFixture, std_count) {
  using it_t = typeof(this->in.begin());

  // occurring
  this->test(std::count<it_t, it_value_t<TypeParam>>,
             count_<it_t, it_value_t<TypeParam>>,
             make_val<it_value_t<TypeParam>>(0));

  // not occurring
  this->test(std::count<it_t, it_value_t<TypeParam>>,
             count_<it_t, it_value_t<TypeParam>>,
             make_val<it_value_t<TypeParam>>(1));
}

TYPED_TEST(TestFixture, std_count_if) {
  using it_t = typeof(this->in.begin());

  // all
  this->test(std::count_if<it_t, is_even<it_value_t<TypeParam>>>,
             count_if_<it_t, is_even<it_value_t<TypeParam>>>,
             is_even<it_value_t<TypeParam>>{});

  // none
  this->test(std::count_if<it_t, is_odd<it_value_t<TypeParam>>>,
             count_if_<it_t, is_odd<it_value_t<TypeParam>>>,
             is_odd<it_value_t<TypeParam>>{});
}

///////////////////////////////////////
//
// mismatch - todo
//
///////////////////////////////////////

///////////////////////////////////////
//
// find
//
///////////////////////////////////////
TYPED_TEST(TestFixture, std_find) {
  using it_t = typeof(this->in.begin());

  // occurring
  this->test(std::find<it_t, it_value_t<TypeParam>>,
             find_<it_t, it_value_t<TypeParam>>,
             make_val<it_value_t<TypeParam>>(0));

  // not occurring
  this->test(std::find<it_t, it_value_t<TypeParam>>,
             find_<it_t, it_value_t<TypeParam>>,
             make_val<it_value_t<TypeParam>>(1));
}

///////////////////////////////////////
//
// find_end
//
///////////////////////////////////////
TYPED_TEST(TestFixture, std_find_end) {
  using it_t = typeof(this->in.begin());

  // occurring
  auto s = subseq_from_(this->in, this->kNumElements - 32, 32);
  this->test(std::find_end<it_t, it_t>, find_end_<it_t, it_t>, s.begin(),
             s.end());

  // not occurring
  s = create_container_<TypeParam>(32, false);
  this->test(std::find_end<it_t, it_t>, find_end_<it_t, it_t>, s.begin(),
             s.end());
}

///////////////////////////////////////
//
// find_first_of
//
///////////////////////////////////////
TYPED_TEST(TestFixture, std_find_first_of) {
  using it_t = typeof(this->in.begin());

  // occurring
  auto s = subseq_from_(this->in, this->kNumElements - 32, 32);
  this->test(std::find_first_of<it_t, it_t>, find_first_of_<it_t, it_t>,
             s.begin(), s.end());

  // not occurring
  s = create_container_<TypeParam>(32, false);
  this->test(std::find_first_of<it_t, it_t>, find_first_of_<it_t, it_t>,
             s.begin(), s.end());
}

///////////////////////////////////////
//
// adjacent_find
//
///////////////////////////////////////
TYPED_TEST(TestFixture, std_adjacent_find) {
  using it_t = typeof(this->in.begin());

  // none
  this->test(std::adjacent_find<it_t>, adjacent_find_<it_t>);

  // some - todo
}

///////////////////////////////////////
//
// search
//
///////////////////////////////////////
TYPED_TEST(TestFixture, std_search) {
  using it_t = typeof(this->in.begin());

  // occurring
  auto s = subseq_from_(this->in, this->kNumElements - 32, 32);
  this->test(std::search<it_t, it_t>, search_<it_t, it_t>, s.begin(), s.end());

  // not occurring
  s = create_container_<TypeParam>(32, false);
  this->test(std::search<it_t, it_t>, search_<it_t, it_t>, s.begin(), s.end());
}

///////////////////////////////////////
//
// search_n - todo check why failing
//
///////////////////////////////////////
// TYPED_TEST(AlgorithmTestFixture, std_search_n) {
//  using it_t = typeof(this->in.begin());
//  using val_t = it_value_t<TypeParam>;
//
//  for (size_t i = 0; i < 3; ++i) {
//    this->test(std::search_n<it_t, size_t, val_t>,
//               search_n_<it_t, size_t, val_t>, i, make_val<val_t>(0));
//    this->test(std::search_n<it_t, size_t, val_t>,
//               search_n_<it_t, size_t, val_t>, i, make_val<val_t>(1));
//  }
//}
