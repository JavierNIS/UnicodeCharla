#ifndef __UTF8_CONVERSION__
#define __UTF8_CONVERSION__

#include "mbstate.h"

size_t 
CharLength(const charUTF8_t*, const size_t&);

size_t 
UTF8toUTF16(const charUTF8_t*, charUTF16_t*, conversionstate_t*, const size_t&);

size_t 
UTF8toUTF32(const charUTF8_t*, charUTF32_t*, conversionstate_t*, const size_t&);

size_t 
UTF8toWIDE(const charUTF8_t*, widechar_t*, conversionstate_t*, const size_t&);

#endif /*__UTF8_CONVERSION__*/
