#ifndef _LEXER_H
#define _LEXER_H

#include <stdio.h>
#include <stddef.h>

enum tk_type {
	TK_UNDEFINED,
	TK_KEYWORD,
	TK_IDENTIFIER,
	TK_INTEGER,
	TK_LPAREN,
	TK_RPAREN,
	TK_LBRACE,
	TK_RBRACE,
	TK_ASTERISK,
	TK_ASSIGN,
	TK_SEMI,
	TK_INCREMENT,
	TK_DECREMENT,
	TK_EOF,
};

struct token {
	enum tk_type type;
	long long value;
};

void lexer_add_sources(const char *path);
void lexer_clean_sources();
struct token lexer_next_token();

#endif
