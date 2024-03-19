#include "UTF16.hpp"

std::size_t 
CharLength(const charUTF16_t* src, std::size_t max);

std::size_t 
UTF16toUTF8(const charUTF16_t*, charUTF8_t*, conversionstate_t*, const std::size_t&);

std::size_t 
UTF16toUTF32(const charUTF16_t*, charUTF32_t*, conversionstate_t*, const std::size_t&);

std::size_t 
UTF16toWIDE(const charUTF16_t*, widechar_t*, conversionstate_t*, const std::size_t&);
