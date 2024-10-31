#ifndef _SYM_H
#define _SYM_H

#define MAXKEYWORDS 31

typedef struct { char *key; int value } symstruct_t;

enum kw_type {
	STRUCT,
	BREAK,
	ELSE,
	SWITCH,
	CASE,
	ENUM,
	REGISTER,
	TYPEDEF,
	EXTERN,
	RETURN,
	UNION,
	CONST,
	CONTINUE,
	FOR,
	DEFAULT,
	GOTO,
	SIZEOF,
	VOLATILE,
	DO,
	IF,
	STATIC,
	WHILE,
	U0,
	U8,
	U16,
	U32,
	U64,
	I8,
	I16,
	I32,
	I64,
};

static symstruct_t keywords[] = {
	{"u0",U0},
	{"u8",U8},
	{"u16",U16},
	{"u32",U32},
	{"u64",U64},
	{"i8",I8},
	{"i16",I16},
	{"i32",I32},
	{"i64",I64},
	{"do",DO},
	{"if",IF},
	{"else",ELSE},
	{"for",FOR},
	{"while",WHILE},
	{"break",BREAK},
	{"continue",CONTINUE},
	{"switch",SWITCH},
	{"case",CASE},
	{"return",RETURN},
	{"const",CONST},
	{"static",STATIC},
	{"volatile",VOLATILE},
	{"register",REGISTER},
	{"sizeof",SIZEOF},
	{"struct",STRUCT},
	{"enum",ENUM},
	{"register",REGISTER},
	{"typedef",TYPEDEF},
	{"enum",ENUM},
	{"goto",GOTO},
	{"extern",EXTERN},
	{"union",UNION},
};

#endif