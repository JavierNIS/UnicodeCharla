#ifndef __UTF16_CONVERSION__
#define __UTF16_CONVERSION__

#include "mbstate.h"

size_t 
CharLength(const charUTF16_t* src, const size_t& max);

size_t 
UTF16toUTF8(const charUTF16_t* src, charUTF8_t* dest, conversionstate_t* conver, const size_t& max);

size_t 
UTF16toUTF32(const charUTF16_t* src, charUTF32_t* dest, conversionstate_t* conver, const size_t& max);

#ifdef __linux__
size_t 
UTF16toWIDE(const charUTF16_t* src, widechar_t* dest, conversionstate_t* conver, const size_t& max);
#endif /*__linux__*/

#endif /*__UTF16_CONVERSION__*/
