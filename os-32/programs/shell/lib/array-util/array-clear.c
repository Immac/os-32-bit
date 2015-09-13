#include "array-clear.h"
#include "array-fill.h"
int MikosLib_Util_ArrayClear(char* array,unsigned int size)
{
    return MikosLib_Util_ArrayFill(array,0,size);
}
