#include "UTF32.hpp"

std::size_t 
UTF32toUTF8(const charUTF32_t*, charUTF8_t*, conversionstate_t*, const std::size_t&);

std::size_t 
UTF32toUTF16(const charUTF32_t*, charUTF16_t*, conversionstate_t*, const std::size_t&);

std::size_t 
UTF32toWIDE(const charUTF32_t*, widechar_t*, conversionstate_t*, const std::size_t&);
