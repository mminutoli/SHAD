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

#include <benchmark/benchmark.h>

#include "common.hpp"
using namespace shad_test_stl;

///////////////////////////////////////
//
// vector
//
///////////////////////////////////////

using VT = std_vector_t;

BENCHMARK_TEMPLATE_DEFINE_F(PerfTestFixture, std_vector_min_element, VT)
(benchmark::State &st) {
  auto f = std::min_element<it_t<VT>>;
  this->run(st, f);
}
BENCHMARK_REGISTER_F(PerfTestFixture, std_vector_min_element)
    ->RangeMultiplier(BENCHMARK_SIZE_MULTIPLIER)
    ->Range(BENCHMARK_MIN_SIZE, BENCHMARK_MAX_SIZE);

BENCHMARK_TEMPLATE_DEFINE_F(PerfTestFixture, std_vector_max_element, VT)
(benchmark::State &st) {
  auto f = std::max_element<it_t<VT>>;
  this->run(st, f);
}
BENCHMARK_REGISTER_F(PerfTestFixture, std_vector_max_element)
    ->RangeMultiplier(BENCHMARK_SIZE_MULTIPLIER)
    ->Range(BENCHMARK_MIN_SIZE, BENCHMARK_MAX_SIZE);

BENCHMARK_TEMPLATE_DEFINE_F(PerfTestFixture, std_vector_minmax_element, VT)
(benchmark::State &st) {
  auto f = std::minmax_element<it_t<VT>>;
  this->run(st, f);
}
BENCHMARK_REGISTER_F(PerfTestFixture, std_vector_minmax_element)
    ->RangeMultiplier(BENCHMARK_SIZE_MULTIPLIER)
    ->Range(BENCHMARK_MIN_SIZE, BENCHMARK_MAX_SIZE);

///////////////////////////////////////
//
// set
//
///////////////////////////////////////

using ST = std_set_t;

BENCHMARK_TEMPLATE_DEFINE_F(PerfTestFixture, std_set_min_element, ST)
(benchmark::State &st) {
  auto f = std::min_element<it_t<ST>>;
  this->run(st, f);
}
BENCHMARK_REGISTER_F(PerfTestFixture, std_set_min_element)
    ->RangeMultiplier(BENCHMARK_SIZE_MULTIPLIER)
    ->Range(BENCHMARK_MIN_SIZE, BENCHMARK_MAX_SIZE);

BENCHMARK_TEMPLATE_DEFINE_F(PerfTestFixture, std_set_max_element, ST)
(benchmark::State &st) {
  auto f = std::max_element<it_t<ST>>;
  this->run(st, f);
}
BENCHMARK_REGISTER_F(PerfTestFixture, std_set_max_element)
    ->RangeMultiplier(BENCHMARK_SIZE_MULTIPLIER)
    ->Range(BENCHMARK_MIN_SIZE, BENCHMARK_MAX_SIZE);

BENCHMARK_TEMPLATE_DEFINE_F(PerfTestFixture, std_set_minmax_element, ST)
(benchmark::State &st) {
  auto f = std::minmax_element<it_t<ST>>;
  this->run(st, f);
}
BENCHMARK_REGISTER_F(PerfTestFixture, std_set_minmax_element)
    ->RangeMultiplier(BENCHMARK_SIZE_MULTIPLIER)
    ->Range(BENCHMARK_MIN_SIZE, BENCHMARK_MAX_SIZE);
