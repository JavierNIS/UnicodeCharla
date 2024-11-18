#ifndef UTF8_CONVERSION
#define UTF8_CONVERSION

#include "unicode_common.h"

mbsize_t 
CharLength(const charUTF8_t* src, conversionInfo_t* conver);

mbsize_t 
UTF8toUTF16(const charUTF8_t* src, charUTF16_t* dest, conversionInfo_t* conver, const mbsize_t max);

mbsize_t 
UTF8toUTF32(const charUTF8_t* src, charUTF32_t* dest, conversionInfo_t* conver, const mbsize_t max);

mbsize_t 
UTF8toWIDE(const charUTF8_t* src, widechar_t* dest, conversionInfo_t* conver, const mbsize_t max);

#endif /*UTF8_CONVERSION*/
