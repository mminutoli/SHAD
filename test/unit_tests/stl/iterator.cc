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

#include <type_traits>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

template <typename T>
class InputIteratorTest : public ::testing::Test {
 protected:
  virtual ~InputIteratorTest() {}
};

template <typename T>
using it_type = typename std::iterator_traits<T>::value_type;

template <typename T, typename = void>
struct is_iterator {
  const bool value = false;
};

// todo refine it for specific iterator categories
template <typename T>
struct is_iterator<
    T, typename std::enable_if<!std::is_same<it_type<T>, void>::value>::type> {
  const bool value = true;
};

// todo add SHAD types
using std_vector_t = std::vector<int>;
using std_unordered_map_t = std::unordered_map<int, int>;
typedef ::testing::Types<std_vector_t, std_unordered_map_t> Types;

TYPED_TEST_CASE(InputIteratorTest, Types);

//
// Check iterators on vector
//
TYPED_TEST(InputIteratorTest, Iterator) {
  ASSERT_TRUE(is_iterator<typename TypeParam::iterator>{}.value);
}
