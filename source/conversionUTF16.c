#include "UTF16.h"
#include <stdio.h>

void
SwapEndiannessU16(charUTF16_t* src){
  charUTF16_t auxiliar = src[0];
  src[0] = src[1];
  src[1] = auxiliar;
}

mbsize_t 
CharLength16(const charUTF16_t* src, conversionInfo_t* conver){
  if(src == 0 || conver->_state == BAD)
    return 0;
  //Primero se asume que el code point no es un par subrogado de UTF-16
  //En cuyo caso, los code points validos son U+0000 a U+D7FF y U+E000 a U+FFFF 
  if(*src < 0xD800 || *src > 0xDF00) return 1; 

  /*En caso de que esta condición no se cumpla, hay que comprobar si estamos
  en big endian o en little endian. En cuyo caso lo que cambia es el orden
  de comprobación*/
  if(conver->_endianness == BIG_ENDIAN){
    //Subrogado alto, entre 0xD800 y 0xDBFF
    //El segundo debe de estar entre 0xDC00 y 0xDFFF
    if(0xD800 <= *src && 
        *src <= 0xDBFF)
      if(0xDC00 <= *(src+1) &&
          *(src+1) <= 0xDFFF) return 2; 
  }else{
    //Subrogado bajo y después alto
    if(0xDC00 <= *src &&
        *src <= 0xDFFF)
      if(0xD800 <= *(src+1) &&
          *(src+1) <= 0xDBFF) return 2;
  }
  SetError(conver, (void*)src); 
  return 0;
}

mbsize_t 
UTF16toUTF8(const charUTF16_t* src, charUTF8_t* dest, conversionInfo_t* conver, const mbsize_t max){
  if(src == 0 || dest == 0 || conver == BAD)
    return 0;
  
  mbsize_t u16_cp_size = CharLength16(src, conver);
  if(u16_cp_size > max)
    u16_cp_size = 0;
  switch(u16_cp_size){
    case 1:
      if (*src < 0x80){
        *dest = *src;
      }else if (*src < 0x800){
        dest[0] = (0xC0 | ((*src & 0x7C0) >> 6));
        dest[1] = (0x80 | (*src & 0x3F));
      }else{
        dest[0] = (0xE0 | ((*src & 0xF000) >> 12));
        dest[1] = (0x80 | ((*src & 0xFC0) >> 6));
        dest[2] = (0x80 | (*src & 0x3F));
      }
      break;
    case 2:
      {}
      charUTF16_t srcBE[2] = {src[0], src[1]};
      if(conver->_endianness == LITTLE_ENDIAN)
        SwapEndiannessU16(srcBE);
      uint8_t conversion_auxiliar = (srcBE[0] & 0x03C) + 1;
      dest[0] = (0xF0 | (conversion_auxiliar & 0x1C));
      dest[1] = (0x80 | ((conversion_auxiliar & 0x03) << 4));
      dest[1] = (dest[1] | (srcBE[0] & 0x3C));
      dest[2] = (0x80 | ((srcBE[0] & 0x3) << 4));
      dest[2] = (dest[2] | ((srcBE[1] & 0x03C0) >> 6));
      dest[3] = (0x80 | (srcBE[1] & 0x3F));
      break;
    default:
      SetError(conver, (void*)src);
  }
  return u16_cp_size;
}

mbsize_t 
UTF16toUTF32(const charUTF16_t* src, charUTF32_t* dest, conversionInfo_t* conver, const mbsize_t max){
  if(src == 0 || dest == 0 || conver->_state == BAD)
    return 0;
  mbsize_t u16_cp_size = CharLength16(src, conver);
  if(u16_cp_size > max)
    u16_cp_size = 0;
  switch (u16_cp_size) {
    case 1:
      *dest = *src;
      break;
    case 2:
      {}
      charUTF32_t destBE = 
        (((src[0] & 0x03ff) << 10) |
         (src[1] & 0x03ff)) + 0x10000;
      if(conver->_endianness == LITTLE_ENDIAN)
        SwapEndiannessU32(&destBE);
      *dest = destBE;
      }
  return u16_cp_size;
}

#ifdef __linux__
mbsize_t 
UTF16toWIDE(const charUTF16_t* src, widechar_t* dest, conversionInfo_t* conver, const mbsize_t max){
  return (UTF16toUTF32(src, dest, conver, max));
}
#endif /*__linux__*/
