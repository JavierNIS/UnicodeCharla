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

    cout << "El tamaño es: " << CharLength(caracter, size) << endl;

    return 0;
}
