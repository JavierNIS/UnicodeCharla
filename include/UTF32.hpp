#ifndef __UTF32_CONVERSION__
#define __UTF32_CONVERSION__

#include "mbstate.hpp"

std::size_t 
UTF32toUTF8(const charUTF32_t*, charUTF8_t*, conversionstate_t*, const std::size_t&);

std::size_t 
UTF32toUTF16(const charUTF32_t*, charUTF16_t*, conversionstate_t*, const std::size_t&);

std::size_t 
UTF32toWIDE(const charUTF32_t*, widechar_t*, conversionstate_t*, const std::size_t&);

#endif /*__UTF32_CONVERSION__*/
