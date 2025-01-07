#ifndef _DEFS_H
#define _DEFS_H

#define u0  void
#define i8  char
#define i16 short
#define i32 int
#define i64 long int

#define u8 unsigned char
#define u16 unsigned short
#define u32 unsigned int
#define u64 unsigned long int

#define bool u8

#define FALSE 0
#define NULL FALSE
#define TRUE 1

#define ARRAY_SIZE(a) ((sizeof(a)/sizeof(a[0])))

#endif