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

template <typename T>
using TF = shad_test_stl::TestFixture<T>;

using TestTypes = ::testing::Types<shad_test_stl::std_vector_t>;
TYPED_TEST_CASE(TF, TestTypes);

///////////////////////////////////////
//
// find_if, find_if_not
//
///////////////////////////////////////
TYPED_TEST(TF, std_find_if) {
  using it_t = typeof(this->in.begin());
  using value_t = typeof(*this->in.begin());

  // found
  this->test(std::find_if<it_t, shad_test_stl::is_even<value_t>>,
             shad_test_stl::find_if_<it_t, shad_test_stl::is_even<value_t>>,
             shad_test_stl::is_even<value_t>{});

  // not found
  this->test(std::find_if<it_t, shad_test_stl::is_odd<value_t>>,
             shad_test_stl::find_if_<it_t, shad_test_stl::is_odd<value_t>>,
             shad_test_stl::is_odd<value_t>{});
}

TYPED_TEST(TF, std_find_if_not) {
  using it_t = typeof(this->in.begin());
  using value_t = typeof(*this->in.begin());

  // not found
  this->test(std::find_if_not<it_t, shad_test_stl::is_even<value_t>>,
             shad_test_stl::find_if_not_<it_t, shad_test_stl::is_even<value_t>>,
             shad_test_stl::is_even<value_t>{});

  // found
  this->test(std::find_if_not<it_t, shad_test_stl::is_odd<value_t>>,
             shad_test_stl::find_if_not_<it_t, shad_test_stl::is_odd<value_t>>,
             shad_test_stl::is_odd<value_t>{});
}

///////////////////////////////////////
//
// all_of, any_of, none_of
//
///////////////////////////////////////
TYPED_TEST(TF, std_all_of) {
  using it_t = typeof(this->in.begin());
  using value_t = typeof(*this->in.begin());

  // true
  this->test(std::all_of<it_t, shad_test_stl::is_even<value_t>>,
             shad_test_stl::all_of_<it_t, shad_test_stl::is_even<value_t>>,
             shad_test_stl::is_even<value_t>{});

  // false
  this->test(std::all_of<it_t, shad_test_stl::is_odd<value_t>>,
             shad_test_stl::all_of_<it_t, shad_test_stl::is_odd<value_t>>,
             shad_test_stl::is_odd<value_t>{});
}

TYPED_TEST(TF, std_any_of) {
  using it_t = typeof(this->in.begin());
  using value_t = typeof(*this->in.begin());

  // true
  this->test(std::any_of<it_t, shad_test_stl::is_even<value_t>>,
             shad_test_stl::any_of_<it_t, shad_test_stl::is_even<value_t>>,
             shad_test_stl::is_even<value_t>{});

  // false
  this->test(std::any_of<it_t, shad_test_stl::is_odd<value_t>>,
             shad_test_stl::any_of_<it_t, shad_test_stl::is_odd<value_t>>,
             shad_test_stl::is_odd<value_t>{});
}

TYPED_TEST(TF, std_none_of) {
  using it_t = typeof(this->in.begin());
  using value_t = typeof(*this->in.begin());

  // false
  this->test(std::none_of<it_t, shad_test_stl::is_even<value_t>>,
             shad_test_stl::none_of_<it_t, shad_test_stl::is_even<value_t>>,
             shad_test_stl::is_even<value_t>{});

  // true
  this->test(std::none_of<it_t, shad_test_stl::is_odd<value_t>>,
             shad_test_stl::none_of_<it_t, shad_test_stl::is_odd<value_t>>,
             shad_test_stl::is_odd<value_t>{});
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
TYPED_TEST(TF, std_count) {
  using it_t = typeof(this->in.begin());
  using value_t = typeof(*this->in.begin());

  // occurring
  this->test(std::count<it_t, value_t>, shad_test_stl::count_<it_t, value_t>,
             shad_test_stl::make_val<value_t>(0));

  // not occurring
  this->test(std::count<it_t, value_t>, shad_test_stl::count_<it_t, value_t>,
             shad_test_stl::make_val<value_t>(1));
}

TYPED_TEST(TF, std_count_if) {
  using it_t = typeof(this->in.begin());
  using value_t = typeof(*this->in.begin());

  // all
  this->test(std::count_if<it_t, shad_test_stl::is_even<value_t>>,
             shad_test_stl::count_if_<it_t, shad_test_stl::is_even<value_t>>,
             shad_test_stl::is_even<value_t>{});

  // none
  this->test(std::count_if<it_t, shad_test_stl::is_odd<value_t>>,
             shad_test_stl::count_if_<it_t, shad_test_stl::is_odd<value_t>>,
             shad_test_stl::is_odd<value_t>{});
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
TYPED_TEST(TF, std_find) {
  using it_t = typeof(this->in.begin());
  using value_t = typeof(*this->in.begin());

  // occurring
  this->test(std::find<it_t, value_t>, shad_test_stl::find_<it_t, value_t>,
             shad_test_stl::make_val<value_t>(0));

  // not occurring
  this->test(std::find<it_t, value_t>, shad_test_stl::find_<it_t, value_t>,
             shad_test_stl::make_val<value_t>(1));
}

///////////////////////////////////////
//
// find_end
//
///////////////////////////////////////
TYPED_TEST(TF, std_find_end) {
  using it_t = typeof(this->in.begin());

  // occurring
  auto s = shad_test_stl::subseq_from_(this->in, this->kNumElements - 32, 32);
  this->test(std::find_end<it_t, it_t>, shad_test_stl::find_end_<it_t, it_t>,
             s.begin(), s.end());

  // not occurring
  s = shad_test_stl::create_container_<TypeParam>(32, false);
  this->test(std::find_end<it_t, it_t>, shad_test_stl::find_end_<it_t, it_t>,
             s.begin(), s.end());
}

///////////////////////////////////////
//
// find_first_of
//
///////////////////////////////////////
TYPED_TEST(TF, std_find_first_of) {
  using it_t = typeof(this->in.begin());

  // occurring
  auto s = shad_test_stl::subseq_from_(this->in, this->kNumElements - 32, 32);
  this->test(std::find_first_of<it_t, it_t>,
             shad_test_stl::find_first_of_<it_t, it_t>, s.begin(), s.end());

  // not occurring
  s = shad_test_stl::create_container_<TypeParam>(32, false);
  this->test(std::find_first_of<it_t, it_t>,
             shad_test_stl::find_first_of_<it_t, it_t>, s.begin(), s.end());
}

///////////////////////////////////////
//
// adjacent_find
//
///////////////////////////////////////
TYPED_TEST(TF, std_adjacent_find) {
  using it_t = typeof(this->in.begin());

  // none
  this->test(std::adjacent_find<it_t>, shad_test_stl::adjacent_find_<it_t>);

  // some - todo
}

///////////////////////////////////////
//
// search
//
///////////////////////////////////////
TYPED_TEST(TF, std_search) {
  using it_t = typeof(this->in.begin());

  // occurring
  auto s = shad_test_stl::subseq_from_(this->in, this->kNumElements - 32, 32);
  this->test(std::search<it_t, it_t>, shad_test_stl::search_<it_t, it_t>,
             s.begin(), s.end());

  // not occurring
  s = shad_test_stl::create_container_<TypeParam>(32, false);
  this->test(std::search<it_t, it_t>, shad_test_stl::search_<it_t, it_t>,
             s.begin(), s.end());
}

///////////////////////////////////////
//
// search_n - todo check why failing
//
///////////////////////////////////////
// TYPED_TEST(AlgorithmTF, std_search_n) {
//  using it_t = typeof(this->in.begin());
//  using val_t = value_t;
//
//  for (size_t i = 0; i < 3; ++i) {
//    this->test(std::search_n<it_t, size_t, val_t>,
//               search_n_<it_t, size_t, val_t>, i,
//               shad_test_stl::make_val<val_t>(0));
//    this->test(std::search_n<it_t, size_t, val_t>,
//               search_n_<it_t, size_t, val_t>, i,
//               shad_test_stl::make_val<val_t>(1));
//  }
//}
