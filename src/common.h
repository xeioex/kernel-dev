// common.h -- Defines typedefs and some global functions.
// From JamesM's kernel development tutorials.

#ifndef COMMON_H
#define COMMON_H

// Some nice typedefs, to standardise sizes across platforms.
// These typedefs are written for 32-bit X86.
typedef unsigned int   u32int;
typedef          int   s32int;
typedef unsigned short u16int;
typedef          short s16int;
typedef unsigned char  u8int;
typedef          char  s8int;
typedef s32int size_t;

void outb(u16int port, u8int value);
u8int inb(u16int port);
u16int inw(u16int port);

void *memset(void *dst, int c, size_t n);
void *memcpy(void *dst, const void *src, size_t n);

// Compare two strings. Should return -1 if 
// str1 < str2, 0 if they are equal or 1 otherwise.
int strcmp(char *str1, char *str2);

int strlen(const char * str);

// Copy the NULL-terminated string src into dest, and
// return dest.
char *strcpy(char *dest, const char *src);

// Concatenate the NULL-terminated string src onto
// the end of dest, and return dest.
char *strcat(char *dest, const char *src);

#endif
