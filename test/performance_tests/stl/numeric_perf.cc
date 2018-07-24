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

#include <functional>
#include <iostream>
#include <numeric>
#include <random>
#include <unordered_map>
#include <vector>

#include <benchmark/benchmark.h>

#include "common.hpp"
using namespace shad_test_stl;

// value initialization
template <typename val_t>
val_t init_val_() {
  return val_t{0};
}

template <>
map_it_val_t init_val_<map_it_val_t>() {
  return map_it_val_t{0, 0};
}

// template test for checking find over iterators
template <typename T>
class NumericTestFixture : public benchmark::Fixture {
 public:
  template <typename F, typename... args_>
  void run(benchmark::State &state, F &&f, args_... args) {
    auto in = create_container_<T>(state.range(0));
    for (auto _ : state) f(in.begin(), in.end(), args...);
  }
};

//
// run
//
using T = std::vector<int>;
BENCHMARK_TEMPLATE_DEFINE_F(NumericTestFixture, std_std_accumulate, T)
(benchmark::State &st) {
  auto f = std::accumulate<it_t<T>, it_value_t<T>>;
  this->run(st, f, 0);
}
BENCHMARK_REGISTER_F(NumericTestFixture, std_std_accumulate)
    ->RangeMultiplier(2)
    ->Range(BENCHMARK_MIN_SIZE, BENCHMARK_MAX_SIZE);

BENCHMARK_TEMPLATE_DEFINE_F(NumericTestFixture, std_std_reduce, T)
(benchmark::State &st) {
  auto f = std::reduce<it_t<T>>;
  this->run(st, f);
}
BENCHMARK_REGISTER_F(NumericTestFixture, std_std_reduce)
    ->RangeMultiplier(2)
    ->Range(BENCHMARK_MIN_SIZE, BENCHMARK_MAX_SIZE);

// todo sequential shad
// todo distributed shad
// todo distributed-async shad
