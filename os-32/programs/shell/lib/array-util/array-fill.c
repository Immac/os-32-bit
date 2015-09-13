#include "array-fill.h"
int MikosLib_Util_ArrayFill(char* array,char fill,unsigned int size)
{
    for(int i = 0; i < size; i++)
    {
        array[i] = fill;
    }
}
