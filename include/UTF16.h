#ifndef __UTF16_CONVERSION__
#define __UTF16_CONVERSION__

#include "mbstate.h"

size_t 
CharLength(const charUTF16_t*, const size_t&);

size_t 
UTF16toUTF8(const charUTF16_t*, charUTF8_t*, conversionstate_t*, const size_t&);

size_t 
UTF16toUTF32(const charUTF16_t*, charUTF32_t*, conversionstate_t*, const size_t&);

#ifdef __linux__
size_t 
UTF16toWIDE(const charUTF16_t*, widechar_t*, conversionstate_t*, const size_t&);
#endif /*__linux__*/

#endif /*__UTF16_CONVERSION__*/
