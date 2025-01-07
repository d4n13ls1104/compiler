#include "sym.h"
#include "lexer.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXSYM 64

static u64 sym_top = 0;
static u64 sym_value[MAXSYM];
static u64 sym_address[MAXSYM];
static u64 sym_datatype[MAXSYM];
static u8  sym_name[MAXSYM][MAXSTR];

static u64 data_segment = 0x2000;

i64 symtab_add_symbol(u8 * name, u64 dt)
{
  strcpy(sym_name[sym_top], name);
  sym_datatype[sym_top] = dt;
  sym_address[sym_top] = data_segment;
  data_segment += atoi(&kw[dt][1]) / 8;
  sym_top = sym_top + 1;
}

i64 symtab_find_by_name(u8 * name)
{
  i64 i;

  for (i = 0; i < MAXSYM; i = i + 1)
    if (!strcmp(name, sym_name[i]))
      return i;

  return -1;
}

u0 printf_symtab()
{
  u64 i;

  printf("SYMBOLS COLLECTED:\n");
  
  for (i = 0; i < MAXSYM; i++) {
    if (sym_name[i][0] == '\0')
      break;

    printf("addr: 0x%016lX, type: %s, name: %s\n",
            sym_address[i], kw[sym_datatype[i]], sym_name[i]);
  }
}