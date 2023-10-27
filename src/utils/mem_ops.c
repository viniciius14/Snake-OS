#include "mem_ops.h"

/* Sets n bytes of memory to value starting at address dst */
static inline void memset(void *dst, uint8_t value, size_t n) {
    uint8_t *d = dst;
    while(n-- > 0){
        *(d++) = value;
    }
}

/* Copies n bytes of memory from src to dst */
static inline void *memcpy(void *dst, const void *src, size_t n) {
    uint8_t *d = dst;
    const uint8_t *s = src;

    while(n-- > 0){
        *(d++) = *(s++);
    }
}

/* Moves n bytes from src to dst */
static inline void *memmove(void *dst, const void *src, size_t n) {
    if(src > dst) {
        return memcpy(dst, src, n);
    }

    uint8_t *d = dst;
    const uint8_t *s = src;

    for (size_t i = n; i > 0; i--) {
        d[i - 1] = s[i - 1];
    }

    return dst;
}
