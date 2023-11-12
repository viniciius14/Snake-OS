#ifndef IO_H
#define IO_H

#include "utils/types.h"

/* Outputs a uint8_t to the specified hardware port */
__inline__ void outportb(uint32_t port,uint8_t value);

/* Outputs a word to a port */
__inline__ void outportw(uint32_t port,uint32_t value);

/* gets a uint8_t from a port */
__inline__ uint8_t inportb(uint32_t port);

__inline__ uint16_t inportw(uint32_t port);


#endif /* IO_H */