#include "UTF16.h"
#include "mbstate.h"

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
    if(src == 0 || dest == 0)
        return 0;
    mbsize_t auxsize = CharLength16(src, conver);
    mbsize_t index = conver->_endianness == BIG_ENDIAN ?
        0 : 1;

    if(conver->_state == BAD)
        return 0;
    else if(auxsize == 2){
        if(max != 4){
            SetError(conver, dest);
            return 0;
        }
        charUTF16_t aux;

        aux = (src[index] & 0x03FF);
        aux += 0x0040;

        index = (index+1)%2;

        dest[3] = (src[index] & 0x003F);
        dest[2] = (((src[index] & 0x03C0) >> 6) |
                (aux & 0x0003));
        dest[1] = (aux & 0x00FC >> 2);
        dest[0] = (aux & 0x0700 >> 8);
        auxsize = 4;

    }else{
        switch(CharLength16inUTF8B(src, conver)){
            case 0:
                SetError(conver, dest);
                auxsize = 0;
                break;
            case 1:
                if(max >= 1){
                    *dest = *src;
                    auxsize = 1;
                }
                break;
            case 2:
                if(max >= 2){
                    dest[1] = ((*dest & 0x003F) | 0x80);
                    dest[0] = (((*dest & 0x07C0) >> 6) | 0xC0);
                    auxsize = 2;
                }
                break;
            case 3:
                if(max >= 3){
                    dest[2] = ((*dest & 0x003F) | 0x80);
                    dest[1] = (((*dest & 0x0FC0) >> 6) | 0x80);
                    dest[0] = (((*dest & 0xF000) >> 12) | 0xE0);
                    auxsize = 3;
                }
                break;
        }
    }
    return auxsize;
}

mbsize_t 
UTF16toUTF32(const charUTF16_t* src, charUTF32_t* dest, conversionInfo_t* conver, const mbsize_t max){
    if(src == 0 || dest == 0 || conver->_state == BAD)
        return 0;
    switch (CharLength16(src, conver)) {
        case 1:
            if(max >= 1){
                *dest = *src;
                return 1;
            }
            break;
        case 2:
            if(max == 2){
                *dest = (((src[0] & 0x03FF) << 10) |
                        (src[1] & 0x03FF));
                return 2;
            }
            break;
    }
    SetError(conver, 0);
    return 0;
}

#ifdef __linux__
mbsize_t 
UTF16toWIDE(const charUTF16_t* src, widechar_t* dest, conversionInfo_t* conver, const mbsize_t max){
        return (UTF16toUTF32(src, dest, conver, max));
}
#endif /*__linux__*/
