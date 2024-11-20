#include "UTF32.h"
#include "UTF16.h"
#include "UTF8.h"
#include <stdlib.h>
#include <stdio.h>

const static mbsize_t num_mb = 4;
const static mbsize_t num_utf16_surr = 2;

void TestALLCodePoints(void){
  char cexit = 'n';
  conversionInfo_t conver; 
  Initialize(&conver);
  for(uint32_t code_point = 0; code_point <= SSP_PLANE[1].end;
      code_point++){
    if(code_point >= 0xD800 && code_point <= 0xDFFF)
      continue;
    charUTF32_t utf32;
    charUTF16_t utf16[num_utf16_surr];
    charUTF8_t utf8[num_mb];
    utf32 = (charUTF32_t)code_point;
    printf("Code point: %u\n", utf32);
    UTF32toUTF8(&utf32, utf8, &conver, num_mb);
    if(!conver._state){
      printf("Error in conversion from utf32 to utf8\n");
      exit(-1);
    }
    printf("UTF8: %s\n", utf8);
    UTF32toUTF16(&utf32, utf16, &conver, num_utf16_surr);
    if(!conver._state){
      printf("Error in conversion from utf32 to utf16\n");
      exit(-1);
    }
    printf("UTF16: %X %X\n\n", utf16[0], utf16[1%num_utf16_surr]);
    if(code_point == BMP_PLANE[1].end || code_point == 0x7F){
      do{
        printf("Continue? [y/n]: ");
        scanf("%c", &cexit);
      }while(cexit != 'y' && cexit != 'n');
      if(cexit == 'n'){
        exit(0);
      }
    }
    UTF8toUTF32(utf8, &utf32, &conver, num_mb);
    if(!conver._state){
      printf("Error in conversion from utf8 to utf32\n");
      exit(-1);
    }
    else if (utf32 != code_point){
      printf("Error in conversion, the code points are not equal (UTF8).");
      printf("Code point obtained: %d\n", code_point);
      exit(-1);
    }
    UTF16toUTF32(utf16, &utf32, &conver, num_utf16_surr);
    if(!conver._state){
      printf("Error in conversion from utf16 to utf32\n");
      exit(-1);
    }
    else if (utf32 != code_point){
      printf("Error in conversion, the code points are not equal (UTF16).");
      printf("Code point obtained: %d\n", utf32);
      exit(-1);
    }
  }
}


int main(int argc, char *argv[]){
  TestALLCodePoints();
  return 0;
}
