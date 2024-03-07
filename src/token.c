#include "token.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Token *token_create(char *literal, enum TokenType type)
{
	struct Token *self = malloc(sizeof(struct Token));
	if (self == NULL)
		return NULL;

	if (type == TOKEN_INT)
		self->constant = atol(literal);

	self->type = type;
	self->literal = literal;
	return self;
}

void token_destroy(struct Token *self)
{
	if (self == NULL)
		return;
	free(self->literal);
	free(self);
}

static char *token_typestr(enum TokenType type)
{
	switch (type) {
	case TOKEN_INT:
		return "TOKEN_INT";
	case TOKEN_LPAREN:
		return "TOKEN_LPAREN";
	case TOKEN_RPAREN:
		return "TOKEN_RPAREN";
	case TOKEN_ADD:
		return "TOKEN_ADD";
	case TOKEN_SUB:
		return "TOKEN_SUB";
	case TOKEN_MUL:
		return "TOKEN_MUL";
	case TOKEN_DIV:
		return "TOKEN_DIV";
	case TOKEN_EOF:
		return "TOKEN_EOF";
	default:
		return "TOKEN_UNKNOWN";
	}
}

char *token_tostr(struct Token *self)
{
	const char *typestr = token_typestr(self->type);
	const char *template = "<type=%s serial={%d} literal='%s'>\n";

	char *str = calloc(strlen(typestr) + strlen(template) + 8, sizeof(char));
	sprintf(str, template, typestr, self->type, self->literal);
	return str;
}
