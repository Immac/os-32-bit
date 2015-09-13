#ifndef STRING_UTIL_H
#define STRING_UTIL_H
int MikosLib_Util_StringCompare(char *me, char *other,unsigned int max);
int MikosLib_Util_StringEquals(char *me, char *other, unsigned int max);
char *MikosLib_Util_StringSubstring(char *me, char divisor, unsigned int max);
#endif // STRING_UTIL_H
