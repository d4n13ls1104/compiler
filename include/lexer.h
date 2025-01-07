#ifndef _LEXER_H_
#define _LEXER_H_

#include "defs.h"

/* hard limit for any lexeme */
#define MAXSTR 1024

#define TK_EOF        0
#define TK_UNKNOWN    1
#define TK_KEYWORD    2
#define TK_INTEGER    3
#define TK_OPERATOR   4
#define TK_SEPARATOR  5
#define TK_IDENTIFIER 6

#define KW_U0 0
#define KW_U8 1
#define KW_U16 2
#define KW_U32 3
#define KW_U64 4
#define KW_I8 5
#define KW_I16 6
#define KW_I32 7
#define KW_I64 8
#define KW_IF 9
#define KW_DO 10
#define KW_FOR 11
#define KW_GOTO 12
#define KW_ELSE 13
#define KW_CASE 14
#define KW_WHILE 15
#define KW_BREAK 16
#define KW_CONST 17
#define KW_UNION 18
#define KW_STRUCT 19
#define KW_SWITCH 20
#define KW_RETURN 21
#define KW_STATIC 22
#define KW_EXTERN 23
#define KW_CONTINUE 24
#define KW_REGISTER 25
#define KW_VOLATILE 26

static const u8 * kw[] = {
  "u0","u8","u16","u32","u64",
  "i8","i16","i32","i64","if","do",
  "for","goto","else","case","while",
  "break","const","union","struct",
  "switch","return","static","extern",
  "continue","register","volatile"
};

#define MAXKW ((ARRAY_SIZE(kw)))

u0  lexer_load_source(u8 * path);
u64 lex(u64 * data, u8 le[MAXSTR]);

#endif