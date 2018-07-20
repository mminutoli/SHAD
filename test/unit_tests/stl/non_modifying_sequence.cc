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
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

#include "common.hpp"
using namespace shad_test_stl;

template <typename T>
class NonModifyingSequenceTest : public ::testing::Test {
 protected:
  using value_type = it_value_t<T>;

  virtual ~NonModifyingSequenceTest() {}
  static constexpr size_t kNumElements = 1024, num_objs = 128;
};

template <typename T>
class AllOfTest : public NonModifyingSequenceTest<T> {
  using value_type = typename NonModifyingSequenceTest<T>::value_type;

 protected:
  template <typename F>
  void run(F &&f) {
    auto in = create_container_<T>(this->kNumElements);
    auto observed = f(in.begin(), in.end(), is_even<value_type>{});
    auto expected = all_of_(in.begin(), in.end(), is_even<value_type>{});
    ASSERT_EQ(observed, expected);
  }

 private:
  template <class InputIt, class UnaryPredicate>
  bool all_of_(InputIt first, InputIt last, UnaryPredicate p) {
    return std::find_if_not(first, last, p) == last;
  }
};

template <typename T>
class AnyOfTest : public NonModifyingSequenceTest<T> {
  using value_type = typename NonModifyingSequenceTest<T>::value_type;

 protected:
  template <typename F>
  void run(F &&f) {
    auto in = create_container_<T>(this->kNumElements);
    auto observed = f(in.begin(), in.end(), is_even<value_type>{});
    auto expected = any_of_(in.begin(), in.end(), is_even<value_type>{});
    ASSERT_EQ(observed, expected);
  }

 private:
  template <class InputIt, class UnaryPredicate>
  bool any_of_(InputIt first, InputIt last, UnaryPredicate p) {
    return std::find_if(first, last, p) != last;
  }
};

template <typename T>
class NoneOfTest : public NonModifyingSequenceTest<T> {
  using value_type = typename NonModifyingSequenceTest<T>::value_type;

 protected:
  template <typename F>
  void run(F &&f) {
    auto in = create_container_<T>(this->kNumElements);
    auto observed = f(in.begin(), in.end(), is_even<value_type>{});
    auto expected = none_of_(in.begin(), in.end(), is_even<value_type>{});
    ASSERT_EQ(observed, expected);
  }

 private:
  template <class InputIt, class UnaryPredicate>
  bool none_of_(InputIt first, InputIt last, UnaryPredicate p) {
    return std::find_if(first, last, p) == last;
  }
};

// todo for_each

template <typename T>
class CountTest : public NonModifyingSequenceTest<T> {
 protected:
  template <typename F>
  void run(F &&f) {
    auto in = create_container_<T>(this->kNumElements);
    auto objs = cherry_pick_(in);

    for (auto &obj : objs) {
      auto observed = f(in.begin(), in.end(), obj);
      auto expected = count_(in.begin(), in.end(), obj);
      ASSERT_EQ(observed, expected);
    }
  }

 private:
  template <class InputIt, class T_>
  typename std::iterator_traits<InputIt>::difference_type count_(
      InputIt first, InputIt last, const T_ &value) {
    typename std::iterator_traits<InputIt>::difference_type ret = 0;
    for (; first != last; ++first) {
      if (*first == value) {
        ret++;
      }
    }
    return ret;
  }
};

template <typename T>
class MismatchTest : public NonModifyingSequenceTest<T> {
 protected:
  template <typename F>
  void run(F &&f) {
    auto in = create_container_<T>(this->kNumElements);

    for (size_t i = 0; i < this->num_objs; ++i) {
      auto s = maybe_subseq_from_(in, i);

      auto observed = f(in.begin(), in.end(), s.begin());
      auto expected = mismatch_(in.begin(), in.end(), s.begin());
      ASSERT_EQ(observed, expected);
    }
  }

 private:
  template <class InputIt1, class InputIt2>
  std::pair<InputIt1, InputIt2> mismatch_(InputIt1 first1, InputIt1 last1,
                                          InputIt2 first2) {
    while (first1 != last1 && *first1 == *first2) {
      ++first1, ++first2;
    }
    return std::make_pair(first1, first2);
  }
};

template <typename T>
class FindTest : public NonModifyingSequenceTest<T> {
 protected:
  template <typename F>
  void run(F &&f) {
    auto in = create_container_<T>(this->kNumElements);
    auto objs = cherry_pick_(in);

    for (auto &obj : objs) {
      auto observed = f(in.begin(), in.end(), obj);
      auto expected = find_(in.begin(), in.end(), obj);
      ASSERT_EQ(observed, expected);
    }
  }

 private:
  template <class InputIt, class T_>
  InputIt find_(InputIt first, InputIt last, const T_ &value) {
    for (; first != last; ++first) {
      if (*first == value) {
        return first;
      }
    }
    return last;
  }
};

template <typename T>
class FindIfTest : public NonModifyingSequenceTest<T> {
  using value_type = typename NonModifyingSequenceTest<T>::value_type;

 protected:
  template <typename F>
  void run(F &&f) {
    auto in = create_container_<T>(this->kNumElements);
    auto observed = f(in.begin(), in.end(), is_even<value_type>{});
    auto expected = find_if_(in.begin(), in.end(), is_even<value_type>{});
    ASSERT_EQ(observed, expected);
  }

 private:
  template <class InputIt, class UnaryPredicate>
  InputIt find_if_(InputIt first, InputIt last, UnaryPredicate p) {
    for (; first != last; ++first) {
      if (p(*first)) {
        return first;
      }
    }
    return last;
  }
};

template <typename T>
class FindIfNotTest : public NonModifyingSequenceTest<T> {
  using value_type = typename NonModifyingSequenceTest<T>::value_type;

 protected:
  template <typename F>
  void run(F &&f) {
    auto in = create_container_<T>(this->kNumElements);
    auto observed = f(in.begin(), in.end(), is_even<value_type>{});
    auto expected = find_if_not_(in.begin(), in.end(), is_even<value_type>{});
    ASSERT_EQ(observed, expected);
  }

 private:
  template <class InputIt, class UnaryPredicate>
  InputIt find_if_not_(InputIt first, InputIt last, UnaryPredicate q) {
    for (; first != last; ++first) {
      if (!q(*first)) {
        return first;
      }
    }
    return last;
  }
};

template <typename T>
class FindEndTest : public NonModifyingSequenceTest<T> {
 protected:
  template <typename F>
  void run(F &&f) {
    auto in = create_container_<T>(this->kNumElements);

    for (size_t i = 0; i < this->num_objs; ++i) {
      auto s = maybe_subseq_from_(in, i);
      auto observed = f(in.begin(), in.end(), s.begin(), s.end());
      auto expected = find_end_(in.begin(), in.end(), s.begin(), s.end());
      ASSERT_EQ(observed, expected);
    }
  }

 private:
  template <class ForwardIt1, class ForwardIt2>
  ForwardIt1 find_end_(ForwardIt1 first, ForwardIt1 last, ForwardIt2 s_first,
                       ForwardIt2 s_last) {
    if (s_first == s_last) return last;
    ForwardIt1 result = last;
    while (true) {
      ForwardIt1 new_result = std::search(first, last, s_first, s_last);
      if (new_result == last) {
        break;
      } else {
        result = new_result;
        first = result;
        ++first;
      }
    }
    return result;
  }
};

template <typename T>
class FindFirstOfTest : public NonModifyingSequenceTest<T> {
 protected:
  template <typename F>
  void run(F &&f) {
    auto in = create_container_<T>(this->kNumElements);

    for (size_t i = 0; i < this->num_objs; ++i) {
      auto s = maybe_subseq_from_(in, i);
      auto observed = f(in.begin(), in.end(), s.begin(), s.end());
      auto expected = find_first_of_(in.begin(), in.end(), s.begin(), s.end());
      ASSERT_EQ(observed, expected);
    }
  }

 private:
  template <class InputIt, class ForwardIt>
  InputIt find_first_of_(InputIt first, InputIt last, ForwardIt s_first,
                         ForwardIt s_last) {
    for (; first != last; ++first) {
      for (ForwardIt it = s_first; it != s_last; ++it) {
        if (*first == *it) {
          return first;
        }
      }
    }
    return last;
  }
};

template <typename T>
class AdjacentFindTest : public NonModifyingSequenceTest<T> {
 protected:
  template <typename F>
  void run(F &&f) {
    auto in = create_container_<T>(this->kNumElements);
    auto observed = f(in.begin(), in.end());
    auto expected = adjacent_find_(in.begin(), in.end());
    ASSERT_EQ(observed, expected);
  }

 private:
  template <class ForwardIt>
  ForwardIt adjacent_find_(ForwardIt first, ForwardIt last) {
    if (first == last) {
      return last;
    }
    ForwardIt next = first;
    ++next;
    for (; next != last; ++next, ++first) {
      if (*first == *next) {
        return first;
      }
    }
    return last;
  }
};

template <typename T>
class SearchTest : public NonModifyingSequenceTest<T> {
 protected:
  template <typename F>
  void run(F &&f) {
    auto in = create_container_<T>(this->kNumElements);

    for (size_t i = 0; i < this->num_objs; ++i) {
      auto s = maybe_subseq_from_(in, i);
      auto observed = f(in.begin(), in.end(), s.begin(), s.end());
      auto expected = search_(in.begin(), in.end(), s.begin(), s.end());
      ASSERT_EQ(observed, expected);
    }
  }

 private:
  template <class ForwardIt1, class ForwardIt2>
  ForwardIt1 search_(ForwardIt1 first, ForwardIt1 last, ForwardIt2 s_first,
                     ForwardIt2 s_last) {
    for (;; ++first) {
      ForwardIt1 it = first;
      for (ForwardIt2 s_it = s_first;; ++it, ++s_it) {
        if (s_it == s_last) {
          return first;
        }
        if (it == last) {
          return last;
        }
        if (!(*it == *s_it)) {
          break;
        }
      }
    }
  }
};

template <typename T>
class SearchNTest : public NonModifyingSequenceTest<T> {
 protected:
  template <typename F>
  void run(F &&f) {
    auto in = create_container_<T>(this->kNumElements);
    auto objs = cherry_pick_(in);

    for (auto &obj : objs) {
      for (size_t i = 0; i < 4; ++i) {
        auto observed = f(in.begin(), in.end(), i, obj);
        auto expected = search_n_(in.begin(), in.end(), i, obj);
        ASSERT_EQ(observed, expected);
      }
    }
  }

 private:
  template <class ForwardIt, class Size, class T_>
  ForwardIt search_n_(ForwardIt first, ForwardIt last, Size count,
                      const T_ &value) {
    for (; first != last; ++first) {
      if (!(*first == value)) {
        continue;
      }

      ForwardIt candidate = first;
      Size cur_count = 0;

      while (true) {
        ++cur_count;
        if (cur_count == count) {
          // success
          return candidate;
        }
        ++first;
        if (first == last) {
          // exhausted the list
          return last;
        }
        if (!(*first == value)) {
          // too few in a row
          break;
        }
      }
    }
    return last;
  }
};

//
// std (sequential)
//
TYPED_TEST_CASE(FindIfTest, AllTypes);
TYPED_TEST(FindIfTest, std) {
  this->run(std::find_if<it_t<TypeParam>, is_even<it_value_t<TypeParam>>>);
}

TYPED_TEST_CASE(FindIfNotTest, AllTypes);
TYPED_TEST(FindIfNotTest, std) {
  this->run(std::find_if_not<it_t<TypeParam>, is_even<it_value_t<TypeParam>>>);
}

TYPED_TEST_CASE(AllOfTest, AllTypes);
TYPED_TEST(AllOfTest, std) {
  this->run(std::all_of<it_t<TypeParam>, is_even<it_value_t<TypeParam>>>);
}

TYPED_TEST_CASE(AnyOfTest, AllTypes);
TYPED_TEST(AnyOfTest, std) {
  this->run(std::any_of<it_t<TypeParam>, is_even<it_value_t<TypeParam>>>);
}

TYPED_TEST_CASE(NoneOfTest, AllTypes);
TYPED_TEST(NoneOfTest, std) {
  this->run(std::none_of<it_t<TypeParam>, is_even<it_value_t<TypeParam>>>);
}

// todo for_each

TYPED_TEST_CASE(CountTest, AllTypes);
TYPED_TEST(CountTest, std) {
  this->run(std::count<it_t<TypeParam>, it_value_t<TypeParam>>);
}

// todo mismatch - need fixing compilation

TYPED_TEST_CASE(FindTest, AllTypes);
TYPED_TEST(FindTest, std) {
  this->run(std::find<it_t<TypeParam>, it_value_t<TypeParam>>);
}

TYPED_TEST_CASE(FindEndTest, AllTypes);
TYPED_TEST(FindEndTest, std) {
  this->run(std::find_end<it_t<TypeParam>, it_t<TypeParam>>);
}

TYPED_TEST_CASE(FindFirstOfTest, AllTypes);
TYPED_TEST(FindFirstOfTest, std) {
  this->run(std::find_first_of<it_t<TypeParam>, it_t<TypeParam>>);
}

TYPED_TEST_CASE(AdjacentFindTest, AllTypes);
TYPED_TEST(AdjacentFindTest, std) {
  this->run(std::adjacent_find<it_t<TypeParam>>);
}

TYPED_TEST_CASE(SearchTest, AllTypes);
TYPED_TEST(SearchTest, std) {
  this->run(std::search<it_t<TypeParam>, it_t<TypeParam>>);
}

// todo search_n - need correctness fix

//
// todo sequential shad
//

//
// todo distributed shad
//

//
// todo distributed-async shad
//
