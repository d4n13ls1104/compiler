#include "lexer.h"
#include "io.h"
#include "sym.h"

#include <string.h>
#include <stdlib.h>
#include <ctype.h>

static int c;
static char *p;

void lexer_advance_char()
{
	if (p && *p)
		c = *p++;
}

void lexer_advance_many(int i)
{
	while (i--)
		lexer_advance_char();
}

void lexer_advance_whitespace()
{
	while (isspace(c))
		lexer_advance_char();
}

void lexer_advance_line()
{
	while (c && c != '\n')
		lexer_advance_char();
}

char lexer_peek(int i)
{
	if (c == '\0')
		return c;
	return p[i];
}

struct token lexer_parse_keyword()
{
	struct token tk;
	tk.type = TK_UNDEFINED;

	for (int i = 0; i < MAXKEYWORDS; i++) {
		symstruct_t sym = keywords[i];
		if (strstr(p, sym.key) == p) {
			tk.type = TK_KEYWORD;
			tk.value = sym.value;
			lexer_advance_many(strlen(sym.key));
			break;
		}
	}

	return tk;
}

struct token lexer_parse_integer()
{
	struct token tk;
	tk.type = TK_INTEGER;

	int sign = c == '-' ? -1 : +1;
	if (sign < 0)
		lexer_advance_char();

	int base = 10;
	if (c == '0') {
		char next = lexer_peek(1);
		base = 	next == 'x' ? 16 :
				next == 'b' ? 2  : 0;
		if (base)
			lexer_advance_many(2);
	}

	tk.value = 0;
	while (isxdigit(c)) {
		static const char *s = "0123456789ABCDEF";
		tk.value = tk.value * base + strchr(s, toupper(c)) - s;
		lexer_advance_char();
	}
	tk.value *= sign;

	return tk;
}

/* note: maybe add anonymous functions at some point */
int ident_cond(int c)
{
	return isalpha(c) || c == '_';
}

struct token lexer_parse_identifier()
{
	struct token tk;
	tk.type = TK_UNDEFINED;

	if (!ident_cond())
		return tk;

	tk.type = TK_IDENTIFIER;

	/* dynamic allocation not yet supported */
	#define IDENT_MAXLEN 4096
	char buffer[IDENT_MAXLEN];
	strncpy_ex(buffer, p, IDENT_MAXLEN, &ident_cond);
	lexer_advance_many(strlen(buffer));

	/* TODO: implement symbol table */
	printf("IDENTIFIER: '%s'\n", buffer);
	return tk;
}

struct token lexer_next_token()
{
	struct token tk;
	tk.type = TK_UNDEFINED;
	lexer_advance_whitespace();

	if (c == '\0') {
		tk.type = TK_EOF;
	} else if (isalpha(c)) {
		tk = lexer_parse_keyword();
		if (tk.type == TK_UNDEFINED)
			tk = lexer_parse_identifier();
	} else if (isdigit(c) || c == '-') {
		tk = lexer_parse_integer();
	}

	return tk;
}

void lexer_add_sources(const char *path)
{
	p = io_read_all(path);
	lexer_advance_char();
}

void lexer_clean_sources()
{
	c = 0;
	free(p);
}
