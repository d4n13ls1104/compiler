#include <stdio.h>
#include <stdlib.h>
#include <err.h>

static size_t fsize(FILE *fp)
{
	fseek(fp, 0, SEEK_END);
	size_t size = ftell(fp);
	rewind(fp);
	return size;
}

char *IO_ReadFileToEnd(const char *path)
{
	FILE *fp = fopen(path, "rb");
	if (fp == NULL)
		return NULL;
	size_t size = fsize(fp);

	char *ret = calloc(size + 1, sizeof(char));
	if (ret == NULL)
		return NULL;

	size_t read = fread(ret, sizeof(char), size, fp);
	if (read < size) {
		free(ret);
		fclose(fp);
		return NULL;
	}
	fclose(fp);
	return ret;
}
