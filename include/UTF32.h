#ifndef __UTF32_CONVERSION__
#define __UTF32_CONVERSION__

#include "mbstate.h"

size_t 
UTF32toUTF8(const charUTF32_t*, charUTF8_t*, conversionstate_t*, const size_t&);

size_t 
UTF32toUTF16(const charUTF32_t*, charUTF16_t*, conversionstate_t*, const size_t&);

#ifdef _WIN32
size_t 
UTF32toWIDE(const charUTF32_t*, widechar_t*, conversionstate_t*, const size_t&);
#endif /*_WIN32*/

#endif /*__UTF32_CONVERSION__*/
