#ifndef PIC_H
#define PIC_H

#include "utils.h"

/* ---------------- Defines ---------------- */

#define PIC_1_CMD   0x20
#define PIC_1_DATA  0x21

#define PIC_2_CMD   0xA0
#define PIC_2_DATA  0xA1

#define NEW_IRQ_0   0x20    /* IRQ 0 - 7 will be mapped to interrupts 32 - 39 */
#define NEW_IRQ_8   0x28    /* IRQ 8 - 15 will be mapped to interrupts 40 - 47 */

#define PIC_EOI     0x20    /* End of interrupt signal */

/* ---------- Function prototypes ---------- */

/* Send end of interrupt command to signal IRQ has been handled */
void send_pic_eoi(uint8_t);

/* Disable PIC */
void disable_pic(void);

/* Set IRQ mask by setting the bit in the IMR (interrupt mask register) */
void set_irq_mask(uint8_t);

/* Clear IRQ mask by clearing the bit in the IMR (interrupt mask register) */
void clear_irq_mask(uint8_t);

/* Remap PIC to user interrupts above first 15, to not interface withe xceptions (ISRs 0-31) */
void remap_pic(void);

#endif