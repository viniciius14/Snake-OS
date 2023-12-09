#ifndef UTILS_H
#define UTILS_H

// #include "debug.h"

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
#define INTERRUPT __attribute__((interrupt))

#define NULL 0

#define CAT(x, y) x##y

#define STI() __asm__ volatile("sti");
#define CLI() __asm__ volatile("cli");

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



#endif /* UTILS_H */