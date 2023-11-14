#ifndef MEM_OPS_H
#define MEM_OPS_H

#include "utils/types.h"

void  memset(void *dst, uint8_t value, size_t n);
void  *memcpy(void *dst, const void *src, size_t n);
void  *memmove(void *dst, const void *src, size_t n);

#endif /* MEM_OPS_H */