/* Copyright 2017 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

// This header declares functions which may be called by the generated code on
// the CPU. Calls to these functions must be resolved explicitly in the JIT in
// xla::cpu::SimpleResolver.  It also defines a per-CpuExecutable context
// which is used to cache expensive state and resources utilized by the
// aforementioned functions.

#ifndef TENSORFLOW_COMPILER_XLA_SERVICE_CPU_CPU_RUNTIME_SSE4_1_H_
#define TENSORFLOW_COMPILER_XLA_SERVICE_CPU_CPU_RUNTIME_SSE4_1_H_

#include "tensorflow/core/platform/macros.h"

// MSVC does not have __SSE4_1__ macro. Eigen enables EIGEN_VECTORIZE_SSE4_1
// when __AVX__ is defined, we should do the same.
#if defined(__SSE4_1__) || (defined(_MSC_VER) && defined(__AVX__))
#include <smmintrin.h>
#define TF_XLA_HAS_SSE4_1
#endif

namespace xla {
namespace cpu {
namespace runtime {

extern const char *const kLogV4F32SSESymbolName;

#ifdef TF_XLA_HAS_SSE4_1
typedef __m128 V4F32SSE;
#endif

}  // namespace runtime
}  // namespace cpu
}  // namespace xla

extern "C" {

#ifdef TF_XLA_HAS_SSE4_1
// The following functions are vectorized versions of a selection of libm
// library functions.
// References to these functions are created by the LLVM vectorizer.
xla::cpu::runtime::V4F32SSE __xla_cpu_runtime_LogV4F32SSE(
    xla::cpu::runtime::V4F32SSE x);
#endif
}

#endif  // TENSORFLOW_COMPILER_XLA_SERVICE_CPU_CPU_RUNTIME_SSE4_1_H_
