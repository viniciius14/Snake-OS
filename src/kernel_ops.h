#ifndef KERNEL_OPS_H
#define KERNEL_OPS_H

#include "utils.h"

void move_cursor(void);
void scroll(void);
void k_put_c(char c);
void k_clear(void);
void k_print(const char *c);
void k_print_hex(uint32_t);
void k_print_dec(uint32_t);
void k_panic(const char *, const char*, bool);

void  memset(void *dst, uint8_t value, size_t n);
void  *memcpy(void *dst, const void *src, size_t n);
void  *memmove(void *dst, const void *src, size_t n);

void fpu_init(void);

#endif /* KERNEL_OPS_H */