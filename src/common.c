// common.c -- Defines some global functions.
// From JamesM's kernel development tutorials.

#include "common.h"

// Write a byte out to the specified port.
void outb(u16int port, u8int value)
{
	asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}

u8int inb(u16int port)
{
	u8int ret;
	asm volatile("inb %1, %0" : "=a" (ret) : "dN" (port));
	return ret;
}

u16int inw(u16int port)
{
	u16int ret;
	asm volatile ("inw %1, %0" : "=a" (ret) : "dN" (port));
	return ret;
}


void *memcpy(void *dst, const void *src, size_t n)
{
	int i, m;
	unsigned long  *wdst = (unsigned long*)dst;  
	unsigned long  *wsrc = (unsigned long*)src; 

	for(i = 0, m = n / sizeof(long); i < m; i++)  
		*(wdst++) = *(wsrc++);  

	for(i = 0, m = n % sizeof(long); i < m; i++)    
	{  
		*(((unsigned char*)wdst+i)) = *(((unsigned char*)wsrc)+i);
	}


	return dst;
}

void *memset(void *dst, int c, size_t n)
{
	int i, m;
	unsigned long  *wdst = dst;  
	long  cc = c + (c<<8) + (c<<16)+ (c<<24); 

	for(i = 0, m = n / sizeof(long); i < m; i++)  
		*(wdst++) = cc;                     

	for(i = 0, m = n % sizeof(long); i < m; i++) 
		*(((unsigned char*)wdst)+i) = c;

	return dst;
}


// Compare two strings. Should return -1 if 
// str1 < str2, 0 if they are equal or 1 otherwise.
int strcmp(char *str1, char *str2)
{
	char * s1 = str1, * s2 = str2;

	while(*s1 == *s2 && *s1 != 0 && *s2 != 0)
	{
		s1++;
		s2++;
	}

	if(*s1==*s2)
		return 0;
	else if (*s1 < *s2)
		return -1;
	else
		return 1;	
}

int strlen(const char * str)
{
	int len = 0;
	const char * s = str;

	while(*s++)
		len++;

	return len;
}

// Copy the NULL-terminated string src into dest, and
// return dest.
char *strcpy(char *dest, const char *src)
{
	int srclen = strlen(src);

	return memcpy(dest,src,srclen);
}

// Concatenate the NULL-terminated string src onto
// the end of dest, and return dest.
char *strcat(char *dest, const char *src)
{
	int srclen = strlen(src);
	int destlen = strlen(dest);

	memcpy(dest+destlen,src,srclen);
	return dest;
}
