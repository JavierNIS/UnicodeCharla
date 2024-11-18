#ifndef UTF16_CONVERSION
#define UTF16_CONVERSION

#include "unicode_common.h"

mbsize_t 
CharLength16(const charUTF16_t* src, conversionInfo_t* conver);

mbsize_t 
UTF16toUTF8(const charUTF16_t* src, charUTF8_t* dest, conversionInfo_t* conver, const mbsize_t max);

mbsize_t 
UTF16toUTF32(const charUTF16_t* src, charUTF32_t* dest, conversionInfo_t* conver, const mbsize_t max);

#ifdef __linux__
mbsize_t 
UTF16toWIDE(const charUTF16_t* src, widechar_t* dest, conversionInfo_t* conver, const mbsize_t max);
#endif /*__linux__*/

#endif /*UTF16_CONVERSION*/
