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

#ifndef TEST_UNIT_TESTS_STL_ALGORITHM_WRAPPERS_HPP_
#define TEST_UNIT_TESTS_STL_ALGORITHM_WRAPPERS_HPP_

#include <algorithm>

namespace shad_test_stl {
// all_of callables
template <typename T, typename... ExecutionPolicy>
struct std_all_of_ {
  template <typename It, typename Pred>
  bool operator()(ExecutionPolicy... p, It begin, It end, Pred &&pred) {
    return std::all_of(p..., begin, end, pred);
  }
};

// any_of callables
template <typename T, typename... ExecutionPolicy>
struct std_any_of_ {
  template <typename It, typename Pred>
  bool operator()(ExecutionPolicy... p, It begin, It end, Pred &&pred) {
    return std::any_of(p..., begin, end, pred);
  }
};

// none_of callables
template <typename T, typename... ExecutionPolicy>
struct std_none_of_ {
  template <typename It, typename Pred>
  bool operator()(ExecutionPolicy... p, It begin, It end, Pred &&pred) {
    return std::none_of(p..., begin, end, pred);
  }
};

// find callables
template <typename T>
struct std_find_ {
  template <typename It, typename... ExecutionPolicy>
  It operator()(ExecutionPolicy... p, It begin, It end, const T &obj) {
    return std::find(p..., begin, end, obj);
  }
};

// min_element callables
template <typename T, typename... ExecutionPolicy>
struct std_min_element_ {
  template <typename It, typename... Policy>
  It operator()(ExecutionPolicy... p, It begin, It end) {
    return std::min_element(p..., begin, end);
  }
};

// accumulate callable
template <typename T, typename... ExecutionPolicy>
struct std_accumulate_ {
  template <typename It>
  T operator()(ExecutionPolicy... p, It begin, It end, T init) {
    return std::accumulate(p..., begin, end, init);
  }
};
}  // namespace shad_test_stl

#endif
