#ifndef _MBSTATE_
#define _MBSTATE_

#include <cstdint>

#ifndef _UTF8_CHAR_
#define _UTF8_CHAR_
typedef uint_least8_t charUTF8_t;
#endif /*_UTF8_CHAR_*/

#ifndef _UTF16_CHAR_
#define _UTF16_CHAR_
typedef uint_least16_t charUTF16_t;
#endif /*_UTF16_CHAR_*/

#ifndef _UTF32_CHAR_
#define _UTF32_CHAR_
typedef uint_least32_t charUTF32_t;
#endif /*_UTF32_CHAR_*/

#ifndef _WIDE_CHAR_
#define _WIDE_CHAR_

#ifdef __linux__
typedef uint_least32_t widechar_t;
#endif /*__linux__*/

#ifdef _WIN32
typedef uint_least16_t widechar_t;
#endif /*_WIN32*/

#endif /*_WIDE_CHAR_*/


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
