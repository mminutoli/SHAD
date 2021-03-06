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

#ifndef INCLUDE_SHAD_RUNTIME_MAPPINGS_CPP_SIMPLE_CPP_SIMPLE_ASYNCHRONOUS_INTERFACE_H_
#define INCLUDE_SHAD_RUNTIME_MAPPINGS_CPP_SIMPLE_CPP_SIMPLE_ASYNCHRONOUS_INTERFACE_H_

#include <cstddef>
#include <cstdint>
#include <memory>
#include <utility>

#include "shad/runtime/asynchronous_interface.h"
#include "shad/runtime/handle.h"
#include "shad/runtime/locality.h"
#include "shad/runtime/mapping_traits.h"
#include "shad/runtime/mappings/cpp_simple/cpp_simple_traits_mapping.h"
#include "shad/runtime/mappings/cpp_simple/cpp_simple_utility.h"

namespace shad {
namespace rt {

namespace impl {

template <>
struct AsynchronousInterface<cpp_tag> {
  template <typename FunT, typename InArgsT>
  static void asyncExecuteAt(Handle &handle, const Locality &loc,
                             FunT &&function, const InArgsT &args) {
    checkLocality(loc);
    handle.id_ =
        handle.IsNull() ? HandleTrait<cpp_tag>::CreateNewHandle() : handle.id_;
    using FunctionTy = void (*)(Handle &, const InArgsT &);
    FunctionTy fn = std::forward<decltype(function)>(function);
    fn(handle, args);
  }

  template <typename FunT>
  static void asyncExecuteAt(Handle &handle, const Locality &loc,
                             FunT &&function,
                             const std::shared_ptr<uint8_t> &argsBuffer,
                             const uint32_t bufferSize) {
    checkLocality(loc);
    handle.id_ =
        handle.IsNull() ? HandleTrait<cpp_tag>::CreateNewHandle() : handle.id_;
    using FunctionTy = void (*)(Handle &, const uint8_t *, const uint32_t);
    FunctionTy fn = std::forward<decltype(function)>(function);
    fn(handle, argsBuffer.get(), bufferSize);
  }

  template <typename FunT, typename InArgsT>
  static void asyncExecuteAtWithRetBuff(Handle &handle, const Locality &loc,
                                        FunT &&function, const InArgsT &args,
                                        uint8_t *resultBuffer,
                                        uint32_t *resultSize) {
    checkLocality(loc);
    handle.id_ =
        handle.IsNull() ? HandleTrait<cpp_tag>::CreateNewHandle() : handle.id_;
    using FunctionTy =
        void (*)(Handle &, const InArgsT &, uint8_t *, uint32_t *);
    FunctionTy fn = std::forward<decltype(function)>(function);
    fn(handle, args, resultBuffer, resultSize);
  }

  template <typename FunT>
  static void asyncExecuteAtWithRetBuff(
      Handle &handle, const Locality &loc, FunT &&function,
      const std::shared_ptr<uint8_t> &argsBuffer, const uint32_t bufferSize,
      uint8_t *resultBuffer, uint32_t *resultSize) {
    checkLocality(loc);
    handle.id_ =
        handle.IsNull() ? HandleTrait<cpp_tag>::CreateNewHandle() : handle.id_;
    using FunctionTy = void (*)(Handle &, const uint8_t *, const uint32_t,
                                uint8_t *, uint32_t *);
    FunctionTy fn = std::forward<decltype(function)>(function);
    fn(handle, argsBuffer.get(), bufferSize, resultBuffer, resultSize);
  }

  template <typename FunT, typename InArgsT, typename ResT>
  static void asyncExecuteAtWithRet(Handle &handle, const Locality &loc,
                                    FunT &&function, const InArgsT &args,
                                    ResT *result) {
    checkLocality(loc);
    handle.id_ =
        handle.IsNull() ? HandleTrait<cpp_tag>::CreateNewHandle() : handle.id_;
    using FunctionTy = void (*)(Handle &, const InArgsT &, ResT *);
    FunctionTy fn = std::forward<decltype(function)>(function);
    fn(handle, args, result);
  }

  template <typename FunT, typename ResT>
  static void asyncExecuteAtWithRet(Handle &handle, const Locality &loc,
                                    FunT &&function,
                                    const std::shared_ptr<uint8_t> &argsBuffer,
                                    const uint32_t bufferSize, ResT *result) {
    checkLocality(loc);
    handle.id_ =
        handle.IsNull() ? HandleTrait<cpp_tag>::CreateNewHandle() : handle.id_;
    using FunctionTy =
        void (*)(Handle &, const uint8_t *, const uint32_t, ResT *);
    FunctionTy fn = std::forward<decltype(function)>(function);
    fn(handle, argsBuffer.get(), bufferSize, result);
  }

  template <typename FunT, typename InArgsT>
  static void asyncExecuteOnAll(Handle &handle, FunT &&function,
                                const InArgsT &args) {
    handle.id_ =
        handle.IsNull() ? HandleTrait<cpp_tag>::CreateNewHandle() : handle.id_;
    using FunctionTy = void (*)(Handle &, const InArgsT &);
    FunctionTy fn = std::forward<decltype(function)>(function);
    fn(handle, args);
  }

  template <typename FunT>
  static void asyncExecuteOnAll(Handle &handle, FunT &&function,
                                const std::shared_ptr<uint8_t> &argsBuffer,
                                const uint32_t bufferSize) {
    handle.id_ =
        handle.IsNull() ? HandleTrait<cpp_tag>::CreateNewHandle() : handle.id_;
    using FunctionTy = void (*)(Handle &, const uint8_t *, const uint32_t);
    FunctionTy fn = std::forward<decltype(function)>(function);
    fn(handle, argsBuffer.get(), bufferSize);
  }

  template <typename FunT, typename InArgsT>
  static void asyncForEachAt(Handle &handle, const Locality &loc,
                             FunT &&function, const InArgsT &args,
                             const size_t numIters) {
    checkLocality(loc);
    handle.id_ =
        handle.IsNull() ? HandleTrait<cpp_tag>::CreateNewHandle() : handle.id_;
    using FunctionTy = void (*)(Handle &, const InArgsT &, size_t);
    FunctionTy fn = std::forward<decltype(function)>(function);
    for (auto i = 0; i < numIters; ++i) fn(handle, args, i);
  }

  template <typename FunT>
  static void asyncForEachAt(Handle &handle, const Locality &loc,
                             FunT &&function,
                             const std::shared_ptr<uint8_t> &argsBuffer,
                             const uint32_t bufferSize, const size_t numIters) {
    checkLocality(loc);
    handle.id_ =
        handle.IsNull() ? HandleTrait<cpp_tag>::CreateNewHandle() : handle.id_;
    using FunctionTy =
        void (*)(Handle &, const uint8_t *, const uint32_t, size_t);
    FunctionTy fn = std::forward<decltype(function)>(function);
    for (auto i = 0; i < numIters; ++i)
      fn(handle, argsBuffer.get(), bufferSize, i);
  }

  template <typename FunT, typename InArgsT>
  static void asyncForEachOnAll(Handle &handle, FunT &&function,
                                const InArgsT &args, const size_t numIters) {
    handle.id_ =
        handle.IsNull() ? HandleTrait<cpp_tag>::CreateNewHandle() : handle.id_;
    using FunctionTy = void (*)(Handle &, const InArgsT &, size_t);
    FunctionTy fn = std::forward<decltype(function)>(function);
    for (auto i = 0; i < numIters; ++i) fn(handle, args, i);
  }

  template <typename FunT>
  static void asyncForEachOnAll(Handle &handle, FunT &&function,
                                const std::shared_ptr<uint8_t> &argsBuffer,
                                const uint32_t bufferSize,
                                const size_t numIters) {
    handle.id_ =
        handle.IsNull() ? HandleTrait<cpp_tag>::CreateNewHandle() : handle.id_;
    using FunctionTy =
        void (*)(Handle &, const uint8_t *, const uint32_t, size_t);
    FunctionTy fn = std::forward<decltype(function)>(function);
    for (auto i = 0; i < numIters; ++i)
      fn(handle, argsBuffer.get(), bufferSize, i);
  }
};

}  // namespace impl

}  // namespace rt
}  // namespace shad

#endif  // INCLUDE_SHAD_RUNTIME_MAPPINGS_CPP_SIMPLE_CPP_SIMPLE_ASYNCHRONOUS_INTERFACE_H_
