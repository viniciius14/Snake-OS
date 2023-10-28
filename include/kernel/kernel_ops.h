#ifndef KERNEL_OPS_H
#define KERNEL_OPS_H

#include "types.h"

void k_panic(char *message, char* code, bool halt);
void k_print(const char *msg, uint8_t line, color text_color);
void k_clear();

#endif /* KERNEL_OPS_H */