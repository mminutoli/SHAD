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

// all_of, any_of, none_of
BENCHMARK_TEMPLATE_DEFINE_F_(std_vector_all_of, VT) {
  using pred_t = is_even<it_value_t<VT>>;
  auto f = std::all_of<it_t<VT>, pred_t>;
  this->run(st, f, pred_t{});
}
BENCHMARK_REGISTER_F_(std_vector_all_of);

BENCHMARK_TEMPLATE_DEFINE_F_(std_vector_any_of, VT) {
  using pred_t = is_odd<it_value_t<VT>>;
  auto f = std::any_of<it_t<VT>, pred_t>;
  this->run(st, f, pred_t{});
}
BENCHMARK_REGISTER_F_(std_vector_any_of);

BENCHMARK_TEMPLATE_DEFINE_F_(std_vector_none_of, VT) {
  using pred_t = is_odd<it_value_t<VT>>;
  auto f = std::none_of<it_t<VT>, pred_t>;
  this->run(st, f, pred_t{});
}
BENCHMARK_REGISTER_F_(std_vector_none_of);

// todo for_each, for_each_n

// count, count_if
BENCHMARK_TEMPLATE_DEFINE_F_(std_vector_count, VT) {
  auto f = std::count<it_t<VT>, it_value_t<VT>>;
  this->run(st, f, 0);
}
BENCHMARK_REGISTER_F_(std_vector_count);

BENCHMARK_TEMPLATE_DEFINE_F_(std_vector_count_if, VT) {
  using pred_t = is_even<it_value_t<VT>>;
  auto f = std::count_if<it_t<VT>, pred_t>;
  this->run(st, f, pred_t{});
}
BENCHMARK_REGISTER_F_(std_vector_count_if);

// todo mismatch

// find, find_if, find_if_not
BENCHMARK_TEMPLATE_DEFINE_F_(std_vector_find, VT) {
  auto f = std::find<it_t<VT>, it_value_t<VT>>;
  this->run(st, f, 1);
}
BENCHMARK_REGISTER_F_(std_vector_find);

BENCHMARK_TEMPLATE_DEFINE_F_(std_vector_find_if, VT) {
  using pred_t = is_odd<it_value_t<VT>>;
  auto f = std::find_if<it_t<VT>, pred_t>;
  this->run(st, f, pred_t{});
}
BENCHMARK_REGISTER_F_(std_vector_find_if);

BENCHMARK_TEMPLATE_DEFINE_F_(std_vector_find_if_not, VT) {
  using pred_t = is_odd<it_value_t<VT>>;
  auto f = std::find_if_not<it_t<VT>, pred_t>;
  this->run(st, f, pred_t{});
}
BENCHMARK_REGISTER_F_(std_vector_find_if_not);

// todo find_end, find_first_of

// adjacent_find
BENCHMARK_TEMPLATE_DEFINE_F_(std_vector_adjacent_find, VT) {
  auto f = std::adjacent_find<it_t<VT>>;
  this->run(st, f);
}
BENCHMARK_REGISTER_F_(std_vector_adjacent_find);

// todo search, search_n

///////////////////////////////////////
//
// set
//
///////////////////////////////////////

using ST = std_set_t;

// all_of, any_of, none_of
BENCHMARK_TEMPLATE_DEFINE_F_(std_set_all_of, ST) {
  using pred_t = is_even<it_value_t<ST>>;
  auto f = std::all_of<it_t<ST>, pred_t>;
  this->run(st, f, pred_t{});
}
BENCHMARK_REGISTER_F_(std_set_all_of);

BENCHMARK_TEMPLATE_DEFINE_F_(std_set_any_of, ST) {
  using pred_t = is_odd<it_value_t<ST>>;
  auto f = std::any_of<it_t<ST>, pred_t>;
  this->run(st, f, pred_t{});
}
BENCHMARK_REGISTER_F_(std_set_any_of);

BENCHMARK_TEMPLATE_DEFINE_F_(std_set_none_of, ST) {
  using pred_t = is_odd<it_value_t<ST>>;
  auto f = std::none_of<it_t<ST>, pred_t>;
  this->run(st, f, pred_t{});
}
BENCHMARK_REGISTER_F_(std_set_none_of);

// todo for_each, for_each_n

// count, count_if
BENCHMARK_TEMPLATE_DEFINE_F_(std_set_count, ST) {
  auto f = std::count<it_t<ST>, it_value_t<ST>>;
  this->run(st, f, 0);
}
BENCHMARK_REGISTER_F_(std_set_count);

BENCHMARK_TEMPLATE_DEFINE_F_(std_set_count_if, ST) {
  using pred_t = is_even<it_value_t<ST>>;
  auto f = std::count_if<it_t<ST>, pred_t>;
  this->run(st, f, pred_t{});
}
BENCHMARK_REGISTER_F_(std_set_count_if);

// todo mismatch

// find, find_if, find_if_not
BENCHMARK_TEMPLATE_DEFINE_F_(std_set_find, ST) {
  auto f = std::find<it_t<ST>, it_value_t<ST>>;
  this->run(st, f, 1);
}
BENCHMARK_REGISTER_F_(std_set_find);

BENCHMARK_TEMPLATE_DEFINE_F_(std_set_find_if, ST) {
  using pred_t = is_odd<it_value_t<ST>>;
  auto f = std::find_if<it_t<ST>, pred_t>;
  this->run(st, f, pred_t{});
}
BENCHMARK_REGISTER_F_(std_set_find_if);

BENCHMARK_TEMPLATE_DEFINE_F_(std_set_find_if_not, ST) {
  using pred_t = is_odd<it_value_t<ST>>;
  auto f = std::find_if_not<it_t<ST>, pred_t>;
  this->run(st, f, pred_t{});
}
BENCHMARK_REGISTER_F_(std_set_find_if_not);

// todo find_end, find_first_of

// adjacent_find
BENCHMARK_TEMPLATE_DEFINE_F_(std_set_adjacent_find, ST) {
  auto f = std::adjacent_find<it_t<ST>>;
  this->run(st, f);
}
BENCHMARK_REGISTER_F_(std_set_adjacent_find);

// todo search, search_n

///////////////////////////////////////
//
// unordered_map
//
///////////////////////////////////////

using UMT = std_unordered_map_t;

// all_of, any_of, none_of
BENCHMARK_TEMPLATE_DEFINE_F_(std_unordered_map_all_of, UMT) {
  using pred_t = is_even<it_value_t<UMT>>;
  auto f = std::all_of<it_t<UMT>, pred_t>;
  this->run(st, f, pred_t{});
}
BENCHMARK_REGISTER_F_(std_unordered_map_all_of);

BENCHMARK_TEMPLATE_DEFINE_F_(std_unordered_map_any_of, UMT) {
  using pred_t = is_odd<it_value_t<UMT>>;
  auto f = std::any_of<it_t<UMT>, pred_t>;
  this->run(st, f, pred_t{});
}
BENCHMARK_REGISTER_F_(std_unordered_map_any_of);

BENCHMARK_TEMPLATE_DEFINE_F_(std_unordered_map_none_of, UMT) {
  using pred_t = is_odd<it_value_t<UMT>>;
  auto f = std::none_of<it_t<UMT>, pred_t>;
  this->run(st, f, pred_t{});
}
BENCHMARK_REGISTER_F_(std_unordered_map_none_of);

// todo for_each, for_each_n

// count, count_if
BENCHMARK_TEMPLATE_DEFINE_F_(std_unordered_map_count, UMT) {
  auto f = std::count<it_t<UMT>, it_value_t<UMT>>;
  this->run(st, f, it_value_t<UMT>{0, 0});
}
BENCHMARK_REGISTER_F_(std_unordered_map_count);

BENCHMARK_TEMPLATE_DEFINE_F_(std_unordered_map_count_if, UMT) {
  using pred_t = is_even<it_value_t<UMT>>;
  auto f = std::count_if<it_t<UMT>, pred_t>;
  this->run(st, f, pred_t{});
}
BENCHMARK_REGISTER_F_(std_unordered_map_count_if);

// todo mismatch

// find, find_if, find_if_not
BENCHMARK_TEMPLATE_DEFINE_F_(std_unordered_map_find, UMT) {
  auto f = std::find<it_t<UMT>, it_value_t<UMT>>;
  this->run(st, f, it_value_t<UMT>{0, 1});
}
BENCHMARK_REGISTER_F_(std_unordered_map_find);

BENCHMARK_TEMPLATE_DEFINE_F_(std_unordered_map_find_if, UMT) {
  using pred_t = is_odd<it_value_t<UMT>>;
  auto f = std::find_if<it_t<UMT>, pred_t>;
  this->run(st, f, pred_t{});
}
BENCHMARK_REGISTER_F_(std_unordered_map_find_if);

BENCHMARK_TEMPLATE_DEFINE_F_(std_unordered_map_find_if_not, UMT) {
  using pred_t = is_odd<it_value_t<UMT>>;
  auto f = std::find_if_not<it_t<UMT>, pred_t>;
  this->run(st, f, pred_t{});
}
BENCHMARK_REGISTER_F_(std_unordered_map_find_if_not);

// todo find_end, find_first_of

// adjacent_find
BENCHMARK_TEMPLATE_DEFINE_F_(std_unordered_map_adjacent_find, UMT) {
  auto f = std::adjacent_find<it_t<UMT>>;
  this->run(st, f);
}
BENCHMARK_REGISTER_F_(std_unordered_map_adjacent_find);

// todo search, search_n
