#include "debugger.h"
#include "kernel_ops.h"
#include "colors.h"
#include "types.h"

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
    uint32_t eax, ebx, ecx, edx, esi, edi, ebp, esp, eip;

    asm volatile(
        "pusha\n\t"
        "call 1f\n" // Call the next instruction, which pushes EIP onto the stack
        "1: popl %0\n" // Get EIP value
        "movl %%esp, %1\n" // Get ESP value
        "popa\n\t"
        : "=m"(eip), "=m"(esp), "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx),
          "=S"(esi), "=D"(edi), "=b"(ebp)
    );

    k_print("------ CONTEXT DUMP ------", WHITE_TXT);
    k_printf("EAX: ", WHITE_TXT);
    k_print_var(eax);
    k_printf("EBX: ", WHITE_TXT);
    k_print_var(ebx);
    k_printf("ECX: ", WHITE_TXT);
    k_print_var(ecx);
    k_printf("EDX: ", WHITE_TXT);
    k_print_var(edx);
    k_printf("ESI: ", WHITE_TXT);
    k_print_var(esi);
    k_printf("EDI: ", WHITE_TXT);
    k_print_var(edi);
    k_printf("EBP: ", WHITE_TXT);
    k_print_var(ebp);
    k_printf("ESP: ", WHITE_TXT);
    k_print_var(esp);
    k_printf("EIP: ", WHITE_TXT);
    k_print_var(eip);
    k_print("------ CONTEXT DUMP END ------", WHITE_TXT);
}