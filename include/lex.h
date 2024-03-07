#ifndef _LEX_H
#define _LEX_H

#include <stdlib.h>

struct Lexer
{
	char *src;
	size_t len;
	size_t pos;
	char c;
};

struct Lexer *lexer_create(char *src);
void lexer_destroy(struct Lexer *self);
void lexer_advance(struct Lexer *self);
void lexer_advance_whitespace(struct Lexer *self);

struct Token *lexer_next_token(struct Lexer *self);
#endif
