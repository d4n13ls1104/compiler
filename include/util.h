#ifndef _UTIL_H
#define _UTIL_H

void die(const char *s);

/* strncpy but only chars satisfied by condition function */
void strncpy_ex(char *dst, const char *src, int count, int (*cond)(int));

#endif
