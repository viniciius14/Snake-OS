#include "utils.h"
#include "kernel_ops.h"

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

    k_print("Entering: ");
    k_print(func_name);
    k_print(" \n");
}

void trace_leave() {
    const char* func_name = __func__;

    k_print("Leaving: ");
    k_print(func_name);
    k_print(" \n");
}
/* WIP */
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

    // k_print("------ CONTEXT DUMP ------");
    // k_print_register("Register EAX: ",&eax, 4);
    // k_print_register("Register EBX: ",&ebx, 4);
    // k_print_register("Register ECX: ",&ecx, 4);
    // k_print_register("Register EDX: ",&edx, 4);
    // k_print_register("Register ESP: ",&esp, 4);
    // k_print("------ CONTEXT DUMP END ------");
}
#endif /* DEBUG */