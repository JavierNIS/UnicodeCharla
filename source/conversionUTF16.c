#include "UTF16.h"

/*
mbsize_t 
CharLength(const charUTF16_t* src, conversionInfo_t* conver, const charUTF16_t* (src+1)){
    if(src == 0 || conver->_state == BAD)
        return 0;
    else if(*src <= 0x7F)
        return 1;
    else if(*src <= 0x7FF)
        return 2;
    else if(*src <= 0xFFFF)
        return 3;
    else return 4;
};
*/
mbsize_t 
CharLength16(const charUTF16_t* src, conversionInfo_t* conver){
    if(src == 0 || conver->_state == BAD)
        return 0;
    else if(*(src+1) == 0) return 1;
    if(conver->_endianness == BIG_ENDIAN){
        if(0xD800 <= *src &&
                *src <= 0xDBFF)
            if(0xDC00 <= *(src+1) &&
                    *(src+1) <= 0xDFFF) return 2;
    }else{
        if(0xDC00 <= *src &&
                *src <= 0xDFFF)
           if(0xD800 <= *(src+1) &&
                   *(src+1) <= 0xDBFF) return 2;
    }
    return 1;
}


mbsize_t 
UTF16toUTF8(const charUTF16_t* src, charUTF8_t* dest, conversionInfo_t* conver, const mbsize_t max){
    return 0;
}

mbsize_t 
UTF16toUTF32(const charUTF16_t* src, charUTF32_t* dest, conversionInfo_t* conver, const mbsize_t max){
    return 0;
}

#ifdef __linux__
mbsize_t 
UTF16toWIDE(const charUTF16_t* src, widechar_t* dest, conversionInfo_t* conver, const mbsize_t max){
        return (UTF16toUTF32(src, dest, conver, max));
}
#endif /*__linux__*/
