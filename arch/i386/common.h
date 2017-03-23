#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>

int strcmp(const char *s1, const char *s2);
char *strcpy(char *dest, const char *src);
int strlen(const char *src);

void * memset(void *dest, const char byte, unsigned int n);
void * memcpy(void *dest, const void *src, unsigned int n);

void itoa (char *buf, const int base, const int d);

#endif
