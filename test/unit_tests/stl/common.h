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

#ifndef TEST_UNIT_TESTS_STL_COMMON_H_
#define TEST_UNIT_TESTS_STL_COMMON_H_

#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace shad_test_stl {

// data-structure tags
struct vector_tag {};
struct map_tag {};
struct set_tag {};

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

template <typename U>
struct ds_tag<std::set<U>> {
  using type = set_tag;
};

// typing utilities

// types for data structures and iterators
// todo add SHAD types
using std_vector_t = std::vector<int>;
using std_unordered_map_t = std::unordered_map<int, int>;
using std_set_t = std::set<int>;

using vector_it_val_t = typename std_vector_t::iterator::value_type;
using map_it_val_t = typename std_unordered_map_t::iterator::value_type;
using set_it_val_t = typename std_set_t::iterator::value_type;

// dereferencing
template <typename val_t>
int val_to_int_(const val_t &v) {
  return v;
}

template <>
int val_to_int_<map_it_val_t>(const map_it_val_t &v) {
  return v.first + v.second;
}

// value creation
template <typename T>
T make_val(int v) {
  return v;
};

template <>
map_it_val_t make_val<map_it_val_t>(int v) {
  return map_it_val_t{v, v};
}

// value insertion
template <typename tag, typename T>
struct insert_value_ {
  void operator()(T &, const typename T::iterator::value_type) {}
};

template <typename T>
struct insert_value_<vector_tag, T> {
  void operator()(T &in, const typename T::iterator::value_type &val) {
    in.push_back(val);
  }
};

template <typename T>
struct insert_value_<map_tag, T> {
  void operator()(T &in, const typename T::iterator::value_type &val) {
    in[val.first] = val.second;
  }
};

template <typename T>
struct insert_value_<set_tag, T> {
  void operator()(T &in, const typename T::iterator::value_type &val) {
    in.insert(val);
  }
};

// container creation and expected checksum
template <typename T>
T create_container_(size_t size, bool even = true) {
  using tag = typename ds_tag<T>::type;
  T res;
  using val_t = typeof(*res.begin());
  for (auto i = size; i > 0; --i)
    insert_value_<tag, T>{}(res, make_val<val_t>(2 * i + !even));
  return res;
}

template <typename T>
int expected_checksum(size_t size, bool even = true) {
  using tag = typename ds_tag<T>::type;
  using val_t = typeof(*T{}.begin());
  int res = 0;
  for (auto i = size; i > 0; --i)
    res += val_to_int_(make_val<val_t>(2 * i + !even));
  return res;
}

// sub-sequencing from containers
template <typename T>
T subseq_from_(const T &in, size_t start_idx, size_t len) {
  T res;
  using tag = typename ds_tag<T>::type;

  // move to starting point
  auto first = in.begin();
  size_t i = 0;
  while (i++ < start_idx && first != in.end()) {
    assert(first != in.end());
    ++first;
  }

  // fill
  for (i = 0; i < len; ++i) {
    assert(first != in.end());
    insert_value_<tag, T>{}(res, *first);
    ++first;
  }

  return res;
}

template <typename T>
struct is_even {
  bool operator()(const T &x) { return !(x % 2); }
};

template <>
struct is_even<map_it_val_t> {
  bool operator()(const map_it_val_t &x) { return is_even<int>{}(x.second); }
};

template <typename T>
struct is_odd {
  bool operator()(const T &x) { return !(is_even<T>{}(x)); }
};

// test fixture
template <typename T>
class TestFixture : public ::testing::Test {
 public:
  void SetUp() { in = create_container_<T>(this->kNumElements); }

  template <typename F, typename... args_>
  void test(F &&sub_f, F &&obj_f, args_... args) {
    auto obs = sub_f(in.begin(), in.end(), args...);
    auto exp = obj_f(in.begin(), in.end(), args...);
    ASSERT_EQ(obs, exp);
  }

 protected:
  virtual ~TestFixture() {}
  static constexpr size_t kNumElements = 1024;
  T in;
};
}  // namespace shad_test_stl

#endif
