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

#include "ds_tag.hpp"
using namespace shad_test_stl;

// custom hashable type
struct wrapped_int {
  typedef int data_type;
  bool operator==(const wrapped_int &w) const { return x == w.x; }
  data_type x;
};

namespace std {
template <>
struct hash<wrapped_int> {
  using argument_type = wrapped_int;
  typedef std::size_t result_type;
  result_type operator()(argument_type const &w) const noexcept {
    return std::hash<typename argument_type::data_type>{}(w.x);
  }
};
}  // namespace std

// types for data structures and iterators
// todo add SHAD types
using std_vector_t = std::vector<wrapped_int>;
using std_unordered_map_t = std::unordered_map<wrapped_int, wrapped_int>;

using vector_it_val_t = typename std_vector_t::iterator::value_type;
using map_it_val_t = typename std_unordered_map_t::iterator::value_type;

// container creation
template <typename tag, typename T>
struct create_container_ {
  T operator()(size_t, int &) {
    assert(false);
    return T{};
  }
};

template <typename T>
struct create_container_<vector_tag, T> {
  T operator()(size_t size, int &checksum) {
    T res;
    std::mt19937 rng;
    std::uniform_int_distribution<int> dist{-128, 128};
    checksum = 0;
    for (auto i = size; i > 0; --i) {
      auto n = wrapped_int{dist(rng)};
      res.push_back(n);
      checksum += n.x;
    }
    return res;
  }
};

template <typename T>
struct create_container_<map_tag, T> {
  T operator()(size_t size, int &checksum) {
    T res;
    std::mt19937 rng;
    std::uniform_int_distribution<int> dist{-128, 128};
    checksum = 0;
    for (auto i = size; i > 0; --i) {
      auto k = wrapped_int{static_cast<int>(i)};
      auto n = wrapped_int{dist(rng)};
      res[k] = n;
      checksum += k.x * n.x;
    }
    return res;
  }
};

// dereferencing by *
template <typename tag, typename V>
int val_to_int_(const V &v) {
  return v.x;
}

template <>
int val_to_int_<map_tag, map_it_val_t>(const map_it_val_t &p) {
  return p.first.x * p.second.x;
}

// dereferencing by ->
template <typename tag, typename It>
struct it_to_int_ {
  int operator()(It &it) { return it->x; }
};

template <typename It>
struct it_to_int_<map_tag, It> {
  int operator()(It &it) { return it->first.x * it->second.x; }
};

// template test for checking sequential for over iterators
template <typename T>
class ForTest : public ::testing::Test {
 protected:
  void run() {
    int exp_checksum, obs_checksum;

    auto v = create_container_<tag, T>{}(this->kNumElements_, exp_checksum);

    // iterate and read
    obs_checksum = 0;
    for (auto it = v.begin(); it != v.end(); ++it)
      obs_checksum += val_to_int_<tag>(*it);
    ASSERT_EQ(obs_checksum, exp_checksum);

    // const-iterate and read
    obs_checksum = 0;
    for (auto it = v.cbegin(); it != v.cend(); ++it)
      obs_checksum += val_to_int_<tag>(*it);
    ASSERT_EQ(obs_checksum, exp_checksum);

    // const-iterate and dereference by ->
    obs_checksum = 0;
    for (auto it = v.begin(); it != v.end(); ++it)
      obs_checksum += it_to_int_<tag, it_t>{}(it);
    ASSERT_EQ(obs_checksum, exp_checksum);

    // const-iterate and dereference by *it++
    obs_checksum = 0;
    auto it = v.cbegin();
    while (it != v.cend())
      obs_checksum += val_to_int_<typename ds_tag<T>::type>(*it++);
    ASSERT_EQ(obs_checksum, exp_checksum);
  }

  virtual ~ForTest() {}

 private:
  using tag = typename ds_tag<T>::type;
  using it_t = typename T::iterator;
  static constexpr size_t kNumElements_ = 1024;
};

//
// run
//
// todo add SHAD types
typedef ::testing::Types<std_vector_t, std_unordered_map_t> AllTypes;

TYPED_TEST_CASE(ForTest, AllTypes);

TYPED_TEST(ForTest, For) { this->run(); }
