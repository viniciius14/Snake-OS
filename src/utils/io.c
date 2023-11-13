#include "utils/io.h"

/* Outputs a uint8_t to the specified hardware port */
__inline__ void outportb(uint32_t port,uint8_t value) {
	__asm__ volatile ("outb %%al,%%dx"::"d" (port), "a" (value));
}

/* Outputs a word to a port */
__inline__ void outportw(uint32_t port,uint32_t value) {
	__asm__ volatile ("outw %%ax,%%dx"::"d" (port), "a" (value));
}

/* gets a uint8_t from a port */
__inline__ uint8_t inportb(uint32_t port) {
	uint8_t value;
	__asm__ volatile ("inb %w1,%b0" : "=a"(value) : "d"(port));
	return value;
}

__inline__ uint16_t inportw(uint32_t port) {
    uint16_t value;
    __asm__ volatile("inw %1, %0" : "=a" (value) : "dN" (port));
    return value;
}