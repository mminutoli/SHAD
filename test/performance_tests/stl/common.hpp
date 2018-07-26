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

#ifndef TEST_UNIT_TESTS_STL_COMMON_HPP_
#define TEST_UNIT_TESTS_STL_COMMON_HPP_

#include <random>
#include <unordered_map>
#include <vector>

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
template <typename T>
using it_t = typename T::iterator;

template <typename T>
using output_it_t = typename T::output_iterator;

template <typename T>
using it_value_t = typename T::iterator::value_type;

// types for data structures and iterators
// todo add SHAD types
using std_vector_t = std::vector<uint64_t>;
using std_unordered_map_t = std::unordered_map<uint64_t, uint64_t>;
using std_set_t = std::set<uint64_t>;

using vector_it_val_t = typename std_vector_t::iterator::value_type;
using map_it_val_t = typename std_unordered_map_t::iterator::value_type;
using set_it_val_t = typename std_set_t::iterator::value_type;

// all-even container creation
template <typename T, typename tag_t>
struct create_container__ {
  T operator()(uint64_t size) {
    T res;
    for (uint64_t i = 0; i < size; ++i) res.push_back(i);
    return res;
  }
};

template <typename T>
struct create_container__<T, map_tag> {
  T operator()(uint64_t size) {
    T res;
    for (uint64_t i = 0; i < size; ++i) res[i] = i;
    return res;
  }
};

template <typename T>
struct create_container__<T, set_tag> {
  T operator()(uint64_t size) {
    T res;
    for (uint64_t i = 0; i < size; ++i) res.insert(i * 4);
    return res;
  }
};

template <typename T>
T create_container_(uint64_t size) {
  return create_container__<T, typename ds_tag<T>::type>{}(size);
}

// even/odd test
template <typename T>
struct is_even {
  bool operator()(const T &x) { return !(x % 2); }
};

template <>
struct is_even<map_it_val_t> {
  bool operator()(const map_it_val_t &x) {
    return is_even<uint64_t>{}(x.second);
  }
};

template <typename T>
struct is_odd {
  bool operator()(const T &x) { return !(is_even<T>{}(x)); }
};

// add 2
template <typename T>
struct add_two {
  bool operator()(const T &x) { return x + 2; }
};

template <>
struct add_two<map_it_val_t> {
  bool operator()(const map_it_val_t &x) {
    return add_two<uint64_t>{}(x.second);
  }
};

// benchmark registration utilities
constexpr uint64_t BENCHMARK_MIN_SIZE = 1024;
constexpr uint64_t BENCHMARK_MAX_SIZE = 64 << 20;
constexpr uint64_t BENCHMARK_SIZE_MULTIPLIER = 4;
}  // namespace shad_test_stl

template <typename T>
class shad_test_stl_PerfTestFixture : public benchmark::Fixture {
  void SetUp(benchmark::State &state) {
    in = shad_test_stl::create_container_<T>(state.range(0));
  }

 public:
  template <typename F, typename... args_>
  void run(benchmark::State &state, F &&f, args_... args) {
    in = shad_test_stl::create_container_<T>(state.range(0));
    for (auto _ : state) f(in.begin(), in.end(), args...);
  }

  template <typename F, typename... args_>
  void run_io(benchmark::State &state, F &&f, args_... args) {
    in = shad_test_stl::create_container_<T>(state.range(0));
    auto out = shad_test_stl::create_container_<T>(state.range(0));
    for (auto _ : state) f(in.begin(), in.end(), out.begin(), args...);
  }

 protected:
  T in;
};

#define BENCHMARK_TEMPLATE_DEFINE_F_(x, y)                         \
  BENCHMARK_TEMPLATE_DEFINE_F(shad_test_stl_PerfTestFixture, x, y) \
  (benchmark::State & st)

#define BENCHMARK_REGISTER_F_(x)                                  \
  BENCHMARK_REGISTER_F(shad_test_stl_PerfTestFixture, x)          \
      ->RangeMultiplier(shad_test_stl::BENCHMARK_SIZE_MULTIPLIER) \
      ->Range(shad_test_stl::BENCHMARK_MIN_SIZE,                  \
              shad_test_stl::BENCHMARK_MAX_SIZE);

#endif
