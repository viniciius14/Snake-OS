#ifndef IO_H
#define IO_H

#include "types.h"

void        outportb(uint32_t port, uint8_t value);
void        outportw(uint32_t port, uint32_t value);
uint8_t     inportb(uint32_t port);
uint16_t    inportw(uint32_t port);

#endif /* IO_H */