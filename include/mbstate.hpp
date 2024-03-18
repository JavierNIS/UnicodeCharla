#ifndef _MBSTATE_
#define _MBSTATE_

#define OK 0
#define BAD -1

typedef struct{
    char* mbchar;
    int state;
} conversionstate_t;

void Initialize(conversionstate_t* conver);
void SetError(conversionstate_t* conver, char* badmb);
void Reset(conversionstate_t* conver);


#endif /*_MBSTATE*/
