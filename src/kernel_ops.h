#ifndef KERNEL_OPS_H
#define KERNEL_OPS_H

#include "utils.h"

void k_panic(const char *msg, const char* code, bool halt);
void k_print(const char *msg, const color text_color);
void k_print_var(const char * msg);
void k_print_register(const char* msg, const void *reg_addr, size_t num_bytes, color text_color);
void k_clear();

void fpu_init();

#endif /* KERNEL_OPS_H */