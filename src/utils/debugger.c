#include "utils/debugger.h"
#include "kernel/kernel_ops.h"
#include "utils/colors.h"
#include "utils/types.h"

/* Since we don't have a proper print func this hacky way will have to do for now */
void trace_enter() {
    const char* func_name = __FUNCTION__;

    k_print("Entering: ", WHITE_TXT);
    k_print_var(func_name);
}

void trace_leave() {
    const char* func_name = __FUNCTION__;

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