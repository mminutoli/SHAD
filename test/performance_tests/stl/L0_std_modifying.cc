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

// transform
BENCHMARK_TEMPLATE_DEFINE_F_(std_vector_transform, VT) {
  using unary_t = add_two<it_value_t<VT>>;
  auto f = std::transform<it_t<VT>, it_t<VT>, unary_t>;
  this->run_io(st, f, unary_t{});
}
BENCHMARK_REGISTER_F_(std_vector_transform);

///////////////////////////////////////
//
// set
//
///////////////////////////////////////

using ST = std_set_t;

// transform - not supported

///////////////////////////////////////
//
// unordered_map
//
///////////////////////////////////////

using UMT = std_unordered_map_t;

// transform - not supported
