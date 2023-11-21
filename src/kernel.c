#include "utils.h"
#include "kernel_ops.h"
#include "interrupts.h"
#include "screen.h"
#include "timer.h"



void kernel_main(void) {
    k_print("Hello, world!\n", WHITE_TXT);

    interrupts_init();
    // k_clear();
    k_print("B2Hello, world!\n", WHITE_TXT);

    fpu_init();
    init_timer(50);
    // init_screen();


    // asm volatile("int $0x3");
    // asm volatile("int $0x4");

    // k_panic("Oh no.", "lalala", true);

    for (;;) {}
}
