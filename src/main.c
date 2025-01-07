#include "util.h"
#include "lexer.h"
#include "sym.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

u0 printf_token(u64 type, u64 data, u8 * str)
{
  printf("type: %s, data: 0x%016lX, str: '%s'\n", 
      token_type_to_str(type), data, str);
}

u0 cc(u8 * path)
{
  u8  le[MAXSTR];
  u64 type, data;

  lexer_load_source(path);

  while ((type = lex(&data, le)) != TK_EOF)
    printf_token(type, data, le);
		
  /*printf_symtab();*/
}

int main(int argc, char * argv[])
{
  if (argc != 2)
    die("invalid argc");
  cc(argv[1]);
  return 0;
}