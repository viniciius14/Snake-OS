#ifndef KERNEL_OPS_H
#define KERNEL_OPS_H

#include "types.h"

void k_panic(const char *msg, const char* code, bool halt);
void k_print(const char *msg, const color text_color);
void k_print_var(const char * msg);
void k_clear();

#endif /* KERNEL_OPS_H */