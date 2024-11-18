#ifndef UTF32_CONVERSION
#define UTF32_CONVERSION

#include "unicode_common.h"

mbsize_t
UTF32mbLength(const charUTF32_t* src);

mbsize_t
UTF32bytesToUTF16(const charUTF32_t* src);

mbsize_t 
UTF32toUTF8(const charUTF32_t* src, charUTF8_t* dest, conversionInfo_t* conver, const mbsize_t max);

mbsize_t 
UTF32toUTF16(const charUTF32_t* src, charUTF16_t* dest, conversionInfo_t* conver, const mbsize_t max);

#ifdef _WIN32
mbsize_t 
UTF32toWIDE(const charUTF32_t*, widechar_t*, conversionInfo_t*, const mbsize_t&);
#endif /*_WIN32*/

#endif /*UTF32_CONVERSION*/
