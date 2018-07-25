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

#include <numeric>

#include <benchmark/benchmark.h>

#include "common.hpp"
using namespace shad_test_stl;

///////////////////////////////////////
//
// vector
//
///////////////////////////////////////

using VT = std_vector_t;

// accumulate
BENCHMARK_TEMPLATE_DEFINE_F_(std_vector_accumulate, VT) {
  auto f = std::accumulate<it_t<VT>, it_value_t<VT>>;
  this->run(st, f, 0);
}
BENCHMARK_REGISTER_F_(std_vector_accumulate);

// reduce
BENCHMARK_TEMPLATE_DEFINE_F_(std_vector_reduce, VT) {
  auto f = std::reduce<it_t<VT>>;
  this->run(st, f);
}
BENCHMARK_REGISTER_F_(std_vector_reduce);

///////////////////////////////////////
//
// set
//
///////////////////////////////////////

using ST = std_set_t;

// accumulate
BENCHMARK_TEMPLATE_DEFINE_F_(std_set_accumulate, ST) {
  auto f = std::accumulate<it_t<ST>, it_value_t<ST>>;
  this->run(st, f, 0);
}
BENCHMARK_REGISTER_F_(std_set_accumulate);

// reduce
BENCHMARK_TEMPLATE_DEFINE_F_(std_set_reduce, ST) {
  auto f = std::reduce<it_t<ST>>;
  this->run(st, f);
}
BENCHMARK_REGISTER_F_(std_set_reduce);
