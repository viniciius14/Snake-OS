#ifndef UTILS_H
#define UTILS_H

// #include "debug.h"

/* ---------- Defines ---------- */

#define true                1
#define false               0

#define SUCCESS             1
#define FAIL                0

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

#define PACKED              __attribute__((packed))
#define INTERRUPT           __attribute__((interrupt))

#define NULL                0

#define CAT(x, y)           x##y

#define STI()               __asm__ __volatile__("sti")
#define CLI()               __asm__ __volatile__("cli")

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

/* First C function that's ran */
void kernel_main(void);

/* Sets n bytes of memory to value starting at address dst */
void  memset(void *dst, uint8_t value, size_t n);

/* Copies n bytes of memory from src to dst */
void  *memcpy(void *dst, const void *src, size_t n);

/* Moves n bytes from src to dst */
void  *memmove(void *dst, const void *src, size_t n);

/* Outputs a byte to the specified hardware port */
void outb(uint32_t, uint8_t);

/* Outputs a word to the specified hardware port */
void outw(uint32_t, uint32_t);

/* Gets a byte from the specified hardware port */
uint8_t inb(uint32_t);

/* Gets a word from to the specified hardware port */
uint16_t inw(uint32_t);

/* Wait 1 I/O cycle for I/O operation to complete */
void io_wait(void);

#endif /* UTILS_H */