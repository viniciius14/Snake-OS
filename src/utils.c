#include "utils.h"
#include "kernel_ops.h"

/* Sets n bytes of memory to value starting at address dst */
void memset(void *dst, uint8_t value, size_t n) {
    uint8_t *d = dst;
    while(n-- > 0) {
        *(d++) = value;
    }
}

/* Copies n bytes of memory from src to dst */
void *memcpy(void *dst, const void *src, size_t n) {
    uint8_t *d = dst;
    const uint8_t *s = src;

    while(n-- > 0) {
        *(d++) = *(s++);
    }
    return dst;
}

/* Moves n bytes from src to dst */
void *memmove(void *dst, const void *src, size_t n) {
    if(src > dst) {
        return memcpy(dst, src, n);
    }

    uint8_t *d = dst;
    const uint8_t *s = src;

    for (size_t i = n; i > 0; i--) {
        d[i - 1] = s[i - 1];
    }

    return dst;
}

/* Outputs a uint8_t to the specified hardware port */
void outportb(uint32_t port,uint8_t value) {
	__asm__ volatile ("outb %%al,%%dx"::"d" (port), "a" (value));
}

/* Outputs a word to a port */
void outportw(uint32_t port,uint32_t value) {
	__asm__ volatile ("outw %%ax,%%dx"::"d" (port), "a" (value));
}

/* gets a uint8_t from a port */
uint8_t inportb(uint32_t port) {
	uint8_t value;
	__asm__ volatile ("inb %w1,%b0" : "=a"(value) : "d"(port));
	return value;
}

uint16_t inportw(uint32_t port) {
    uint16_t value;
    __asm__ volatile("inw %1, %0" : "=a" (value) : "dN" (port));
    return value;
}

#ifdef DEBUG

/* Since we don't have a proper print func this hacky way will have to do for now */
void trace_enter() {
    const char* func_name = __func__;

    k_print("Entering: ", WHITE_TXT);
    k_print_var(func_name);
}

void trace_leave() {
    const char* func_name = __func__;

    k_print("Leaving: ", WHITE_TXT);
    k_print_var(func_name);
}

void context_dump() {
    uint32_t eax, ebx, ecx, edx, esp;

    __asm__ __volatile__ (
        "movl %%eax, %0\n\t"
        "movl %%ebx, %1\n\t"
        "movl %%ecx, %2\n\t"
        "movl %%edx, %3\n\t"
        "movl %%esp, %4\n\t"
        : "=r" (eax), "=r" (ebx), "=r" (ecx), "=r" (edx), "=r" (esp)
    );

    k_print("------ CONTEXT DUMP ------", WHITE_TXT);
    k_print_register("Register EAX: ",&eax, 4, WHITE_TXT);
    k_print_register("Register EBX: ",&ebx, 4, WHITE_TXT);
    k_print_register("Register ECX: ",&ecx, 4, WHITE_TXT);
    k_print_register("Register EDX: ",&edx, 4, WHITE_TXT);
    k_print_register("Register ESP: ",&esp, 4, WHITE_TXT);
    k_print("------ CONTEXT DUMP END ------", WHITE_TXT);
}

#endif