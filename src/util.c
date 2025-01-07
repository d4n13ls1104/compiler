#include "util.h"
#include "lexer.h"

#include <stdio.h>
#include <stdlib.h>

u0 die(u8 * s)
{
  fprintf(stderr, "%s\n", s);
  exit(EXIT_FAILURE);
}

u64 fsize(FILE * fp)
{
  u64 i;
  fseek(fp, 0, SEEK_END);
  i = ftell(fp);
  rewind(fp);
  return i;
}

u8 * readfile(u8 * path)
{
  FILE * fp;
  u8   * data;
  u64    size;

  fp = fopen(path, "rb");
  size = fsize(fp);
  data = malloc(size);
  fread(data, 1, size, fp);
  fclose(fp);
  return data;
}

u8 * token_type_to_str(u64 i)
{
  switch (i) {
  case TK_EOF:
    return "EOF";
  case TK_IDENTIFIER:
    return "IDENTIFIER";
  case TK_KEYWORD:
    return "KEYWORD";
  case TK_INTEGER:
    return "INTEGER";
  case TK_OPERATOR:
    return "OPERATOR";
  case TK_SEPARATOR:
    return "SEPARATOR";
  case TK_UNKNOWN:
    return "UNKNOWN";
  }
}

bool kw_is_datatype(u64 i)
{
  switch (i) {
  case KW_U0:
  case KW_U8:
  case KW_U16:
  case KW_U32:
  case KW_U64:
  case KW_I64:
  case KW_I32:
  case KW_I16:
  case KW_I8:
    return TRUE;
  default:
    return FALSE;
  }
}