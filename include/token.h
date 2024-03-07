#ifndef _NODE_H
#define _NODE_H

enum TokenType
{
	TOKEN_INT,
	TOKEN_LPAREN,
	TOKEN_RPAREN,
	TOKEN_ADD,
	TOKEN_SUB,
	TOKEN_MUL,
	TOKEN_DIV,
	TOKEN_EOF,
};

struct Token
{
	char *literal;
	enum TokenType type;
	struct Token *left;
	struct Token *right;
	int constant;
};

struct Token *token_create(char *literal, enum TokenType type);
void token_destroy(struct Token *self);
char *token_tostr(struct Token *self);

#endif
