#include "util.h"
#include "lexer.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>

static u8 c;
static u8 * src;

u0 lexer_load_source(u8 * path)
{
  src = readfile(path);
  c = *src;
}

/* harden later */
u8 peek(i64 i)
{
  return src[i];
}

u0 seek(i64 i)
{
  src += i;
  c = *src;
}

u0 seekwsp()
{
  while (isspace(c))
    seek(1);
}

i64 identifier(u8 s[MAXSTR])
{
  i64 i;

  i = 0;
  while (i < MAXSTR && (isalnum(c) || c == '_')) {
    s[i++] = c;
    seek(1);
  }
  s[i] = '\0';

  return i;
}

u64 base()
{
  u64 i;

  i = 10;
  if (c == '0') {
    if (peek(1) == 'x')
      i = 16;
    else if (peek(1) == 'b')
      i = 2;
    if (i != 10)
      seek(2);
    return i;
  }

  return i;
}

u64 integer()
{
  u64 i;
  u64 xx;

  i = 0;
  xx = base();
  while (isxdigit(c)) {
    static i8 * s = "0123456789ABCDEF";
    i = i * xx + strchr(s, toupper(c)) - s;
    seek(1);
  }

  return i;
}

u64 keyword()
{
  u64  i;
  u64  len;
  u8 * str;

  for (i = 0; i < MAXKW; i++) {
    str = kw[i];
    len = strlen(str);
    if (!strncmp(src, str, len)) {
      seek(len);
      return i;
    }
  }

  return -1;
}

u64 lex(u64 * i, u8 s[MAXSTR])
{
  seekwsp();

  *i = c;
  s[0] = c;
  s[1] = 0;

  switch (tolower(c)) {
  case '\0':
    return TK_EOF;
  case '+':
  case '-':
  case '*':
  case '/':
  case '%':
  case '=':
  case '<':
  case '>':
  case '!':
    seek(1);
    return TK_OPERATOR;
  case ';':
  case ',':
  case '(':
  case ')':
  case '{':
  case '}':
  case '[':
  case ']':
  case '\'':
  case '\"':
    seek(1);
    return TK_SEPARATOR;
  case '0':
  case '1':
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
  case '7':
  case '8':
  case '9':
    *i = integer();
    return TK_INTEGER;
  case '_':
  case 'a':
  case 'b':
  case 'c':
  case 'd':
  case 'e':
  case 'f':
  case 'g':
  case 'h':
  case 'i':
  case 'j':
  case 'k':
  case 'l':
  case 'm':
  case 'n':
  case 'o':
  case 'p':
  case 'q':
  case 'r':
  case 's':
  case 't':
  case 'u':
  case 'v':
  case 'w':
  case 'x':
  case 'y':
  case 'z':
    *i = keyword();
    if (*i < MAXKW)
      return TK_KEYWORD;
    else {
      *i = identifier(s);
      return TK_IDENTIFIER;
    }
	break;

  default:
    return TK_UNKNOWN;
  }
}