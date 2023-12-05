#include "kernel_ops.h"
#include "interrupts.h"
#include "timer.h"
// #include "screen.h"
// uint32_t tick = 12;
const char *m = "HELLO";
const char *m1 = "HELLO1";
void kernel_main(void) {
    k_print("wow\n\n");
    init_idt();
    k_print("wow\n\n");
    fpu_init();
    k_print("wow\n\n");
    // registers_t reg;
    // timer_callback(reg);
    // k_print_dec(tick);

    // asm volatile("int $0x3");
    // asm volatile("int $0x4");
    // // asm volatile ("int $0x3");
    // asm volatile("sti");
    // asm("sti");
    // init_timer(50);
    // init_screen();


    for (;;) {}
}
