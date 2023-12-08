#include "idt.h"
#include "kernel_ops.h"


void kernel_main(void) {
    k_print("Ran init_idt()\n");

    init_idt();
    k_print("Ran init_idt()\n");
    // init_isr();
    k_print("Ran init_isr()\n");
    // init_fpu();
    k_print("Ran init_fpu()\n");

    // init_timer(363);
    k_print("Ran init_timer()\n");

    // init_screen();


    for (;;) {}
}
