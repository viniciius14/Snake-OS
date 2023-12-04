#include "kernel_ops.h"
#include "interrupts.h"
#include "timer.h"
// #include "screen.h"
extern uint32_t tick;
void kernel_main(void) {
    init_idt();
    fpu_init();
    
    init_timer(50);
    // init_screen();


    for (;;) {}
}
