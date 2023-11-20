#include "interrupts.h"
#include "kernel_ops.h"
#include "utils.h"


void kernel_main(void) {
    k_print("Hello, world!\n", WHITE_TXT);

    interrupts_init();
    // k_clear();

    // fpu_init();
    //screen_init();


    // asm volatile("int $0x3");
    // asm volatile("int $0x4");

    // k_panic("Oh no.", "lalala", true);

    for (;;) {}
}
