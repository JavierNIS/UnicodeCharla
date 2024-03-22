#include "UTF32.h"

size_t 
UTF32toUTF8(const charUTF32_t* src, charUTF8_t* dest, conversionstate_t* conver, const size_t& max);

size_t 
UTF32toUTF16(const charUTF32_t* src, charUTF16_t* dest, conversionstate_t* conver, const size_t& max);

#ifdef _WIN32
size_t 
UTF32toWIDE(const charUTF32_t*, widechar_t*, conversionstate_t*, const size_t&);
#endif /*_WIN32*/
