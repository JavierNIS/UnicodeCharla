#include "UTF8.hpp"

std::size_t 
CharLength(const charUTF8_t*);

std::size_t 
UTF8toUTF16(const charUTF8_t*, charUTF16_t*, conversionstate_t*, const std::size_t&);

std::size_t 
UTF8toUTF32(const charUTF8_t*, charUTF32_t*, conversionstate_t*, const std::size_t&);

std::size_t 
UTF8toWIDE(const charUTF8_t*, widechar_t*, conversionstate_t*, const std::size_t&);
