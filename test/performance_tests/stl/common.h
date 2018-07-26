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

// types for data structures and iterators
// todo add SHAD types
using std_vector_t = std::vector<int>;
using std_unordered_map_t = std::unordered_map<int, int>;
using std_set_t = std::set<int>;

using vector_it_val_t = typename std_vector_t::iterator::value_type;
using map_it_val_t = typename std_unordered_map_t::iterator::value_type;
using set_it_val_t = typename std_set_t::iterator::value_type;

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
