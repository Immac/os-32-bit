#ifndef UTIL_MAP_H
#define UTIL_MAP_H

typedef struct MikosLib_StoI_MapEntry
{
    char *key;
    int value;
} MikosLib_StoI_MapEntry_type;

typedef struct MikosLib_StoI_Map
{
    MikosLib_StoI_MapEntry_type *map;
} MikosLib_StoI_Map_type;

void MikosLib_StoI_Map_Construct(MikosLib_StoI_Map_type *me, MikosLib_StoI_MapEntry_type *map);
int MikosLib_StoI_Map_EvaluateKey(MikosLib_StoI_Map_type *me, char *key, int size);

#endif // STRINGTOINTMAP_H
