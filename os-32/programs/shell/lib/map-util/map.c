#include "map.h"
#include "../string-util/string-util.h"
void MikosLib_StoI_Map_Construct(MikosLib_StoI_Map_type *me, MikosLib_StoI_MapEntry_type *map)
{
    me->map = map;
}

int MikosLib_StoI_Map_EvaluateKey(MikosLib_StoI_Map_type *me, char *key, int size)
{
    int i = 0;
    char *currentKey = me->map[i].key;
    while (currentKey) {
        if (MikosLib_Util_StringCompare(currentKey, key,size) == 0)
            return me->map[i].value;
        currentKey = me->map[++i].key;
    }
    return -1;
}
