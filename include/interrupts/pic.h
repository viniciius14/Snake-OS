#ifndef PIC_H
#define PIC_H

#include "utils/types.h"


/* IRQ macros */
#define ALL             0xFF
#define TIMER           0
#define KEYBOARD        1
#define CASCADE         2
#define COM2_4          3
#define COM1_3          4
#define LPT             5
#define FLOPPY          6
#define FREE7           7
#define CLOCK           8
#define FREE9           9
#define FREE10          10
#define FREE11          11
#define PS2MOUSE        12
#define COPROC          13
#define IDE_1           14
#define IDE_2           15

/* PIC macros Master = PIC chip 1, Slave = PIC chip 2 */
#define MASTER          0x20
#define MASTERDATA      0x21
#define SLAVE           0xA0
#define SLAVEDATA       0xA1
#define EOI             0x20

#define ICW1_INIT       0x10    /* required for PIC initialisation */
#define ICW1_EDGE       0x08    /* edge triggered IRQs */
#define ICW1_SINGLE     0x02    /* only MASTER (not cascaded) */
#define	ICW1_ICW4       0x01    /* there IS an ICW4 control word */
#define ICW4_SFNM       0x10    /* Special Fully Nested Mode */
#define ICW4_BUFFER     0x08    /* Buffered Mode */
#define ICW4_MASTER     0x04    /* this is the Master PIC */
#define ICW4_AEOI       0x02    /* Auto EOI */
#define ICW4_8086       0x01    /* 80/86 Mode */

void remapPIC(int pic1, int pic2);      //remap PIC
void maskIRQ(uint8_t irq);                 //PIC irq masking
void unmaskIRQ(uint8_t irq);               //PIC irq unmasking

#endif /* PIC_H */