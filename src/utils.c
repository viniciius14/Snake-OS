#include "utils.h"

/* Outputs a uint8_t to the specified hardware port */
void outb(uint32_t port,uint8_t value) {
	__asm__ volatile ("outb %%al,%%dx"::"d" (port), "a" (value));
}

/* Outputs a word to a port */
void outw(uint32_t port,uint32_t value) {
	__asm__ volatile ("outw %%ax,%%dx"::"d" (port), "a" (value));
}

/* gets a uint8_t from a port */
uint8_t inb(uint32_t port) {
	uint8_t value;
	__asm__ volatile ("inb %w1,%b0" : "=a"(value) : "d"(port));
	return value;
}

uint16_t inw(uint32_t port) {
    uint16_t value;
    __asm__ volatile("inw %1, %0" : "=a" (value) : "dN" (port));
    return value;
}

/* Wait 1 I/O cycle for I/O operation to complete */
void io_wait(void) {
    __asm__ __volatile__ ("outb %%al, $0x80" : : "a"(0));
}