#include <iostream>
#include "UTF8.hpp"
#include "mbstate.hpp"

using namespace std;

int main (int argc, char *argv[]) {
    int size=0;
    charUTF8_t caracter[5]={0};

    cout << "Introduce num:" << endl;
    do{
        cin >> size;
    }while (size <= 0 || size > 4);

    caracter[size]='\0';

    for(int i = 0; i < size; i++)
        cin >> caracter[i];

    size_t tamañoreal = CharLength(caracter, size);
    cout << "El tamaño es: " << tamañoreal << endl << endl;
    
    charUTF16_t* utf16caracter = 0;
    if(tamañoreal == 4)
        utf16caracter = new charUTF16_t[2];
    else
        utf16caracter = new charUTF16_t;
    conversionstate_t conver;
    Initialize(&conver);
    
    cout << "Convirtiendo a UTF16: " << endl << endl;

    if(UTF8toUTF16(caracter, utf16caracter, &conver, size) != tamañoreal){
        cerr << "problema en conversión a utf16" << endl;
        return -1;
    }

    cout << "En hexadecimal: " << hex << *utf16caracter; 

    if(tamañoreal == 4)
        cout << utf16caracter[1];
    cout << endl;
    cout << "caracter: " << dec << *utf16caracter << endl << endl;

    charUTF32_t utf32caracter;

    cout << "Convirtiendo a UTF32: " << endl << endl;

    if(UTF8toUTF32(caracter, &utf32caracter, &conver, size) != tamañoreal){
        cerr << "problema en conversión a utf16" << endl;
        return -1;
    }

    cout << "En hexadecimal: " << hex << utf32caracter << endl;
    cout << "caracter: " << dec << utf32caracter << endl << endl;

    if(tamañoreal == 4)
        delete [] utf16caracter;
    else
        delete utf16caracter;
    return 0;
}
