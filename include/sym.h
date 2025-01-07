#ifndef _SYM_H
#define _SYM_H

#include "defs.h"

i64 symtab_add_symbol(u8 * name, u64 datatype);
i64 symtab_find_by_name(u8 * name);
u0 printf_symtab();

#endif