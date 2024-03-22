#include "mbstate.h"

void Initialize(conversionstate_t* conver){
    conver->mbchar = nullptr;
    conver->state = OK;
};

void SetError(conversionstate_t* conver, char* badmb){
    conver->mbchar=badmb;
    conver->state=BAD;
}
void Reset(conversionstate_t* conver){
    conver->state=OK;
};
