#ifndef STRING_UTIL_H
#define STRING_UTIL_H
#include "../../syscall-interface.h"
#include "../array-util/array-clear.h"
int MikosLib_Util_StringCompare(char *me, char *other,unsigned int max);
int MikosLib_Util_StringEquals(char *me, char *other, unsigned int max);
void MikosLib_Util_StringCopy(char *me,char *other,unsigned int max);
char *MikosLib_Util_StringSubstring(char *me, char delimiter, unsigned int max);
#endif // STRING_UTIL_H
