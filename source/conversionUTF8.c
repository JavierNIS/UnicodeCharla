#include "UTF8.h"

//TESTED
mbsize_t 
CharLength(const charUTF8_t* src, conversionInfo_t* conver){
  if(src == 0 || conver->_state == BAD)
    return 0;;
  if((*src & 0x80) == 0x0) //Code point of one byte
    return 1;
  charUTF8_t srcAux = *src & 0xF0;
  if(srcAux == 0xC0 || srcAux == 0xD0) //Two bytes
    return 2;
  else if(srcAux == 0xE0) //Three bytes
    return 3;
  else if(srcAux == 0xF0) //Four bytes
    return 4;
  else{
    SetError(conver, (void*)src);
    return 0;
  }
}

////////////////////////////////////////////////////////////////////////////////

mbsize_t 
UTF8toUTF16(const charUTF8_t* src, charUTF16_t* dest, conversionInfo_t* conver, const mbsize_t max){
  if(dest == 0 || conver == 0)
    return 0;
  mbsize_t u8_cp_size = CharLength(src, conver);
  if (u8_cp_size > max)
    u8_cp_size = 0;

  switch (u8_cp_size){
    default:
      SetError(conver, (void*)src);
      break;
    case 1:
      *dest = *src;
      break;
    case 2:
      *dest = ((src[1] & 0x3F) |
          (src[0] & 0x1F) << 6);
      break;
    case 3:
      *dest = ((src[2] & 0x3F) | 
          (src[1] & 0x3F) << 6 | 
          (src[0] & 0x0F) << 12);
      break;
    case 4:
      {}
      charUTF32_t code_point =
        ((src[0] & 0x7) << 18) + ((src[1] & 0x3F) << 12) +
        ((src[2] & 0x3F) << 6) + (src[3] & 0x3F) - 0x10000;
      dest[0] = (0xD800 | ((code_point >> 10)));
      dest[1] = (0xDC00 | ((code_point & 0x3FF)));
      /*dest[0] = ( 0xD800 | 
          (src[2] & 0x30) >> 4 | 
          ((src[1] -0x10) & 0x3F) << 2 | 
          (src[0] & 0x07) << 7);
      dest[1] = ( 0xDC00 | 
          (src[3] & 0x3F) | 
          (src[2] & 0x0F) << 6);*/

      if(conver->_endianness == LITTLE_ENDIAN)
        SwapEndiannessU16(dest);
      break;
  }
  return u8_cp_size;
}

////////////////////////////////////////////////////////////////////////////////

//TESTED
mbsize_t 
UTF8toUTF32(const charUTF8_t* src, charUTF32_t* dest, conversionInfo_t* conver, const mbsize_t max){
  if(dest == 0 || conver == 0 || 
      conver->_state == BAD)
    return 0;
  mbsize_t u8_cp_size = CharLength(src, conver);
  if(u8_cp_size > max)
    u8_cp_size = 0;
  
  switch (u8_cp_size){
    default:
      SetError(conver, (void*)src);
      break;
    case 1:
        *dest = *src;
      break;
    case 2:
        *dest = ((src[1] & 0x3F) |
            (src[0] & 0x1F) << 6);
      break;
    case 3:
        *dest = ((src[2] & 0x3F) |
            (src[1] & 0x3F) << 6 |
            (src[0] & 0x0F) << 12);
      break;
    case 4:
        *dest = ((src[3] & 0x3F) |
            (src[2] & 0x3F) << 6 |
            (src[1] & 0x3F) << 12 |
            (src[0] & 0x07) << 18);
      break;
  }

  if(conver->_endianness == LITTLE_ENDIAN)
    SwapEndiannessU32(dest);
  return u8_cp_size;
}
////////////////////////////////////////////////////////////////////////////////

mbsize_t 
UTF8toWIDE(const charUTF8_t* src, widechar_t* dest, conversionInfo_t* conver, const mbsize_t max){
#ifdef _WIN32
  return UTF8toUTF16(src, dest, conver, max);
#elif defined __linux__
  return UTF8toUTF32(src, dest, conver, max);
#endif
}
