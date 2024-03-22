#ifndef __UTF8_CONVERSION__
#define __UTF8_CONVERSION__

#include "mbstate.h"

size_t 
CharLength(const charUTF8_t* src, const size_t& max);

size_t 
UTF8toUTF16(const charUTF8_t* src, charUTF16_t* dest, conversionstate_t* conver, const size_t& max);

size_t 
UTF8toUTF32(const charUTF8_t* src, charUTF32_t* dest, conversionstate_t* conver, const size_t& max);

size_t 
UTF8toWIDE(const charUTF8_t* src, widechar_t* dest, conversionstate_t* conver, const size_t& max);

#endif /*__UTF8_CONVERSION__*/
