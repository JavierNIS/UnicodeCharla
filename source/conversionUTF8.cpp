#include "UTF8.hpp"

std::size_t 
CharLength(const charUTF8_t* src, const std::size_t& max){
    if(src == 0 && max == 0)
        return 0;
    else if((*src & 0x80) == 0x0 && max >= 1) //Code point de un byte
        return 1;
    else if((*src & 0xF0) == 0xC0 && max >= 2) //Dos bytes
        return 2;
    else if((*src & 0xF0) == 0xE0 && max >= 3) //Tres bytes
        return 3;
    else if((*src & 0xF0) == 0xF0 && max == 4) //Cuatro bytes
        return 4;
    else
        return 0;
}

std::size_t 
UTF8toUTF16(const charUTF8_t* src, charUTF16_t* dest, conversionstate_t* conver, const std::size_t& max){
    if(dest == 0 || conver == 0)
        return 0;
    switch (CharLength(src, max)){
        case 0:
            return 0;
            break;
        case 1:
            if(max >= 1)
                *dest = *src;
            else
                return 0;
            return 1;
            break;
        case 2:
            if(max >= 2)
                *dest = ((src[0] & 0x1F) << 5 | (src[1] & 0x3F));
            else
                return 0;
            return 2;
            break;
        case 3:
            if(max >= 3)
                *dest = ((src[2] & 0x3F) | (src[1] & 0x3F) << 6 | (src[0] & 0x0F) << 12);
        case 4:
            if(max == 4){
                dest[1] = ((src[3] & 0x3F) | (src[2] & 0x0F) << 6);
                dest[0] = ((src[2] & 0x30) | ((src[1] -0x10000) & 0x3F) << 2 | (src[0] & 0x07) << 7);
            }else 
                return 0;
            return 4;
            break;
            

std::size_t 
UTF8toUTF32(const charUTF8_t* src, charUTF32_t* dest, conversionstate_t* conver, const std::size_t& max);

std::size_t 
UTF8toWIDE(const charUTF8_t* src, widechar_t* dest, conversionstate_t* conver, const std::size_t& max);
