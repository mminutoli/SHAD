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

#include "common.hpp"
using namespace shad_test_stl;

// types for data structures and iterators
// todo add SHAD types
using std_vector_t = std::vector<int>;
using std_unordered_map_t = std::unordered_map<int, int>;

using vector_it_val_t = typename std_vector_t::iterator::value_type;
using map_it_val_t = typename std_unordered_map_t::iterator::value_type;

// container creation
template <typename tag, typename T>
struct create_container_ {
  T operator()(size_t) {
    assert(false);
    return T{};
  }
};

template <typename T>
struct create_container_<vector_tag, T> {
  T operator()(size_t size) {
    T res;
    std::mt19937 rng;
    std::uniform_int_distribution<int> dist{-128, 128};
    for (auto i = size; i > 0; --i) res.push_back(dist(rng));
    return res;
  }
};

template <typename T>
struct create_container_<map_tag, T> {
  T operator()(size_t size) {
    T res;
    std::mt19937 rng;
    std::uniform_int_distribution<int> dist{-128, 128};
    for (auto i = size; i > 0; --i) res[dist(rng)] = dist(rng);
    return res;
  }
};

// random selection from containers
template <typename tag, typename T>
struct cherry_pick_ {
  std::vector<typename T::iterator::value_type> operator()(const T &in) {
    assert(false);
    return T{};
  }
};

template <typename T>
struct cherry_pick_<vector_tag, T> {
  std::vector<vector_it_val_t> operator()(const T &in) {
    std::vector<vector_it_val_t> res;
    std::mt19937 rng;
    std::uniform_int_distribution<int> pick_dist{0, 1};
    std::uniform_int_distribution<int> poison_dist{-10, 10};
    for (auto it = in.begin(); it != in.end(); ++it) {
      if (pick_dist(rng))
        res.push_back(*it);
      else
        res.push_back(vector_it_val_t{poison_dist(rng)});
    }
    return res;
  }
};

template <typename T>
struct cherry_pick_<map_tag, T> {
  std::vector<map_it_val_t> operator()(const T &in) {
    std::vector<map_it_val_t> res;
    std::mt19937 rng;
    std::uniform_int_distribution<int> pick_dist{0, 1};
    std::uniform_int_distribution<int> poison_dist{-10, 10};
    for (auto it = in.begin(); it != in.end(); ++it) {
      if (pick_dist(rng))
        res.push_back(*it);
      else
        res.push_back(map_it_val_t{poison_dist(rng), poison_dist(rng)});
    }
    return res;
  }
};

// accumulate callables
template <typename T>
struct std_find_ {
  template <typename It, typename... Policy>
  It operator()(It begin, It end, const T &obj) {
    return std::find(begin, end, obj);
  }
};

// min_element callables
template <typename T>
struct std_min_element_ {
  template <typename It, typename... Policy>
  It operator()(It begin, It end) {
    return std::min_element(begin, end);
  }
};

// template test for checking find over iterators
template <typename T>
class AlgorithmTests : public ::testing::Test {
 protected:
  template <typename F>
  void find(F &&f) {
    // create the input containers
    auto in = create_container_<tag, T>{}(this->kNumElements);

    // create the container with the values to be searched
    auto objs = cherry_pick_<tag, T>{}(in);

    // create the containers with the search results
    std::vector<typename T::const_iterator> obs_found(this->num_objs);
    std::vector<typename T::const_iterator> exp_found(this->num_objs);

    // search
    auto obs_found_it = obs_found.begin();
    for (auto &obj : objs) *obs_found_it++ = f(in.begin(), in.end(), obj);

    // seq-for search
    auto exp_found_it = exp_found.begin();
    for (auto &obj : objs) {
      *exp_found_it = in.end();
      for (auto it = in.begin(); it != in.end(); ++it)
        if (*it == obj) {
          *exp_found_it = it;
          break;
        }
      ++exp_found_it;
    }

    // check correctness
    exp_found_it = exp_found.begin();
    for (auto &found_entry : obs_found) ASSERT_EQ(found_entry, *exp_found_it++);
  }

  template <typename F>
  void min_element(F &&f) {
    // create the input containers
    auto in = create_container_<tag, T>{}(this->kNumElements);

    // apply
    auto obs = f(in.begin(), in.end());

    // seq-for reference
    auto exp = in.begin();
    for (auto it = in.begin(); it != in.end(); ++it)
      if (*it < *exp) exp = it;

    // check correctness
    ASSERT_EQ(obs, exp);
  }

  virtual ~AlgorithmTests() {}

 private:
  using tag = typename ds_tag<T>::type;
  using it_t = typename T::iterator;
  using it_val_t = typename it_t::value_type;
  static constexpr size_t kNumElements = 1024, num_objs = 128;
};

//
// run
//
// todo add SHAD types
typedef ::testing::Types<std_vector_t, std_unordered_map_t> Types;

TYPED_TEST_CASE(AlgorithmTests, Types);

// (sequential) std
TYPED_TEST(AlgorithmTests, find) {
  using it_val_t = typename TypeParam::iterator::value_type;
  this->find(std_find_<it_val_t>{});
  this->min_element(std_min_element_<it_val_t>{});
}

// todo std on shad
// todo sequential shad
// todo distributed shad
// todo distributed-async shad
