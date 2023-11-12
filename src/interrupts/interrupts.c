#include "utils/types.h"
#include "interrupts/interrupts.h"
#include "interrupts/pic.h"
#include "utils/mem_ops.h"
#include "kernel/kernel_ops.h"

struct IDT_Pointer      idt_pointer;
struct IDT_Descriptor   idt_list[256];

void interrupts_init(void) {
    /* Disable interrupts */
    interrupts(false);

    /* Remap PIC IRQs to cover software interrupts 0x20-0x30 */
    remapPIC(0x20, 0x28);

    /* Mask the IRQs so they don't mess anything up */
    maskIRQ(ALL);

    /* Here we load all the interrupts and "connect" them to their handler function */
    load_exceptions();

	/* Point the IDT register to our IDT array */
    load_IDT();

    /* Enable interrupts */
    interrupts(true);
}

void load_IDT(void) {
    idt_pointer.limit = 256 * sizeof(struct IDT_Descriptor) - 1;
    idt_pointer.base = (uintptr_t) &idt_pointer;

    memset(&idt_list, 0, sizeof(struct IDT_Descriptor) * 256);

    struct IDT_Pointer *idt = &idt_pointer;

    __asm__ __volatile__("lidt (%0) ": :"p" (idt));
}

/* set descriptor number'th element settings' to be handled by handler_f */
void add_int(int number, void(*handler_f)()) {
    uint16_t selector = 0x08;
    uint16_t settings = 0;
    uint32_t offset = (uintptr_t)handler_f;

    /* get CS selector */
    __asm__ __volatile__("movw %%cs,%0" :"=g"(selector));


    settings = 0x8E00;  /* 1000111000000000 = present, ring0, int_gate */

    idt_list[number].offset_low     = (offset & 0xFFFF);
    idt_list[number].selector       = selector;
    idt_list[number].__ignored      = 0;
    idt_list[number].type           = (settings >> 8);
    idt_list[number].offset_high    = (offset >> 16);
}

void interrupts(bool opt) {
    if(opt) {
        __asm__ __volatile__("sti");
    } else {
        __asm__ __volatile__("cli");
    }
}

/* Add all Exception Interrupts */
void load_exceptions(void) {
	add_int(0,  int00);
    add_int(1,  int01);
    add_int(2,  int02);
    add_int(3,  int03);
    add_int(4,  int04);
    add_int(5,  int05);
    add_int(6,  int06);
    add_int(7,  int07);
    add_int(8,  int08);
    add_int(9,  int09);
    add_int(10, int10);
    add_int(11, int11);
    add_int(12, int12);
    add_int(13, int13);
    add_int(14, int14);
    add_int(16, int16);
    add_int(17, int17);
    add_int(18, int18);
    add_int(19, int19);
	add_int(20, 0);       /* Intel reserved interrupts from 20 - 31 */
	add_int(21, 0);
	add_int(22, 0);
	add_int(23, 0);
	add_int(24, 0);
	add_int(25, 0);
	add_int(26, 0);
	add_int(27, 0);
	add_int(28, 0);
	add_int(29, 0);
	add_int(30, 0);
	add_int(31, 0);
}

/* Exception handlers */
void int_00(void) {
	k_panic("Divide By Zero Error","#00", false);
}

void int_01(void) {
	k_panic("Debug Error","#DB", false);
}

void int_02(void) {
	k_panic("NMI Interrupt","#--", false);
}

void int_03(void) {
	k_panic("Breakpoint","#BP", false);
}

void int_04(void) {
	k_panic("Overflow","#OF", false);
}

void int_05(void) {
	k_panic("BOUND Range Exceeded","#BR", false);
}

void int_06(void) {
	k_panic("Invalid Opcode","#UD", false);
}

void int_07(void) {
	k_panic("Device Not Available","#NM", false);
}

void int_08(void) {
	k_panic("Double Fault","#DF", true);
}

void int_09(void) {
	k_panic("Coprocessor Segment Overrun", "#NA", false);
}

void int_10(void) {
	k_panic("Invalid TSS","#TS", false);
}

void int_11(void) {
	k_panic("Segment Not Present","#NP", false);
}

void int_12(void) {
	k_panic("Stack Segment Fault","#SS", false);
}

void int_13(void) {
	k_panic("Gneral Protection Fault","#GP", false);
}

void int_14(void) {
	k_panic("Page Fault","#PF", false);
}

void int_16(void) {
	k_panic("FPU Floating-Point Error","#MF", false);
}

void int_17(void) {
	k_panic("Alignment Check","#AC", false);
}

void int_18(void) {
	k_panic("Machine Check","#MC", true);
}

void int_19(void) {
	k_panic("SIMD Floating-Point","#XF", false);
}
