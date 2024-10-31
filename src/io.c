#include <stdio.h>
#include <stdlib.h>

size_t flen(FILE *fp)
{
	fseek(fp, 0, SEEK_END);
	size_t sz = ftell(fp);
	rewind(fp);
	return sz;
}

char *io_read_all(const char *file_path)
{
	FILE *fp = fopen(file_path, "rb");
	if (fp == NULL)
		return NULL;

	size_t  file_len = flen(fp);
	char   *ret = malloc(file_len + 1);
	size_t 	bytes_read = fread(ret, sizeof(char), file_len, fp);

	if (bytes_read != file_len) {
		free(ret);
		ret = NULL;
	}

	fclose(fp);
	return ret;
}