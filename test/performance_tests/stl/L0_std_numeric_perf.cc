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

#include "common.h"

///////////////////////////////////////
//
// vector
//
///////////////////////////////////////
using VT = shad_test_stl::std_vector_t;

// accumulate
BENCHMARK_TEMPLATE_DEFINE_F_(std_vector_accumulate, VT) {
  using it_t = typeof(this->in.begin());
  using val_t = typename VT::iterator::value_type;
  auto f = std::accumulate<it_t, val_t>;
  this->run(st, f, 0);
}
BENCHMARK_REGISTER_F_(std_vector_accumulate);

#ifdef STD_REDUCE_TEST
// reduce
BENCHMARK_TEMPLATE_DEFINE_F_(std_vector_reduce, VT) {
  using it_t = typeof(this->in.begin());
  auto f = std::reduce<it_t>;
  this->run(st, f);
}
BENCHMARK_REGISTER_F_(std_vector_reduce);
#endif

///////////////////////////////////////
//
// set
//
///////////////////////////////////////
using ST = shad_test_stl::std_set_t;

// accumulate
BENCHMARK_TEMPLATE_DEFINE_F_(std_set_accumulate, ST) {
  using it_t = typeof(this->in.begin());
  using val_t = typename ST::iterator::value_type;
  auto f = std::accumulate<it_t, val_t>;
  this->run(st, f, 0);
}
BENCHMARK_REGISTER_F_(std_set_accumulate);

#ifdef STD_REDUCE_TEST
// reduce
BENCHMARK_TEMPLATE_DEFINE_F_(std_set_reduce, ST) {
  using it_t = typeof(this->in.begin());
  auto f = std::reduce<it_t>;
  this->run(st, f);
}
BENCHMARK_REGISTER_F_(std_set_reduce);
#endif
