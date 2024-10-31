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
	if (p && *p != '\0')
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

	unsigned base = 10;
	if (c == '0') {
		char next = lexer_peek(1);
		base = 	next == 'x' ? 16 :
				next == 'b' ? 2  : 10;
	}

	tk.value = 0;
	while (isxdigit(c)) {
		static const char *s = "0123456789ABCDEF";
		tk.value = tk.value * base + strchr(s, toupper(c)) - s;
		lexer_advance_char();
	}

	return tk;
}

struct token lexer_parse_identifier()
{
	struct token tk;
	tk.type = TK_UNDEFINED;

	if (isalpha(c) || c != '_')
		tk.type = TK_IDENTIFIER;

	/* dynamic allocation not yet supported */
	int i;
	char buffer[4096];
	for (i = 0; i < 4096; i++) {
		if (c == '\0' || (!isalpha(c) && c != '_'))
			break;
		buffer[i] = c;
		lexer_advance_char();
	}
	buffer[i] = '\0';

	/* TODO: implement symbol table */
	printf("parsed ident: '%s'\n", buffer);
	return tk;
}

struct token lexer_next_token()
{
	struct token tk;
	tk.type = TK_UNDEFINED;
	lexer_advance_whitespace();

	if (isalpha(c)) {
		tk = lexer_parse_keyword();
		if (tk.type == TK_UNDEFINED)
			tk = lexer_parse_identifier();
	} else if (isdigit(c)) {
		tk = lexer_parse_integer();
	}

	return tk;
}

void lexer_add_sources(const char *path)
{
	p = io_read_all(path);
	c = *p;
}

void lexer_clean_sources()
{
	c = 0;
	free(p);
}
