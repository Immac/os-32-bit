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
