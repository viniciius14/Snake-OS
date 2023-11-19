#ifndef KERNEL_OPS_H
#define KERNEL_OPS_H

#include "utils.h"

void k_panic(const char *msg, const char* code, bool halt);
void k_print(const char *msg, const color text_color);
void k_print_var(const char * msg);
void k_print_register(const char* msg, const void *reg_addr, size_t num_bytes, color text_color);
void k_clear(void);

void  memset(void *dst, uint8_t value, size_t n);
void  *memcpy(void *dst, const void *src, size_t n);
void  *memmove(void *dst, const void *src, size_t n);

void fpu_init(void);

#endif /* KERNEL_OPS_H */