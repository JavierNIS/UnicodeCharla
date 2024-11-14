#include "UTF32.h"
#include "mbstate.h"

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
  mbsize_t correct_conversion = 1;
  
  return correct_conversion;
}

mbsize_t 
UTF32toUTF16(const charUTF32_t* src, charUTF16_t* dest, conversionInfo_t* conver, const mbsize_t max);

#ifdef _WIN32
mbsize_t 
UTF32toWIDE(const charUTF32_t*, widechar_t*, conversionInfo_t*, const mbsize_t&);
#endif /*_WIN32*/
