#include "UTF16.h"
#include "mbstate.h"
#include <stdint.h>
#include <stdlib.h>

mbsize_t 
CharLength16(const charUTF16_t* src, conversionInfo_t* conver){
  if(src == 0 || conver->_state == BAD)
    return 0;
  //Primero se asume que el code point no es un par subrogado de UTF-16
  //En cuyo caso, los code points validos son U+0000 a U+D7FF y U+E000 a U+FFFF 
  if(*src < 0xD800 || *src > 0xE000) return 1; 

  /*En caso de que esta condición no se cumpla, hay que comprobar si estamos
  en big endian o en little endian. En cuyo caso lo que cambia es el orden
  de comprobación*/
  if(conver->_endianness == BIG_ENDIAN){
    //Subrogado alto, entre 0xD800 y 0xDBFF
    //El segundo debe de estar entre 0xDC00 y 0xDFFF
    if(0xD801 <= *src && 
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
  conver->_state = BAD;
  return 0;
}

mbsize_t 
CharLength16inUTF8B(const charUTF16_t* src, conversionInfo_t* conver){
  if(src == 0 || conver->_state == BAD)
    return 0;
  else if(*src <= 0x7F)
    return 1;
  else if(*src <= 0x7FF)
    return 2;
  else if(*src <= 0xFFFF)
    return 3;
  else if(CharLength16(src, conver) == 2)
    return 4;
  else
    return 0;
}


mbsize_t 
UTF16toUTF8(const charUTF16_t* src, charUTF8_t* dest, conversionInfo_t* conver, const mbsize_t max){
  if(src == 0 || dest == 0 || conver == BAD)
    return 0;
  
  mbsize_t u16_cp_size = CharLength16(src, conver);
  mbsize_t u8_cp_bytes = 0;
  switch(u16_cp_size){
    case 1:
      if (*src < 0x80 && max >= 1){
        u8_cp_bytes = 1;
        *dest = *src;
      }else if (*src < 0x800 && max >= 2){
        u8_cp_bytes = 2;
        dest[0] = (0xC0 | ((*src & 0x7C) >> 6));
        dest[1] = (0x80 | (*src & 0x3F));
      }else if (*src < 0xFFFF && max >= 3){
        u8_cp_bytes = 3;
        dest[0] = (0xE0 | ((*src & 0xF000) >> 12));
        dest[1] = (0x80 | ((*src & 0xFC) >> 6));
        dest[2] = (0x80 | (*src & 0x3F));
      }else {
        conver->_state = BAD;
      }
      break;
    case 2:
      if(max == 4){
        u8_cp_bytes = 4;
        uint8_t conversion_auxiliar = 0;
        if ( conver->_endianness == BIG_ENDIAN){
          conversion_auxiliar = (*src & 0x03C) + 1;
          dest[0] = (0xF0 | (conversion_auxiliar & 0x1C));
          dest[1] = (0x80 | ((conversion_auxiliar & 0x03) << 4));
          dest[1] = (dest[1] | (*src & 0x3C));
          dest[2] = (0x80 | ((*src & 0x3) << 4));
          dest[2] = (dest[2] | ((src[1] & 0x03C0) >> 6));
          dest[3] = (0x80 | (src[1] & 0x3F));
        }else{
          conversion_auxiliar = (src[1] & 0x03C) + 1;
          dest[0] = (0xF0 | (conversion_auxiliar & 0x1C));
          dest[1] = (0x80 | ((conversion_auxiliar & 0x03) << 4));
          dest[1] = (dest[1] | (src[1] & 0x3C));
          dest[2] = (0x80 | ((src[1] & 0x3) << 4));
          dest[2] = (dest[2] | ((*src & 0x03C0) >> 6));
          dest[3] = (0x80 | (*src & 0x3F));
        }
      }else {
        conver->_state = BAD;
      }
      break;
    case 0:
      conver->_state = BAD;
  }
  return u8_cp_bytes;
}

mbsize_t 
UTF16toUTF32(const charUTF16_t* src, charUTF32_t* dest, conversionInfo_t* conver, const mbsize_t max){
  if(src == 0 || dest == 0 || conver->_state == BAD)
    return 0;
  mbsize_t u16_cp_size = CharLength16(src, conver);
  switch (u16_cp_size) {
    case 1:
      if(max >= 1){
        *dest = *src;
        if(conver->_endianness == BIG_ENDIAN)
          *dest = (*dest << 16);
        return 1;
      }
      break;
    case 2:
      if(max == 2){
        charUTF32_t destBE = 
          (((src[0] & 0x03ff) << 10) |
           (src[1] & 0x03ff));
        if(conver->_endianness == BIG_ENDIAN)
          *dest = destBE;
        else{
          *dest = (((destBE >> 24) & 0x000000ff) | //3th byte to 0th
              ((destBE << 8) & 0x00ff0000) | //1th byte to 2th
              ((destBE >> 8) & 0x0000ff00) | //2th byte to 1th
              ((destBE << 24) & 0xff000000)); //0th byte to 3th
        }
        return 2;
      }
      break;
  }
  conver->_state = BAD;
  return 0;
}

#ifdef __linux__
mbsize_t 
UTF16toWIDE(const charUTF16_t* src, widechar_t* dest, conversionInfo_t* conver, const mbsize_t max){
  return (UTF16toUTF32(src, dest, conver, max));
}
#endif /*__linux__*/
