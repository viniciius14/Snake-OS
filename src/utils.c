#include "utils.h"

void memset(void *dst, uint8_t value, size_t n) {
    uint8_t *d = dst;
    while (n-- > 0) {
        *(d++) = value;
    }
}

void *memcpy(void *dst, const void *src, size_t n) {
    uint8_t *d = dst;
    const uint8_t *s = src;

    while (n-- > 0) {
        *(d++) = *(s++);
    }
    return dst;
}

void *memmove(void *dst, const void *src, size_t n) {
    if (src > dst) {
        return memcpy(dst, src, n);
    }

    uint8_t *d = dst;
    const uint8_t *s = src;

    for (size_t i = n ; i > 0 ; i--) {
        d[i - 1] = s[i - 1];
    }

    return dst;
}

void outb(uint32_t port,uint8_t value) {
	__asm__ volatile ("outb %%al,%%dx"::"d" (port), "a" (value));
}

void outw(uint32_t port,uint32_t value) {
	__asm__ volatile ("outw %%ax,%%dx"::"d" (port), "a" (value));
}

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

void io_wait(void) {
    ASM ("outb %%al, $0x80" : : "a"(0));
}