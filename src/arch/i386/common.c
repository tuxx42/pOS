#include <common.h>

int strcmp(const char *s1, const char *s2)
{
	char *str1 = (char *)s1;
	char *str2 = (char *)s2;
	while (*str1 && *str2 && (*str1++ == *str2++))
		;

	if (*str1 == '\0' && *str2 == '\0')
		return 0;

	return (*str1 == '\0') ? -1 : 1;
}

char *strcpy(char *dest, const char *src)
{
	char *dbp = dest;
	const char *sbp = src;

	while (*sbp)
		*dbp++ = *sbp++;

	*dbp = '\0';

	return dest;
}

int strlen(const char *src)
{
	const char *sbp = src;

	while (*sbp++)
		;

	return (int)(sbp-src);
}

void * memset(void *dest, const char byte, unsigned int n)
{
	unsigned char *dbp = (unsigned char *)dest;

	if ((dest != (void *)0) && (n > 0))
		while (n--)
			*dbp++ = byte;

	return dest;
}

void * memcpy(void *dest, const void *src, unsigned int n)
{
	unsigned char *dbp = (unsigned char *)dest;
	unsigned char *sbp = (unsigned char *)src;

	if ((dest != (void *)0) && (src != (void *)0) && (n > 0))
		while (n--)
			*dbp++ = *sbp++;
	return dest;
}

/* Convert the integer D to a string and save the string in BUF. If
   BASE is equal to 'd', interpret that D is decimal, and if BASE is
   equal to 'x', interpret that D is hexadecimal. */
void itoa (char *buf, const int base, const int d)
{
	char *p = buf;
	char *p1, *p2;
	unsigned long ud = d;
	int divisor = 10;

	/* If %d is specified and D is minus, put `-' in the head. */
	if (base == 'd' && d < 0) {
		*p++ = '-';
		buf++;
		ud = -d;
	}
	else if (base == 'x')
		divisor = 16;

	/* Divide UD by DIVISOR until UD == 0. */
	do {
		int remainder = ud % divisor;

		*p++ = (remainder < 10) ? remainder + '0' : remainder + 'a' - 10;
	} while (ud /= divisor);

	/* Terminate BUF. */
	*p = 0;

	/* Reverse BUF. */
	p1 = buf;
	p2 = p - 1;
	while (p1 < p2) {
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}
}
