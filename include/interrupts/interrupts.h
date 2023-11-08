#include "types.h"

#ifndef INTERRUTPS_H
#define INTERRUPTS_H

void load_exceptions();

/* These are all assembly functions in interrupts.asm */
extern void int00(void);
extern void int01(void);
extern void int02(void);
extern void int03(void);
extern void int04(void);
extern void int05(void);
extern void int06(void);
extern void int07(void);
extern void int08(void);
extern void int09(void);
extern void int10(void);
extern void int11(void);
extern void int12(void);
extern void int13(void);
extern void int14(void);
extern void int15(void);
extern void int16(void);
extern void int17(void);
extern void int18(void);
extern void int19(void);
extern void int32(void);

/* enables/disables software interrupts */
void interrupts(bool opt);

#endif /* INTERRUPTS_H */