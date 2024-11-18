#ifndef UNICODE_COMMON
#define UNICODE_COMMON

#include "mbstate.h"
#include "codepoints.h"

void
SwapEndiannessU32(charUTF32_t* src);

void
SwapEndiannessU16(charUTF16_t* src);

#endif /*UNICODE_COMMON*/
