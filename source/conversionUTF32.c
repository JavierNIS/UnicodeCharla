#include "UTF16.h"
#include "UTF32.h"
#include "mbstate.h"

mbsize_t
UTF32mbLength(const charUTF32_t* src){
  mbsize_t u8_cp_length = 0;
  if(*src < 0x80)
    u8_cp_length = 1;
  else if(*src < 0x800)
    u8_cp_length = 2;
  else if(*src < 0x10000)
    u8_cp_length = 3;
  else
    u8_cp_length = 4;
  return u8_cp_length;
}

mbsize_t
UTF32bytesToUTF16(const charUTF32_t* src){
  mbsize_t u16_cp_length = 0;
  u16_cp_length = *src <= 0xFFFF ? 1 : 2;
  return u16_cp_length;
}

void
SwapEndiannessU32(charUTF32_t* src){
  charUTF32_t auxiliar = *src;
  *src = (((auxiliar >> 24) & 0x000000ff) | //3th byte to 0th
      ((auxiliar << 8) & 0x00ff0000) | //1th byte to 2th
      ((auxiliar >> 8) & 0x0000ff00) | //2th byte to 1th
      ((auxiliar << 24) & 0xff000000)); //0th byte to 3th
}
mbsize_t 
UTF32toUTF8(const charUTF32_t* src, charUTF8_t* dest, conversionInfo_t* conver, const mbsize_t max){
  if(src == 0 || dest == 0 || conver->_state == BAD)
    return 0;
  mbsize_t u8_cp_length = UTF32mbLength((charUTF32_t*)src);
  if(u8_cp_length > max)
    u8_cp_length = 0;

  charUTF32_t srcBE = *dest;
  if(conver->_endianness == LITTLE_ENDIAN)
    SwapEndiannessU32(&srcBE);

  switch (u8_cp_length) {
    case 1:
      *dest = srcBE; 
      break;
    case 2:
      dest[0] = (0xC0 | ((srcBE & 0x7C0) >> 6));
      dest[1] = (0x80 | (srcBE & 0x3F));
      break;
    case 3:
      dest[0] = (0xE0 | ((srcBE & 0xF000) >> 12));
      dest[1] = (0x80 | ((srcBE & 0xFC0) >> 6));
      dest[2] = (0x80 | (srcBE & 0x3F));
      break;
    case 4:
      dest[0] = (0xF0 | ((srcBE & 0x1C0000) >> 18));
      dest[1] = (0x80 | ((srcBE & 0x030000) >> 12));
      dest[1] = (0x80 | ((srcBE & 0xF000) >> 12));
      dest[2] = (0x80 | ((srcBE & 0xFC0) >> 6));
      dest[3] = (0x80 | (srcBE & 0x3F));
      break;
    default:
      SetError(conver, (void*)src);
      break;
  }
  
  return u8_cp_length;
}

mbsize_t 
UTF32toUTF16(const charUTF32_t* src, charUTF16_t* dest, conversionInfo_t* conver, const mbsize_t max){
  if(src == 0 || dest == 0 || conver->_state == BAD)
    return 0;
  mbsize_t u16_cp_length = UTF32bytesToUTF16(src);
  if(u16_cp_length > max)
    u16_cp_length = 0;
  switch (u16_cp_length){
    case 1:
      *dest = *src;
      break;
    case 2:
      {}
      charUTF32_t code_point = *src;
      if(conver->_endianness == LITTLE_ENDIAN)
        SwapEndiannessU32(&code_point);
      code_point-= 0x10000;
      dest[0] = ( 0xD800 | ((0x001FFC00 & code_point) >> 10));
      dest[1] = ( 0xDC00 | (0x000003FF & code_point));
      if(conver->_endianness == LITTLE_ENDIAN)
        SwapEndiannessU16(dest);
      break;
    default:
      SetError(conver, (void*)src);
      break;
  }
  return u16_cp_length;
}

#ifdef _WIN32
mbsize_t 
UTF32toWIDE(const charUTF32_t* src, widechar_t* dest, conversionInfo_t* conver, const mbsize_t& max){
  return (UTF32toUTF16(src, dest, conver, max));
}
#endif /*_WIN32*/
