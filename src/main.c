#include "io.h"
#include "lex.h"

#include <err.h>

int main(int argc, char *argv[])
{
	if (argc != 2)
		errx(1, "usage: %s <file>\n", argv[0]);

	char *data = IO_ReadFileToEnd(argv[1]);

	struct Lexer *l = lexer_create(data);

	lexer_destroy(l);

	return 0;
}
