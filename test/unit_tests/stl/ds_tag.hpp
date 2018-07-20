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

#ifndef TEST_UNIT_TESTS_STL_DS_TAG_HPP_
#define TEST_UNIT_TESTS_STL_DS_TAG_HPP_

#include <vector>
#include <unordered_map>

namespace shad_test_stl {
struct vector_tag {};
struct map_tag {};

template <typename T>
struct ds_tag {
  using type = void;
};

template <typename U>
struct ds_tag<std::vector<U>> {
  using type = vector_tag;
};

template <typename... U>
struct ds_tag<std::unordered_map<U...>> {
  using type = map_tag;
};
}  // namespace shad_test_stl

#endif
