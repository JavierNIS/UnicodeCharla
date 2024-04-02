#include "UTF16.h"
#include "UTF8.h"
#include "mbstate.h"
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
    int size=0;
    charUTF8_t caracter[5]={0};
    conversionInfo_t conver;
    Initialize(&conver);

    printf("Introduce num:\n");
    do{
        scanf("%d", &size);
    }while (size <= 0 || size > 4);


    printf("Introduce el caracter:\n");
    scanf("%4s", caracter);

    int tamañoreal = CharLength(caracter, &conver);

    printf("Para el caracter: %s\n", caracter);
    printf("El tamaño es: %d\n\n", tamañoreal);

    charUTF16_t* utf16caracter = 0;
    if(tamañoreal == 4)
        utf16caracter = (charUTF16_t*)malloc(2*sizeof(charUTF16_t));
    else
        utf16caracter = (charUTF16_t*)malloc(sizeof(charUTF16_t));

    printf("Convirtiendo a UTF16...\n\n");

    if(UTF8toUTF16(caracter, utf16caracter, &conver, size) != tamañoreal){
        printf("problema en conversión a utf16\n");
        return -1;
    }
    printf("En hexadecimal: ");
    if(tamañoreal == 4)
        printf("%x %x", utf16caracter[0], utf16caracter[1]);
    else
        printf("%x", *utf16caracter);
    printf("\nEl tamaño del caracter en utf-16 es: %hhu\n", CharLength16(utf16caracter, &conver));
    printf("\n\n");

    charUTF32_t utf32caracter;

    printf("Convirtiendo a UTF32...\n\n");

    if(UTF8toUTF32(caracter, &utf32caracter, &conver, size) != tamañoreal){
        printf("problema en conversión a utf32\n");
        return -1;
    }

    printf("En hexadecimal: %x\n", utf32caracter);
    printf("caracter: %d\n\n", utf32caracter);

    free(utf16caracter);
    return 0;
}
