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
#include <array>  //todo
#include <set>
#include <vector>

#include "benchmark/benchmark.h"

#include "shad/data_structures/array.h"  //todo

#include "common.h"

///////////////////////////////////////
//
// std::vector
//
///////////////////////////////////////
BENCHMARK_TEMPLATE_DEFINE_F(VectorPerf, std_vector_min_element,
                            std::vector<int>)
(benchmark::State& st) {
  using it_t = typeof(this->in->begin());
  auto f = std::min_element<it_t>;
  this->run(st, f);
}
BENCHMARK_REGISTER_F_(VectorPerf, std_vector_min_element);

BENCHMARK_TEMPLATE_DEFINE_F(VectorPerf, std_vector_max_element,
                            std::vector<int>)
(benchmark::State& st) {
  using it_t = typeof(this->in->begin());
  auto f = std::max_element<it_t>;
  this->run(st, f);
}
BENCHMARK_REGISTER_F_(VectorPerf, std_vector_max_element)

BENCHMARK_TEMPLATE_DEFINE_F(VectorPerf, std_vector_minmax_element,
                            std::vector<int>)
(benchmark::State& st) {
  using it_t = typeof(this->in->begin());
  auto f = std::minmax_element<it_t>;
  this->run(st, f);
}
BENCHMARK_REGISTER_F_(VectorPerf, std_vector_minmax_element);

///////////////////////////////////////
//
// shad::array - min size
//
///////////////////////////////////////
using shad_array_t_s0 = shad::array<int, shad_test_stl::BENCHMARK_MIN_SIZE>;

BENCHMARK_TEMPLATE_DEFINE_F(ArrayPerf, shad_array_min_element_s0,
                            shad_array_t_s0)
(benchmark::State& st) {
  this->run(st, std::min_element<typeof(this->in->begin())>);
}
BENCHMARK_REGISTER_F(ArrayPerf, shad_array_min_element_s0)
    ->Arg(shad_test_stl::BENCHMARK_MIN_SIZE);

BENCHMARK_TEMPLATE_DEFINE_F(ArrayPerf, shad_array_max_element_s0,
                            shad_array_t_s0)
(benchmark::State& st) {
  this->run(st, std::max_element<typeof(this->in->begin())>);
}
BENCHMARK_REGISTER_F(ArrayPerf, shad_array_max_element_s0)
    ->Arg(shad_test_stl::BENCHMARK_MIN_SIZE);

BENCHMARK_TEMPLATE_DEFINE_F(ArrayPerf, shad_array_minmax_element_s0,
                            shad_array_t_s0)
(benchmark::State& st) {
  this->run(st, std::minmax_element<typeof(this->in->begin())>);
}
BENCHMARK_REGISTER_F(ArrayPerf, shad_array_minmax_element_s0)
    ->Arg(shad_test_stl::BENCHMARK_MIN_SIZE);

///////////////////////////////////////
//
// shad::array - max size
//
///////////////////////////////////////
using shad_array_t_s1 = shad::array<int, shad_test_stl::BENCHMARK_MAX_SIZE>;

BENCHMARK_TEMPLATE_DEFINE_F(ArrayPerf, shad_array_min_element_s1,
                            shad_array_t_s1)
(benchmark::State& st) {
  this->run(st, std::min_element<typeof(this->in->begin())>);
}
BENCHMARK_REGISTER_F(ArrayPerf, shad_array_min_element_s1)
    ->Arg(shad_test_stl::BENCHMARK_MAX_SIZE);

BENCHMARK_TEMPLATE_DEFINE_F(ArrayPerf, shad_array_max_element_s1,
                            shad_array_t_s1)
(benchmark::State& st) {
  this->run(st, std::max_element<typeof(this->in->begin())>);
}
BENCHMARK_REGISTER_F(ArrayPerf, shad_array_max_element_s1)
    ->Arg(shad_test_stl::BENCHMARK_MAX_SIZE);

BENCHMARK_TEMPLATE_DEFINE_F(ArrayPerf, shad_array_minmax_element_s1,
                            shad_array_t_s1)
(benchmark::State& st) {
  this->run(st, std::minmax_element<typeof(this->in->begin())>);
}
BENCHMARK_REGISTER_F(ArrayPerf, shad_array_minmax_element_s1)
    ->Arg(shad_test_stl::BENCHMARK_MAX_SIZE);

///////////////////////////////////////
//
// std::set
//
///////////////////////////////////////
BENCHMARK_TEMPLATE_DEFINE_F(SetPerf, std_set_min_element, std::set<int>)
(benchmark::State& st) {
  using it_t = typeof(this->in->begin());
  auto f = std::min_element<it_t>;
  this->run(st, f);
}
BENCHMARK_REGISTER_F_(SetPerf, std_set_min_element)

BENCHMARK_TEMPLATE_DEFINE_F(SetPerf, std_set_max_element, std::set<int>)
(benchmark::State& st) {
  using it_t = typeof(this->in->begin());
  auto f = std::max_element<it_t>;
  this->run(st, f);
}
BENCHMARK_REGISTER_F_(SetPerf, std_set_max_element)

BENCHMARK_TEMPLATE_DEFINE_F(SetPerf, std_set_minmax_element, std::set<int>)
(benchmark::State& st) {
  using it_t = typeof(this->in->begin());
  auto f = std::minmax_element<it_t>;
  this->run(st, f);
}
BENCHMARK_REGISTER_F_(SetPerf, std_set_minmax_element)
