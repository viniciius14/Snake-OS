#include "types.h"
#include "interrupts.h"
#include "pic.h"

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

    /* Add a customized interrupt */
    // AddInt(48, int32, 0);

	/* Point the IDT register to our IDT array */
    load_IDT();

    /* Enable interrupts */
    interrupts(true);
}

void load_IDT(void) {
    idt_pointer.limit = 256 * sizeof(struct IDT_Descriptor) - 1;
    idt_pointer.base = (uintptr_t) &idt_pointer;

    memset(&idt_list[0], 0, sizeof(struct IDT_Descriptor) * 256);

    struct IDT_Pointer *idt = &idt_pointer;

    asm volatile("lidt (%0) ": :"p" (idt));
}

/* set descriptor number'th elements settings' to dpl and to be handled by handler_f */
void add_int(int number, void(*handler_f)(), uint32_t dpl) {
    uint16_t selector = 0x08;
    uint16_t settings = 0;
    uint32_t offset = (uintptr_t)handler_f;

    /* get CS selector */
    asm volatile("movw %%cs,%0" :"=g"(selector));

    switch(dpl) {
        case 0:
            settings = 0x8E00;  /* 1000111000000000 = present, ring0, int_gate */
            break;
        default:
            settings = 0xEE00;  /* 1110111000000000 = present, ring3, int_gate */
            break;
    }

    idt_list[number].offset_low     = (offset & 0xFFFF);
    idt_list[number].selector       = selector;
    idt_list[number].__ignored      = 0;
    idt_list[number].type           = (settings >> 8);
    idt_list[number].offset_high    = (offset >> 16);
}

void interrupts(bool opt) {
    if(opt) {
        asm("sti");
    } else {
        asm("cli");
    }
}

/* Add all Exception Interrupts */
void load_exceptions(void) {
	add_int(0,  int00, 0);
    add_int(1,  int01, 0);
    add_int(2,  int02, 0);
    add_int(3,  int03, 0);
    add_int(4,  int04, 0);
    add_int(5,  int05, 0);
    add_int(6,  int06, 0);
    add_int(7,  int07, 0);
    add_int(8,  int08, 0);
    add_int(9,  int09, 0);
    add_int(10, int10, 0);
    add_int(11, int11, 0);
    add_int(12, int12, 0);
    add_int(13, int13, 0);
    add_int(14, int14, 0);
    add_int(16, int16, 0);
    add_int(17, int17, 0);
    add_int(18, int18, 0);
    add_int(19, int19, 0);
	add_int(20, 0,     0);       /* Intel reserved interrupts from 20 - 31 */
	add_int(21, 0,     0);
	add_int(22, 0,     0);
	add_int(23, 0,     0);
	add_int(24, 0,     0);
	add_int(25, 0,     0);
	add_int(26, 0,     0);
	add_int(27, 0,     0);
	add_int(28, 0,     0);
	add_int(29, 0,     0);
	add_int(30, 0,     0);
	add_int(31, 0,     0);
}

/* Exception handlers */
void int_00(void) {
	panic("Divide By Zero Error","#00", false);
}

void int_01(void) {
	panic("Debug Error","#DB", false);
}

void int_02(void) {
	panic("NMI Interrupt","#--", false);
}

void int_03(void) {
	panic("Breakpoint","#BP", false);
}

void int_04(void) {
	panic("Overflow","#OF", false);
}

void int_05(void) {
	panic("BOUND Range Exceeded","#BR", false);
}

void int_06(void) {
	panic("Invalid Opcode","#UD", false);
}

void int_07(void) {
	panic("Device Not Available","#NM", false);
}

void int_08(void) {
	panic("Double Fault","#DF", true);
}

void int_09(void) {
	panic("Coprocessor Segment Overrun", "#NA", false);
}

void int_10(void) {
	panic("Invalid TSS","#TS", false);
}

void int_11(void) {
	panic("Segment Not Present","#NP", false);
}

void int_12(void) {
	panic("Stack Segment Fault","#SS", false);
}

void int_13(void) {
	panic("Gneral Protection Fault","#GP", false);
}

void int_14(void) {
	panic("Page Fault","#PF", false);
}

void int_16(void) {
	panic("FPU Floating-Point Error","#MF", false);
}

void int_17(void) {
	panic("Alignment Check","#AC", false);
}

void int_18(void) {
	panic("Machine Check","#MC", true);
}

void int_19(void) {
	panic("SIMD Floating-Point","#XF", false);
}
