#include "io.h"

/* Outputs a byte to the specified hardware port */
static inline void outportb(uint32_t port, uint8_t value) {
    asm("outb %%al, %%dx" : : "d" (port), "a" (value));
}

/* Outputs 2 bytes to the specified hardware port */
static inline void outportw(uint32_t port, uint32_t value) {
    asm("outw %%ax, %%dx" : : "d" (port), "a" (value));
}

/* Gets a byte from the specified hardware port */
static inline uint8_t inportb(uint32_t port) {
	uint8_t value;
	asm("inb %w1,%b0" : "=a"(value) : "d"(port));
	return value;
}
