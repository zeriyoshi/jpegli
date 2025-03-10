// Copyright (c) the JPEG XL Project Authors.
//
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file or at
// https://developers.google.com/open-source/licenses/bsd

#ifndef LIB_JPEGLI_MEMORY_MANAGER_H_
#define LIB_JPEGLI_MEMORY_MANAGER_H_

#include <cstdlib>

#include "lib/jpegli/common.h"

#define JPOOL_PERMANENT_ALIGNED (JPOOL_NUMPOOLS + JPOOL_PERMANENT)
#define JPOOL_IMAGE_ALIGNED (JPOOL_NUMPOOLS + JPOOL_IMAGE)

namespace jpegli {

void InitMemoryManager(j_common_ptr cinfo);

template <typename T>
T* Allocate(j_common_ptr cinfo, size_t len, int pool_id = JPOOL_PERMANENT) {
  const size_t size = len * sizeof(T);  // NOLINT
  void* p = (*cinfo->mem->alloc_small)(cinfo, pool_id, size);
  return reinterpret_cast<T*>(p);
}

template <typename T>
T* Allocate(j_decompress_ptr cinfo, size_t len, int pool_id = JPOOL_PERMANENT) {
  return Allocate<T>(reinterpret_cast<j_common_ptr>(cinfo), len, pool_id);
}

template <typename T>
T* Allocate(j_compress_ptr cinfo, size_t len, int pool_id = JPOOL_PERMANENT) {
  return Allocate<T>(reinterpret_cast<j_common_ptr>(cinfo), len, pool_id);
}

template <typename T>
JBLOCKARRAY GetBlockRow(T cinfo, int c, JDIMENSION by) {
  return (*cinfo->mem->access_virt_barray)(
      reinterpret_cast<j_common_ptr>(cinfo), cinfo->master->coeff_buffers[c],
      by, 1, true);
}

}  // namespace jpegli

#endif  // LIB_JPEGLI_MEMORY_MANAGER_H_
