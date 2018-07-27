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

#include <array>  //todo
#include <numeric>
#include <set>
#include <vector>

#include "benchmark/benchmark.h"

#include "shad/data_structures/array.h"  //todo

#include "common.h"

///////////////////////////////////////
//
// vector
//
///////////////////////////////////////
// accumulate
BENCHMARK_TEMPLATE_DEFINE_F(VectorPerf, std_vector_accumulate, std::vector<int>)
(benchmark::State& st) {
  using it_t = typeof(this->in->begin());
  using value_t = typename std::vector<int>::iterator::value_type;
  auto f = std::accumulate<it_t, value_t>;
  this->run(st, f, 0);
}
BENCHMARK_REGISTER_F_(VectorPerf, std_vector_accumulate);

#ifdef STD_REDUCE_TEST
// reduce
BENCHMARK_TEMPLATE_DEFINE_F(VectorPerf, std_vector_reduce, std::vector<int>)
(benchmark::State& st) {
  using it_t = typeof(this->in->begin());
  auto f = std::reduce<it_t>;
  this->run(st, f);
}
BENCHMARK_REGISTER_F_(VectorPerf, std_vector_reduce);
#endif

///////////////////////////////////////
//
// set
//
///////////////////////////////////////
// accumulate
BENCHMARK_TEMPLATE_DEFINE_F(SetPerf, std_set_accumulate, std::set<int>)
(benchmark::State& st) {
  using it_t = typeof(this->in->begin());
  auto f = std::accumulate<it_t, int>;
  this->run(st, f, 0);
}
BENCHMARK_REGISTER_F_(SetPerf, std_set_accumulate);

#ifdef STD_REDUCE_TEST
// reduce
BENCHMARK_TEMPLATE_DEFINE_F(SetPerf, std_set_reduce, std::set<int>)
(benchmark::State& st) {
  using it_t = typeof(this->in->begin());
  auto f = std::reduce<it_t>;
  this->run(st, f);
}
BENCHMARK_REGISTER_F_(SetPerf, std_set_reduce);
#endif
