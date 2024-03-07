#include "lex.h"
#include "token.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <err.h>

struct Lexer *lexer_create(char *src)
{
	struct Lexer *self = malloc(sizeof(struct Lexer));
	if (self == NULL)
		errx(1, "LEX_Init: failed to initialize lexer");

	self->src = src;
	self->len = strlen(src);
	self->pos = 0;
	self->c = self->src[self->pos];
	return self;
}

void lexer_destroy(struct Lexer *self)
{
	if (self == NULL)
		return;
	free(self->src);
	free(self);
}

void lexer_advance(struct Lexer *self)
{
	if ((self->pos < self->len) && self->c != '\0')
		self->c = self->src[++self->pos];
}

void lexer_advance_whitespace(struct Lexer *self)
{
	while (self->c == ' ' || self->c == '\t' || self->c == '\r' || self->c == '\n')
		lexer_advance(self);
}

struct Token *lexer_advance_with(struct Lexer *self, struct Token *t)
{
	lexer_advance(self);
	return t;
}

struct Token *lexer_advance_current(struct Lexer *self, enum TokenType type)
{
	char *literal = malloc(2);
	if (literal == NULL)
		return NULL;

	literal[0] = self->c;
	literal[1] = '\0';
	lexer_advance(self);
	struct Token *ret = token_create(literal, type);
	return ret;
}

struct Token *lexer_parse_int(struct Lexer *self)
{
	char *literal = calloc(2, sizeof(char));
	if (literal == NULL)
		return NULL;

	while (isdigit(self->c)) {
		literal = realloc(literal, (strlen(literal) + 2) * sizeof(char));
		strcat(literal, (char[]){self->c, 0});
		lexer_advance(self);
	}
	return token_create(literal, TOKEN_INT);
}

struct Token *lexer_next_token(struct Lexer *self)
{
	while (self->c != '\0') {
		lexer_advance_whitespace(self);

		if (isdigit(self->c))
			return lexer_advance_with(self, lexer_parse_int(self));

		switch (self->c) {
			case '+':
				return lexer_advance_current(self, TOKEN_ADD);
			case '-':
				return lexer_advance_current(self, TOKEN_SUB);
			case '*':
				return lexer_advance_current(self, TOKEN_MUL);
			case '/':
				return lexer_advance_current(self, TOKEN_DIV);
			default:
				fprintf(stderr, "unexpected char: %c\n", self->c);
		}
	}
	return token_create(0, TOKEN_EOF);
}
