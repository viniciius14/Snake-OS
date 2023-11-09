#include "io.h"

/* Outputs a byte to the specified hardware port */
static inline void outportb(uint32_t port, uint8_t value) {
    asm volatile("outb %%al, %%dx" : : "d" (port), "a" (value));
}

/* Outputs 2 bytes to the specified hardware port */
static inline void outportw(uint32_t port, uint32_t value) {
    asm volatile("outw %%ax, %%dx" : : "d" (port), "a" (value));
}

/* Gets a byte from the specified hardware port */
static inline uint8_t inportb(uint32_t port) {
	uint8_t value;
	asm volatile("inb %w1,%b0" : "=a"(value) : "d"(port));
	return value;
}

static inline uint16_t inportw(uint32_t port) {
    uint16_t value;
    asm volatile("inw %1, %0" : "=a" (value) : "dN" (port));
    return value;
}