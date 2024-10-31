#include "lexer.h"
#include "util.h"
#include "io.h"

#include <stdio.h>
#include <stdlib.h>

void compile(const char *path)
{
	lexer_add_sources(path);

	struct token tk;
	while ((tk = lexer_next_token()).type != TK_EOF)
		;

	lexer_clean_sources();
}

int main(int argc, char *argv[])
{
	if (argc != 2)
		die("invalid argc");

	compile(argv[1]);
	return 0;
}