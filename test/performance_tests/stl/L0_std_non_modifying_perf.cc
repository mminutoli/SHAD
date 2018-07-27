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
#include <unordered_map>
#include <vector>

#include "benchmark/benchmark.h"

#include "shad/data_structures/array.h"  //todo

#include "common.h"

///////////////////////////////////////
//
// vector
//
///////////////////////////////////////
// all_of, any_of, none_of
BENCHMARK_TEMPLATE_DEFINE_F(VectorPerf, std_vector_all_of, std::vector<int>)
(benchmark::State& st) {
  using it_t = typeof(this->in->begin());
  using value_t = typeof(*this->in->begin());
  using pred_t = shad_test_stl::is_even<value_t>;
  auto f = std::all_of<it_t, pred_t>;
  this->run(st, f, pred_t{});
  assert(f(this->in->begin(), this->in->end(), pred_t{}));
}
BENCHMARK_REGISTER_F_(VectorPerf, std_vector_all_of);

BENCHMARK_TEMPLATE_DEFINE_F(VectorPerf, std_vector_any_of, std::vector<int>)
(benchmark::State& st) {
  using it_t = typeof(this->in->begin());
  using value_t = typeof(*this->in->begin());
  using pred_t = shad_test_stl::is_odd<value_t>;
  auto f = std::any_of<it_t, pred_t>;
  this->run(st, f, pred_t{});
}
BENCHMARK_REGISTER_F_(VectorPerf, std_vector_any_of);

BENCHMARK_TEMPLATE_DEFINE_F(VectorPerf, std_vector_none_of, std::vector<int>)
(benchmark::State& st) {
  using it_t = typeof(this->in->begin());
  using value_t = typeof(*this->in->begin());
  using pred_t = shad_test_stl::is_odd<value_t>;
  auto f = std::none_of<it_t, pred_t>;
  this->run(st, f, pred_t{});
}
BENCHMARK_REGISTER_F_(VectorPerf, std_vector_none_of);

// todo for_each, for_each_n

// count, count_if
BENCHMARK_TEMPLATE_DEFINE_F(VectorPerf, std_vector_count, std::vector<int>)
(benchmark::State& st) {
  using it_t = typeof(this->in->begin());
  using value_t = typeof(*this->in->begin());
  auto f = std::count<it_t, value_t>;
  this->run(st, f, 0);
}
BENCHMARK_REGISTER_F_(VectorPerf, std_vector_count);

BENCHMARK_TEMPLATE_DEFINE_F(VectorPerf, std_vector_count_if, std::vector<int>)
(benchmark::State& st) {
  using it_t = typeof(this->in->begin());
  using value_t = typeof(*this->in->begin());
  using pred_t = shad_test_stl::is_even<value_t>;
  auto f = std::count_if<it_t, pred_t>;
  this->run(st, f, pred_t{});
}
BENCHMARK_REGISTER_F_(VectorPerf, std_vector_count_if);

// todo mismatch

// find, find_if, find_if_not
BENCHMARK_TEMPLATE_DEFINE_F(VectorPerf, std_vector_find, std::vector<int>)
(benchmark::State& st) {
  using it_t = typeof(this->in->begin());
  using value_t = typeof(*this->in->begin());
  auto f = std::find<it_t, value_t>;
  this->run(st, f, 1);
}
BENCHMARK_REGISTER_F_(VectorPerf, std_vector_find);

BENCHMARK_TEMPLATE_DEFINE_F(VectorPerf, std_vector_find_if, std::vector<int>)
(benchmark::State& st) {
  using it_t = typeof(this->in->begin());
  using value_t = typeof(*this->in->begin());
  using pred_t = shad_test_stl::is_odd<value_t>;
  auto f = std::find_if<it_t, pred_t>;
  this->run(st, f, pred_t{});
}
BENCHMARK_REGISTER_F_(VectorPerf, std_vector_find_if);

BENCHMARK_TEMPLATE_DEFINE_F(VectorPerf, std_vector_find_if_not,
                            std::vector<int>)
(benchmark::State& st) {
  using it_t = typeof(this->in->begin());
  using value_t = typeof(*this->in->begin());
  using pred_t = shad_test_stl::is_even<value_t>;
  auto f = std::find_if_not<it_t, pred_t>;
  this->run(st, f, pred_t{});
}
BENCHMARK_REGISTER_F_(VectorPerf, std_vector_find_if_not);

// todo find_end, find_first_of

// adjacent_find
BENCHMARK_TEMPLATE_DEFINE_F(VectorPerf, std_vector_adjacent_find,
                            std::vector<int>)
(benchmark::State& st) {
  using it_t = typeof(this->in->begin());
  auto f = std::adjacent_find<it_t>;
  this->run(st, f);
}
BENCHMARK_REGISTER_F_(VectorPerf, std_vector_adjacent_find);

// todo search, search_n

///////////////////////////////////////
//
// unordered_map
//
///////////////////////////////////////
using std_map_t = std::unordered_map<int, int>;

// all_of, any_of, none_of
BENCHMARK_TEMPLATE_DEFINE_F(MapPerf, std_unordered_map_all_of, std_map_t)
(benchmark::State& st) {
  using it_t = typeof(this->in->begin());
  using value_t = typeof(*this->in->begin());
  using pred_t = shad_test_stl::is_even<value_t>;
  auto f = std::all_of<it_t, pred_t>;
  this->run(st, f, pred_t{});
}
// BENCHMARK_REGISTER_F_(MapPerf, std_unordered_map_all_of);

BENCHMARK_TEMPLATE_DEFINE_F(MapPerf, std_unordered_map_any_of, std_map_t)
(benchmark::State& st) {
  using it_t = typeof(this->in->begin());
  using value_t = typeof(*this->in->begin());
  using pred_t = shad_test_stl::is_odd<value_t>;
  auto f = std::any_of<it_t, pred_t>;
  this->run(st, f, pred_t{});
}
BENCHMARK_REGISTER_F_(MapPerf, std_unordered_map_any_of);

BENCHMARK_TEMPLATE_DEFINE_F(MapPerf, std_unordered_map_none_of, std_map_t)
(benchmark::State& st) {
  using it_t = typeof(this->in->begin());
  using value_t = typeof(*this->in->begin());
  using pred_t = shad_test_stl::is_odd<value_t>;
  auto f = std::none_of<it_t, pred_t>;
  this->run(st, f, pred_t{});
}
BENCHMARK_REGISTER_F_(MapPerf, std_unordered_map_none_of);

// todo for_each, for_each_n

// count, count_if
BENCHMARK_TEMPLATE_DEFINE_F(MapPerf, std_unordered_map_count, std_map_t)
(benchmark::State& st) {
  using it_t = typeof(this->in->begin());
  using value_t = typeof(*this->in->begin());
  auto f = std::count<it_t, value_t>;
  this->run(st, f, value_t{0, 0});
}
BENCHMARK_REGISTER_F_(MapPerf, std_unordered_map_count);

BENCHMARK_TEMPLATE_DEFINE_F(MapPerf, std_unordered_map_count_if, std_map_t)
(benchmark::State& st) {
  using it_t = typeof(this->in->begin());
  using value_t = typeof(*this->in->begin());
  using pred_t = shad_test_stl::is_even<value_t>;
  auto f = std::count_if<it_t, pred_t>;
  this->run(st, f, pred_t{});
}
BENCHMARK_REGISTER_F_(MapPerf, std_unordered_map_count_if);

// todo mismatch

// find, find_if, find_if_not
BENCHMARK_TEMPLATE_DEFINE_F(MapPerf, std_unordered_map_find, std_map_t)
(benchmark::State& st) {
  using it_t = typeof(this->in->begin());
  using value_t = typeof(*this->in->begin());
  auto f = std::find<it_t, value_t>;
  this->run(st, f, value_t{0, 1});
}
BENCHMARK_REGISTER_F_(MapPerf, std_unordered_map_find);

BENCHMARK_TEMPLATE_DEFINE_F(MapPerf, std_unordered_map_find_if, std_map_t)
(benchmark::State& st) {
  using it_t = typeof(this->in->begin());
  using value_t = typeof(*this->in->begin());
  using pred_t = shad_test_stl::is_odd<value_t>;
  auto f = std::find_if<it_t, pred_t>;
  this->run(st, f, pred_t{});
}
BENCHMARK_REGISTER_F_(MapPerf, std_unordered_map_find_if);

BENCHMARK_TEMPLATE_DEFINE_F(MapPerf, std_unordered_map_find_if_not, std_map_t)
(benchmark::State& st) {
  using it_t = typeof(this->in->begin());
  using value_t = typeof(*this->in->begin());
  using pred_t = shad_test_stl::is_even<value_t>;
  auto f = std::find_if_not<it_t, pred_t>;
  this->run(st, f, pred_t{});
}
BENCHMARK_REGISTER_F_(MapPerf, std_unordered_map_find_if_not);

// todo find_end, find_first_of

// adjacent_find
BENCHMARK_TEMPLATE_DEFINE_F(MapPerf, std_unordered_map_adjacent_find, std_map_t)
(benchmark::State& st) {
  using it_t = typeof(this->in->begin());
  auto f = std::adjacent_find<it_t>;
  this->run(st, f);
}
BENCHMARK_REGISTER_F_(MapPerf, std_unordered_map_adjacent_find);

// todo search, search_n

///////////////////////////////////////
//
// set
//
///////////////////////////////////////
// all_of, any_of, none_of
BENCHMARK_TEMPLATE_DEFINE_F(SetPerf, std_set_all_of, std::set<int>)
(benchmark::State& st) {
  using it_t = typeof(this->in->begin());
  using value_t = typeof(*this->in->begin());
  using pred_t = shad_test_stl::is_even<value_t>;
  auto f = std::all_of<it_t, pred_t>;
  this->run(st, f, pred_t{});
}
BENCHMARK_REGISTER_F_(SetPerf, std_set_all_of);

BENCHMARK_TEMPLATE_DEFINE_F(SetPerf, std_set_any_of, std::set<int>)
(benchmark::State& st) {
  using it_t = typeof(this->in->begin());
  using value_t = typeof(*this->in->begin());
  using pred_t = shad_test_stl::is_odd<value_t>;
  auto f = std::any_of<it_t, pred_t>;
  this->run(st, f, pred_t{});
}
BENCHMARK_REGISTER_F_(SetPerf, std_set_any_of);

BENCHMARK_TEMPLATE_DEFINE_F(SetPerf, std_set_none_of, std::set<int>)
(benchmark::State& st) {
  using it_t = typeof(this->in->begin());
  using value_t = typeof(*this->in->begin());
  using pred_t = shad_test_stl::is_odd<value_t>;
  auto f = std::none_of<it_t, pred_t>;
  this->run(st, f, pred_t{});
}
BENCHMARK_REGISTER_F_(SetPerf, std_set_none_of);

// todo for_each, for_each_n

// count, count_if
BENCHMARK_TEMPLATE_DEFINE_F(SetPerf, std_set_count, std::set<int>)
(benchmark::State& st) {
  using it_t = typeof(this->in->begin());
  using value_t = typeof(*this->in->begin());
  auto f = std::count<it_t, value_t>;
  this->run(st, f, 0);
}
BENCHMARK_REGISTER_F_(SetPerf, std_set_count);

BENCHMARK_TEMPLATE_DEFINE_F(SetPerf, std_set_count_if, std::set<int>)
(benchmark::State& st) {
  using it_t = typeof(this->in->begin());
  using value_t = typeof(*this->in->begin());
  using pred_t = shad_test_stl::is_even<value_t>;
  auto f = std::count_if<it_t, pred_t>;
  this->run(st, f, pred_t{});
}
BENCHMARK_REGISTER_F_(SetPerf, std_set_count_if);

// todo mismatch

// find, find_if, find_if_not
BENCHMARK_TEMPLATE_DEFINE_F(SetPerf, std_set_find, std::set<int>)
(benchmark::State& st) {
  using it_t = typeof(this->in->begin());
  using value_t = typeof(*this->in->begin());
  auto f = std::find<it_t, value_t>;
  this->run(st, f, 1);
}
BENCHMARK_REGISTER_F_(SetPerf, std_set_find);

BENCHMARK_TEMPLATE_DEFINE_F(SetPerf, std_set_find_if, std::set<int>)
(benchmark::State& st) {
  using it_t = typeof(this->in->begin());
  using value_t = typeof(*this->in->begin());
  using pred_t = shad_test_stl::is_odd<value_t>;
  auto f = std::find_if<it_t, pred_t>;
  this->run(st, f, pred_t{});
}
BENCHMARK_REGISTER_F_(SetPerf, std_set_find_if);

BENCHMARK_TEMPLATE_DEFINE_F(SetPerf, std_set_find_if_not, std::set<int>)
(benchmark::State& st) {
  using it_t = typeof(this->in->begin());
  using value_t = typeof(*this->in->begin());
  using pred_t = shad_test_stl::is_even<value_t>;
  auto f = std::find_if_not<it_t, pred_t>;
  this->run(st, f, pred_t{});
}
BENCHMARK_REGISTER_F_(SetPerf, std_set_find_if_not);

// todo find_end, find_first_of

// adjacent_find
BENCHMARK_TEMPLATE_DEFINE_F(SetPerf, std_set_adjacent_find, std::set<int>)
(benchmark::State& st) {
  using it_t = typeof(this->in->begin());
  auto f = std::adjacent_find<it_t>;
  this->run(st, f);
}
BENCHMARK_REGISTER_F_(SetPerf, std_set_adjacent_find);

// todo search, search_n
