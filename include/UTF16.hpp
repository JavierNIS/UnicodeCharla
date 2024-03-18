#ifndef __UTF16_CONVERSION__
#define __UTF16_CONVERSION__

#include "mbstate.hpp"

std::size_t 
CharLength(const charUTF16_t*);

std::size_t 
UTF16toUTF8(const charUTF16_t*, charUTF8_t*, conversionstate_t*, const std::size_t&);

std::size_t 
UTF16toUTF32(const charUTF16_t*, charUTF32_t*, conversionstate_t*, const std::size_t&);

std::size_t 
UTF16toWIDE(const charUTF16_t*, widechar_t*, conversionstate_t*, const std::size_t&);

#endif /*__UTF16_CONVERSION__*/
