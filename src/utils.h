#ifndef UTILS_H
#define UTILS_H

/* ---------- Defines ---------- */

#define true 1
#define false 0

#define SUCCESS 1
#define FAIL 0

#define RED_TXT     0x04
#define WHITE_TXT   0x07
#define BLUE_TXT    0x09

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