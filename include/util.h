#ifndef _UTIL_H
#define _UTIL_H

#include "defs.h"

bool kw_is_datatype(u64 i);
u8 * token_type_to_str(u64 type);

u8 * readfile(u8 * path);

u0 die(u8 * s);

#endif