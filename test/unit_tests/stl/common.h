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

#ifndef TEST_UNIT_TESTS_STL_COMMON_H_
#define TEST_UNIT_TESTS_STL_COMMON_H_

#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

#include "shad/data_structures/array.h"

namespace shad_test_stl {

static constexpr size_t kNumElements = 1024;

// container creation and expected checksum
template <typename T, bool even>
struct create_vector_ {
  std::shared_ptr<T> operator()(size_t) { return nullptr; }
};

template <typename T, bool even>
struct create_array_ {
  std::shared_ptr<T> operator()() { return nullptr; }
};

template <typename T, bool even>
struct create_set_ {
  std::shared_ptr<T> operator()(size_t) { return nullptr; }
};

template <typename T, bool even>
struct create_map_ {
  std::shared_ptr<T> operator()(size_t) { return nullptr; }
};

template <typename U, bool even>
struct create_vector_<std::vector<U>, even> {
  using T = std::vector<U>;
  std::shared_ptr<T> operator()(size_t size) {
    auto res = std::make_shared<T>();
    for (size_t i = 0; i < size; ++i) res->push_back(2 * i + !even);
    return res;
  }
};

template <typename U, size_t size, bool even>
struct create_array_<std::array<U, size>, even> {
  using T = std::array<U, size>;
  std::shared_ptr<T> operator()() {
    auto res = std::make_shared<T>();
    for (size_t i = 0; i < size; ++i) res->at(i) = 2 * i + !even;
    return res;
  }
};

template <typename U, size_t size, bool even>
struct create_array_<shad::array<U, size>, even> {
  using T = shad::array<U, size>;
  std::shared_ptr<T> operator()() {
    auto res = T::Create();
    for (size_t i = 0; i < size; ++i) res->at(i) = 2 * i + !even;
    return res;
  }
};

template <typename U, bool even>
struct create_set_<std::set<U>, even> {
  using T = std::set<U>;
  std::shared_ptr<T> operator()(size_t size) {
    auto res = std::make_shared<T>();
    for (size_t i = 0; i < size; ++i) res->insert(2 * i + !even);
    return res;
  }
};

template <typename U, typename V, bool even>
struct create_map_<std::unordered_map<U, V>, even> {
  using T = std::unordered_map<U, V>;
  std::shared_ptr<T> operator()(size_t size) {
    auto res = std::make_shared<T>();
    for (size_t i = 0; i < size; ++i) (*res)[i] = 2 * i + !even;
    return res;
  }
};

template <bool even>
int64_t expected_checksum_(size_t size) {
  int64_t res = 0;
  for (size_t i = 0; i < size; ++i) res += 2 * i + !even;
  return res;
}

// container destruction
template <typename T>
struct destroy_container_ {
  void operator()(std::shared_ptr<T>) {}
};

template <typename U, size_t size>
struct destroy_container_<shad::array<U, size>> {
  using T = shad::array<U, size>;
  void operator()(std::shared_ptr<T> c) { T::Destroy(c.get()->GetGlobalID()); }
};

// sub-sequencing from containers
template <typename T>
typename T::iterator it_seek_(std::shared_ptr<T> in, size_t start_idx) {
  auto first = in->begin();
  size_t i = 0;
  while (i++ < start_idx && first != in->end()) {
    assert(first != in->end());
    ++first;
  }
  return first;
}

template <typename T>
struct subseq_from_ {
  std::shared_ptr<T> operator()(std::shared_ptr<T> in, size_t start_idx,
                                size_t len) {
    return nullptr;
  }
};

template <typename U>
struct subseq_from_<std::vector<U>> {
  using T = std::vector<U>;
  std::shared_ptr<T> operator()(std::shared_ptr<T> in, size_t start_idx,
                                size_t len) {
    assert(start_idx < in->size());
    auto first = it_seek_(in, start_idx);
    auto res = std::make_shared<T>();
    for (size_t i = 0; i < len; ++i) {
      assert(first != in->end());
      res->push_back(*first++);
    }
    return res;
  }
};

template <typename U, size_t size>
struct subseq_from_<std::array<U, size>> {
  using T = std::array<U, size>;
  std::shared_ptr<T> operator()(std::shared_ptr<T> in, size_t start_idx,
                                size_t len) {
    assert(start_idx < size);
    auto first = it_seek_(in, start_idx);
    auto res = std::make_shared<T>();
    for (size_t i = 0; i < len; ++i) {
      assert(first != in->end());
      res->at(i) = *first++;
    }
    return res;
  }
};

template <typename U, size_t size>
struct subseq_from_<shad::array<U, size>> {
  using T = shad::array<U, size>;
  std::shared_ptr<T> operator()(std::shared_ptr<T> in, size_t start_idx,
                                size_t len) {
    assert(start_idx < size);
    auto first = it_seek(in, start_idx);
    auto res = T::Create();
    for (size_t i = 0; i < len; ++i) {
      assert(first != in->end());
      res->at(i) = *first++;
    }
    return res;
  }
};

template <typename U>
struct subseq_from_<std::set<U>> {
  using T = std::set<U>;
  std::shared_ptr<T> operator()(std::shared_ptr<T> in, size_t start_idx,
                                size_t len) {
    assert(start_idx < in->size());
    auto first = it_seek_(in, start_idx);
    auto res = std::make_shared<T>();
    for (size_t i = 0; i < len; ++i) {
      assert(first != in->end());
      res->insert(*first++);
    }
    return res;
  }
};

template <typename U, typename V>
struct subseq_from_<std::unordered_map<U, V>> {
  using T = std::unordered_map<U, V>;
  std::shared_ptr<T> operator()(std::shared_ptr<T> in, size_t start_idx,
                                size_t len) {
    assert(start_idx < in->size());
    auto first = it_seek_(in, start_idx);
    auto res = std::make_shared<T>();
    std::unordered_map<U, V> x;
    for (size_t i = 0; i < len; ++i) {
      assert(first != in->end());
      res->operator[]((*first).first) = (*first).second;
      ++first;
    }
    return res;
  }
};

// evenness/oddness test
template <typename T>
struct is_even {
  bool operator()(const T &x) { return !(x % 2); }
};

template <typename T, typename U>
struct is_even<std::pair<const T, U>> {
  bool operator()(const std::pair<const T, U> &x) {
    return is_even<U>{}(x.second);
  }
};

template <typename T>
struct is_odd {
  bool operator()(const T &x) { return !(is_even<T>{}(x)); }
};

// test fixtures
template <typename T>
class TestFixture : public ::testing::Test {
  void TearDown() { destroy_container_<T>{}(this->in); }

 public:
  template <typename F, typename... args_>
  void test(F &&sub_f, F &&obj_f, args_... args) {
    auto obs = sub_f(in->begin(), in->end(), args...);
    auto exp = obj_f(in->begin(), in->end(), args...);
    ASSERT_EQ(obs, exp);
  }

 protected:
  virtual ~TestFixture() {}
  std::shared_ptr<T> in;
};

template <typename T>
class VectorTestFixture : public TestFixture<T> {
  void SetUp() { this->in = create_vector_<T, true>{}(kNumElements); }

 protected:
  int64_t expected_checksum() { return expected_checksum_<true>(kNumElements); }
};

template <typename T>
class ArrayTestFixture : public TestFixture<T> {
  void SetUp() { this->in = create_array_<T, true>{}(); }

 protected:
  int64_t expected_checksum() { return expected_checksum_<true>(kNumElements); }
};

template <typename T>
class SetTestFixture : public TestFixture<T> {
  void SetUp() { this->in = create_set_<T, true>{}(kNumElements); }

 protected:
  int64_t expected_checksum() { return expected_checksum_<true>(kNumElements); }
};

template <typename T>
class MapTestFixture : public TestFixture<T> {
  void SetUp() { this->in = create_map_<T, true>{}(kNumElements); }

 protected:
  int64_t expected_checksum() { return expected_checksum_<true>(kNumElements); }
};
}  // namespace shad_test_stl

#endif
