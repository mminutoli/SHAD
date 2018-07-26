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

///////////////////////////////////////
//
// std::vector
//
///////////////////////////////////////
using VT = shad_test_stl::std_vector_t;

// transform
BENCHMARK_TEMPLATE_DEFINE_F_(std_vector_transform, VT) {
  using it_t = typeof(this->in.begin());
  using val_t = typeof(*this->in.begin());
  using unary_t = shad_test_stl::add_two<val_t>;
  auto f = std::transform<it_t, it_t, unary_t>;
  this->run_io(st, f, unary_t{});
}
BENCHMARK_REGISTER_F_(std_vector_transform);

///////////////////////////////////////
//
// std::set
//
///////////////////////////////////////
using ST = shad_test_stl::std_set_t;

// transform - not supported

///////////////////////////////////////
//
// std::unordered_map
//
///////////////////////////////////////
using UMT = shad_test_stl::std_unordered_map_t;

// transform - not supported
