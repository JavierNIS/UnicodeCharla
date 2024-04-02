#include "UTF8.h"
#include "mbstate.h"

mbsize_t 
CharLength(const charUTF8_t* src, conversionInfo_t* conver){
    if(src == 0 || conver->_state == BAD)
        return 0;
    else if((*src & 0x80) == 0x0) //Code point de un byte
        return 1;
    else if((*src & 0xF0) == 0xC0) //Dos bytes
        return 2;
    else if((*src & 0xF0) == 0xE0) //Tres bytes
        return 3;
    else if((*src & 0xF0) == 0xF0) //Cuatro bytes
        return 4;
    else{
        SetError(conver, (charUTF8_t*)src);
        return 0;
    }
}

////////////////////////////////////////////////////////////////////////////////

mbsize_t 
UTF8toUTF16(const charUTF8_t* src, charUTF16_t* dest, conversionInfo_t* conver, const mbsize_t max){
    if(dest == 0 || conver == 0)
        return 0;
    switch (CharLength(src, conver)){
        case 0:
            SetError(conver, (charUTF8_t*)src);
            return 0;
            break;
        case 1:
            if(max >= 1){
                *dest = *src;
                return 1;
            }
            break;
        case 2:
            if(max >= 2){
                *dest = ((src[1] & 0x3F) |
                        (src[0] & 0x1F) << 6);
                return 2;
            }
            break;
        case 3:
            if(max >= 3){
                *dest = ((src[2] & 0x3F) | 
                        (src[1] & 0x3F) << 6 | 
                        (src[0] & 0x0F) << 12);
                return 3;
            }
            break;
        case 4:
            if(max == 4){
                dest[1] = ( 0xDC00 | 
                        (src[3] & 0x3F) | 
                        (src[2] & 0x0F) << 6);
                dest[0] = ( 0xD800 | 
                        (src[2] & 0x30) >> 4 | 
                        ((src[1] -0x10) & 0x3F) << 2 | 
                        (src[0] & 0x07) << 8);
                return 4;
            } 
            break;
    }
    SetError(conver, (charUTF8_t*)src);
    return 0;
}

////////////////////////////////////////////////////////////////////////////////

mbsize_t 
UTF8toUTF32(const charUTF8_t* src, charUTF32_t* dest, conversionInfo_t* conver, const mbsize_t max){
    if(dest == 0 || conver == 0 || 
            conver->_state == BAD)
        return 0;
    switch (CharLength(src, conver)){
        case 0:
            return 0;
            break;
        case 1:
            if(max >= 1){
                *dest = *src;
                return 1;
            }
            break;
        case 2:
            if(max >= 2){
                *dest = ((src[1] & 0x3F) |
                        (src[0] & 0x1F) << 6);
                return 2;
            }
            break;
        case 3:
            if(max >= 3){
                *dest = ((src[2] & 0x3F) |
                        (src[1] & 0x3F) << 6 |
                        (src[0] & 0x0F) << 12);
                return 3;
            }
            break;
        case 4:
            if(max == 4){
                *dest = ((src[3] & 0x3F) |
                        (src[2] & 0x3F) << 6 |
                        (src[1] & 0x3F) << 12 |
                        (src[0] & 0x07) << 18);
                return 4;
            }
            break;
    }
    SetError(conver, (charUTF8_t*)src);
    return 0;
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
