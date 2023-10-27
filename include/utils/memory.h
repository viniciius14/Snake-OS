#ifndef MEMORY_H
#define MEMORY_H

#include "types.h"

static inline void  memset(void *dst, uint8_t value, size_t n);
static inline void  *memcpy(void *dst, const void *src, size_t n);
static inline void  *memmove(void *dst, const void *src, size_t n);

#endif /* MEMORY_H */