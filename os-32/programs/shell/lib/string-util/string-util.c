#include "string-util.h"

int MikosLib_Util_StringCompare(char *me, char *other,unsigned int max)
{   int i;
	for (i = 0; me[i] != '\0' && i < max;i++)
	{
		if(other[i] == '0')
			return 1;
		if(other[i] > me[i])
			return -1;
		if(me[i] > other[i])
			return 1;
	}
	if (i == max || other[i] == '\0')
		return 0;
	return -1;
}

int MikosLib_Util_StringEquals(char *me, char *other, unsigned int max)
{
    return !(MikosLib_Util_StringCompare(me,other,max));
}

char *MikosLib_Util_StringSubstring(char *me, char divisor, unsigned int max)
{
        char temp[max];
        MikosLib_Util_ArrayClear(temp,max);
        int i;
        for(i = 0; i < max ; i++)
        {
            temp[i] = me[i];
            if (temp[i] == divisor || temp[i] == 0)
            {
                break;
            }
        }
        temp[i] = 0;
        char *substring = Mikos_Malloc(i * sizeof(substring));
        MikosLib_Util_StringCopy(substring,temp,i);
        return substring;
}

void MikosLib_Util_StringCopy(char *me,char *other,unsigned int max)
{
    int i;
    for(i = 0; i < max; i++)
    {
        me[i] = other[i];
        if(me[i] == 0)
        {
            break;
        }
    }
    if(i == max - 1)
    {
        me[i] = 0;
    }
}
