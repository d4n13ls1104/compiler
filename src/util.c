#include <stdio.h>
#include <stdlib.h>

void die(const char *s)
{
	fprintf(stderr, "%s\n", s);
	exit(EXIT_FAILURE);
}
