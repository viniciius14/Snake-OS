#ifndef PIC_H
#define PIC_H

#include "utils.h"

/* PIC macros Master = PIC chip 1, Slave = PIC chip 2 */
#define MASTER          0x20
#define MASTERDATA      0x21
#define SLAVE           0xA0
#define SLAVEDATA       0xA1
#define EOI             0x20

void remapPIC(uint8_t pic1, uint8_t pic2);  //remap PIC
void maskIRQ(uint8_t irq);          //PIC irq masking
void unmaskIRQ(uint8_t irq);        //PIC irq unmasking

#endif /* PIC_H */