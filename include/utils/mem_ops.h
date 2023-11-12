#ifndef MEM_OPS_H
#define MEM_OPS_H

#include "utils/types.h"

static inline void  memset(void *dst, uint8_t value, size_t n);
static inline void  *memcpy(void *dst, const void *src, size_t n);
static inline void  *memmove(void *dst, const void *src, size_t n);

#endif /* MEM_OPS_H */