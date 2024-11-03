#include <stdio.h>
#include <stdlib.h>

void die(const char *s)
{
	fprintf(stderr, "%s\n", s);
	exit(EXIT_FAILURE);
}

void strncpy_ex(char *dst, const char *src, int count, int (*cond)(int))
{
	if (dst == NULL)
		return;
	if (src == NULL) {
		*dst = '\0';
		return;
	}
	while (cond(*src) && count--)
		*dst++ = *src++;
	*dst = '\0';
}
