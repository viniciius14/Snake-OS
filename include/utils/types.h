#ifndef TYPES_H
#define TYPES_H

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

typedef uint8_t             color;

#define bool uint8_t
#define true 1
#define false 0

#define SUCCESS 1
#define FAIL 0

#endif