#ifndef PIC_H
#define PIC_H

#include "utils.h"

void remapPIC(uint8_t pic1, uint8_t pic2);  //remap PIC
void maskIRQ(uint8_t irq);          //PIC irq masking
void unmaskIRQ(uint8_t irq);        //PIC irq unmasking

#endif /* PIC_H */