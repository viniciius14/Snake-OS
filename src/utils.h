#ifndef UTILS_H
#define UTILS_H

/* ---------- Defines ---------- */

#define true 1
#define false 0

#define SUCCESS 1
#define FAIL 0

#define BLACK_TXT           0x00
#define BLUE_TXT            0x01
#define GREEN_TXT           0x02
#define CYAN_TXT            0x03
#define RED_TXT             0x04
#define MAGENTA_TXT         0x05
#define BROWN_TXT           0x06
#define LIGHT_GRAY_TXT      0x07
#define DARK_GRAY_TXT       0x08
#define LIGHT_BLUE_TXT      0x09
#define LIGHT_GREEN_TXT     0x0A
#define LIGHT_CYAN_TXT      0x0B
#define LIGHT_RED_TXT       0x0C
#define LIGHT_MAGENTA_TXT   0x0D
#define YELLOW_TXT          0x0E
#define WHITE_TXT           0x0F

#define PACKED __attribute__((packed))

#define NULL 0

#define CAT(x, y) x##y

#ifdef DEBUG
#define TRACE_E(x)      void trace_enter(x);
#define TRACE_L(x)      void trace_leave(x);
#define PRINTF(x)       void debug_printf(x);
#define CTX_DMP(x)      void context_dump(x);
#define CHECKPOINT(x)   void checkpoint(x);
#else
#define TRACE_E(x)
#define TRACE_L(x)
#define PRINTF(x)
#define CTX_DMP(x)
#define CHECKPOINT(x)
#endif /* DEBUG */



/* IRQ macros */
#define ALL             0xFF
#define TIMER           0x00
#define KEYBOARD        0x01
#define CASCADE         0x02
#define COM2_4          0x03
#define COM1_3          0x04
#define LPT             0x05
#define FLOPPY          0x06
#define FREE7           0x07
#define CLOCK           0x08
#define FREE9           0x09
#define FREE10          0x10
#define FREE11          0x11
#define PS2MOUSE        0x12
#define COPROC          0x13
#define IDE_1           0x14
#define IDE_2           0x15

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

/* ---------- Typedef's ---------- */

typedef unsigned char       uint8_t;
typedef unsigned short int  uint16_t;
typedef unsigned int        uint32_t;
typedef unsigned long int   uint64_t;

typedef signed char         int8_t;
typedef short int           int16_t;
typedef int                 int32_t;
typedef long int            int64_t;

typedef uint32_t            uintptr_t;

typedef uint64_t            size_t;

typedef uint8_t             bool;

typedef char                color;


/* ---------- Function prototypes ---------- */

void kernel_main(void);

/* Outputs a uint8_t to the specified hardware port */
void outportb(uint32_t port,uint8_t value);

/* Outputs a word to a port */
void outportw(uint32_t port,uint32_t value);

/* gets a uint8_t from a port */
uint8_t inportb(uint32_t port);

uint16_t inportw(uint32_t port);

void trace_enter(void);
void trace_leave(void);
void context_dump(void);
void checkpoint(void);


#endif /* UTILS_H */