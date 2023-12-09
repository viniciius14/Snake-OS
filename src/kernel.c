#include "utils.h"
#include "kernel_ops.h"
#include "idt.h"


void kernel_main(void) {
    k_print("Test");
    init_idt_32();
    for (;;) {}
}
